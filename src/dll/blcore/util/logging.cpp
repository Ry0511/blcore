#include "blcore/pch.h"

#include "blcore/util/common.h"
#include "blcore/util/logging.h"
#include "blcore/util/logging_backend.h"
#include "blcore/util/win_console.h"

namespace blcore::logging {

namespace {

using clock = std::chrono::system_clock;

struct Message {
    clock::time_point time;
    Level level;
    std::string msg;
};

std::mutex _queue_mutex;
std::condition_variable _queue_cv;
std::vector<Message> _message_queue;
std::atomic_bool _stopping{false};
std::atomic_bool _stopped{false};

std::mutex _sinks_mutex;
std::vector<std::ofstream> _files;
std::optional<WinConsole> _console;

std::atomic_bool _initialised{false};

////////////////////////////////////////////////////////////////////////////////
// | FORMATTING |
////////////////////////////////////////////////////////////////////////////////

std::string_view level_name(Level level) {
    // clang-format off
    switch (level) {
        case Level::Misc:  return "MISC ";
        case Level::Info:  return "INFO ";
        case Level::Warn:  return "WARN ";
        case Level::Debug: return "DEBUG";
        case Level::Error: return "ERROR";
    }
    // clang-format on
    return "UNKNOWN";
}

std::string timestamp(clock::time_point time) {
    const std::time_t time_t = clock::to_time_t(time);
    std::tm local{};
    localtime_s(&local, &time_t);
    return std::format(
        "{:04}/{:02}/{:02} {:02}:{:02}",
        local.tm_year + 1900,
        local.tm_mon + 1,
        local.tm_mday,
        local.tm_hour,
        local.tm_min
    );
}

void format_message(std::string& out, const Message& message) {
    const std::string prefix = std::format("{} | {} | ", timestamp(message.time), level_name(message.level));

    std::string_view rest = message.msg;
    while (true) {
        const size_t end = rest.find('\n');
        std::string_view line = rest.substr(0, end);
        if (line.ends_with('\r')) {
            line.remove_suffix(1);
        }

        out += prefix;
        out += line;
        out += '\n';

        if (end == std::string_view::npos) {
            break;
        }
        rest.remove_prefix(end + 1);
        if (rest.empty()) {
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// | LOGGER THREAD |
////////////////////////////////////////////////////////////////////////////////

void write_raw_text(const std::string& text) {
    const std::scoped_lock lock{_sinks_mutex};

    for (auto& file : _files) {
        file.write(text.data(), static_cast<std::streamsize>(text.size()));
        file.flush();
    }

    if (_console) {
        _console->write(text);
    }
}

void logger_thread() {
    std::vector<Message> local_queue{};
    std::string local_text{};

    while (true) {
        bool stop = false;
        {
            std::unique_lock lock{_queue_mutex};
            _queue_cv.wait_for(
                lock,
                std::chrono::milliseconds{100},
                [] { return _stopping || !_message_queue.empty(); }
            );
            stop = _stopping;
            local_queue.swap(_message_queue);
        }

        local_text.clear();
        for (const auto& message : local_queue) {
            format_message(local_text, message);
        }
        local_queue.clear();

        if (!local_text.empty()) {
            write_raw_text(local_text);
        }

        if (stop) {
            local_text.clear();
            format_message(
                local_text,
                {
                    .time = clock::now(),
                    .level = Level::Info,
                    .msg = "logging thread stopping",
                }
            );
            write_raw_text(local_text);
            break;
        }
    }

    {
        const std::scoped_lock lock{_sinks_mutex};
        _files.clear();
        _console.reset();
    }

    _stopped = true;
    _stopped.notify_all();
}

void enqueue(Level level, std::string&& msg) {
    {
        const std::scoped_lock lock{_queue_mutex};
        _message_queue.push_back({
            .time = clock::now(),
            .level = level,
            .msg = std::move(msg),
        });
    }
    _queue_cv.notify_one();
}

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// | API |
////////////////////////////////////////////////////////////////////////////////

void initialise() {
    if (_initialised.exchange(true)) {
        return;
    }

    _stopping = false;
    _stopped = false;
    std::thread{&logger_thread}.detach();
}

void terminate(bool wait) {
    if (!_initialised.exchange(false)) {
        return;
    }

    _stopping = true;
    _queue_cv.notify_one();

    if (wait) {
        _stopped.wait(false);
    }
}

void set_console_logging(bool enabled) {
    const std::scoped_lock lock{_sinks_mutex};
    if (!enabled) {
        _console.reset();
    } else if (!_console) {
        _console.emplace();
    }
}

void add_log_file(const fs::path& out, bool append) {
    std::ofstream file{out, append ? std::ios::app : std::ios::trunc};
    if (!file.is_open()) {
        enqueue(Level::Error, std::format("failed to open log file '{}'", util::narrow(out.wstring())));
        return;
    }

    const std::scoped_lock lock{_sinks_mutex};
    _files.push_back(std::move(file));
}

}  // namespace blcore::logging

////////////////////////////////////////////////////////////////////////////////
// | EXPORTS |
////////////////////////////////////////////////////////////////////////////////

BLCORE_API_FN(void, blcore_log, blcore::logging::Level level, const char* msg, size_t len) {
    const std::string_view view{msg, len};
    blcore::logging::enqueue(level, std::string{view});
}

BLCORE_API_FN(void, blcore_log_wide, blcore::logging::Level level, const wchar_t* msg, size_t len) {
    const std::wstring_view view{msg, len};
    blcore::logging::enqueue(level, blcore::util::narrow(view));
}
