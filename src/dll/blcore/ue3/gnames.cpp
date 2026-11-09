#include "blcore/pch.h"

#include "blcore/api/gnames.h"
#include "blcore/game/game.h"

BLCORE_API_FN(blcore::ue3::TArray<blcore::ue3::FNameEntry*>*, blcore_get_gnames) {
    return blcore::game::current().gnames().data();
}
