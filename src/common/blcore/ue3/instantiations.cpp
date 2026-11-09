#include "blcore/blcore.h"
#include "blcore/ue3/fname.h"
#include "blcore/ue3/mapping/vfunc.h"
#include "blcore/ue3/tarray.h"
#include "blcore/ue3/tmap/tinlineallocator.h"
#include "blcore/ue3/tmap/tmap.h"
#include "blcore/ue3/tmap/tset.h"
#include "blcore/ue3/tmap/tsparsearray.h"

namespace blcore::ue3 {

template struct TArray<int32_t>;
template struct TInlineAllocator<int32_t, 1>;
template struct TSparseArray<int32_t>;
template struct TSet<int32_t>;
template struct TMap<FName, void*>;
template struct VFunc<int32_t(int32_t), 0>;

}  // namespace blcore::ue3
