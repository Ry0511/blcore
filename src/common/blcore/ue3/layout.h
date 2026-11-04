#ifndef BLCORE_UE3_LAYOUT_H
#define BLCORE_UE3_LAYOUT_H

namespace blcore {

namespace bl1 {}
namespace bl1e {}

#ifdef WILLOW
namespace layout = bl1;

#elifdef WILLOW64
namespace layout = bl1e;

#else
#error "define WILLOW or WILLOW64"
#endif

}  // namespace blcore

#endif  // BLCORE_UE3_LAYOUT_H
