#include "blcore/util/hook.h"

namespace blcore::hook {

bool remove(void* target) {
    return blcore_hook_remove(target) == API_OK;
}

bool enable(void* target) {
    return blcore_hook_enable(target) == API_OK;
}

bool disable(void* target) {
    return blcore_hook_disable(target) == API_OK;
}

}  // namespace blcore::hook
