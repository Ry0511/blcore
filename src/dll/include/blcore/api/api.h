#ifndef BLCORE_API_API_H
#define BLCORE_API_API_H

#include "blcore/blcore.h"

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

namespace blcore {

using ApiResult = uint32_t;

inline constexpr ApiResult API_OK = 0;
inline constexpr ApiResult API_FAIL = 1;

}  // namespace blcore

#endif  // BLCORE_API_API_H
