#ifndef BLCORE_VERSION_H
#define BLCORE_VERSION_H

#include "blcore/blcore.h"

namespace blcore {

#include "blcore/version.inl"

constexpr int VERSION_MAJOR = PROJECT_VERSION_MAJOR;
constexpr int VERSION_MINOR = PROJECT_VERSION_MINOR;
constexpr int VERSION_PATCH = PROJECT_VERSION_PATCH;

#undef PROJECT_VERSION_MAJOR
#undef PROJECT_VERSION_MINOR
#undef PROJECT_VERSION_PATCH
#undef GIT_HEAD_SHA1

const std::string& get_version_string();

}  // namespace blcore

#endif  // BLCORE_VERSION_H
