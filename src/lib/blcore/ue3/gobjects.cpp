#include "blcore/api/gobjects.h"
#include "blcore/ue3/gobjects.h"

namespace blcore::ue3 {

GObjects::GObjects() : m_Objects{blcore_get_gobjects()} {}

std::span<void*> GObjects::objects() const {
    return (m_Objects != nullptr) ? m_Objects->span() : std::span<void*>{};
}

}  // namespace blcore::ue3
