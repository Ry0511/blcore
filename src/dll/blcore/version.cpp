#include "blcore/pch.h"
#include "blcore/version.h"

namespace blcore {

namespace {

#include "blcore/version.inl"

constexpr auto GIT_SHA1 = std::string_view{GIT_HEAD_SHA1};

}  // namespace

const std::string& get_version_string() {
    static const std::string version_str = std::format(
        "blcore v{}.{}.{} ({})",
        VERSION_MAJOR,
        VERSION_MINOR,
        VERSION_PATCH,
        GIT_SHA1.substr(0, 8)
    );
    return version_str;
}

}  // namespace blcore
