#include "blcore/pch.h"

#include "blcore/ue3/globals.h"
#include "blcore/ue3/gobjects.h"

BLCORE_API_FN(blcore::ue3::TArray<void*>*, blcore_get_gobjects) {
    return blcore::ue3::found_globals().gobjects;
}
