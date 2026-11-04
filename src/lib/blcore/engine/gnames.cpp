#include "blcore/api/gnames.h"
#include "blcore/engine/gnames.h"

namespace blcore::engine {

GNames::GNames() : m_Entries{blcore_get_gnames()} {}

std::span<ue3::FNameEntry*> GNames::entries() const {
    return (m_Entries != nullptr) ? m_Entries->span() : std::span<ue3::FNameEntry*>{};
}

}  // namespace blcore::engine
