#ifndef BLCORE_API_API_H
#define BLCORE_API_API_H

// NOLINTBEGIN(cppcoreguidelines-macro-usage)

#define BLCORE_CALL __cdecl
#define BLCORE_EXPORT __declspec(dllexport)
#define BLCORE_IMPORT __declspec(dllimport)

#ifdef BLCORE_EXPORTS
#define BLCORE_API BLCORE_EXPORT
#else
#define BLCORE_API BLCORE_IMPORT
#endif

#define BLCORE_API_FN(ret, name, ...) \
    extern "C" BLCORE_API ret BLCORE_CALL name(__VA_ARGS__) noexcept(false)

// NOLINTEND(cppcoreguidelines-macro-usage)

#endif  // BLCORE_API_API_H
