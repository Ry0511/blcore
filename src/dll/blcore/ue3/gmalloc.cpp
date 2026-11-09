#include "blcore/pch.h"

#include "blcore/api/gmalloc.h"
#include "blcore/game/game.h"

BLCORE_API_FN(blcore::ue3::FMalloc**, blcore_get_gmalloc) {
    return blcore::game::current().gmalloc().data();
}
