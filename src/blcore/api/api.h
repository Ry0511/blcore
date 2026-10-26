#ifndef BLCORE_API_API_H
#define BLCORE_API_API_H

// NOLINTBEGIN(cppcoreguidelines-macro-usage)

#ifdef BLCORE_EXPORTS
#define BLCORE_API __declspec(dllexport)
#else
#define BLCORE_API __declspec(dllimport)
#endif

#define BLCORE_API_FN(ret, name, ...) \
    extern "C" BLCORE_API ret __cdecl name(__VA_ARGS__) noexcept(false)

// NOLINTEND(cppcoreguidelines-macro-usage)

#endif  // BLCORE_API_API_H
