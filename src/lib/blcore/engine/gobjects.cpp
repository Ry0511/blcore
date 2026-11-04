#include "blcore/api/gobjects.h"
#include "blcore/engine/gobjects.h"

namespace blcore::engine {

GObjects::GObjects() : m_Objects{blcore_get_gobjects()} {}

std::span<ue3::UObject*> GObjects::objects() const {
    return (m_Objects != nullptr) ? m_Objects->span() : std::span<ue3::UObject*>{};
}

}  // namespace blcore::engine
