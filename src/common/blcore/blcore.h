#ifndef BLCORE_BLCORE_H
#define BLCORE_BLCORE_H

#include <cstdint>
#include <string>
#include <filesystem>

namespace blcore {

#ifdef WILLOW64
static_assert(sizeof(void*) == 8, "x64 required for bl1e");
#endif

#ifdef WILLOW
static_assert(sizeof(void*) == 4, "x86 required for bl1");
#endif

namespace fs = std::filesystem;

using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::uint8_t;

using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::int8_t;

using std::intptr_t;
using std::size_t;
using std::uintptr_t;

}  // namespace blcore

#endif  // BLCORE_BLCORE_H
