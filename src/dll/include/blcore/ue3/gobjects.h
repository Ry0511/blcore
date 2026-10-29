#ifndef BLCORE_UE3_GOBJECTS_H
#define BLCORE_UE3_GOBJECTS_H

#include "blcore/api/gobjects.h"
#include "blcore/ue3/tarray.h"

#include <cstddef>
#include <span>

namespace blcore::ue3 {

class GObjects {
   public:
    GObjects() = default;

    [[nodiscard]] std::size_t size() const {
        return objects().size();
    }

    [[nodiscard]] void* at(std::size_t index) const {
        const std::span<void*> objects = this->objects();
        return (index < objects.size()) ? objects.subspan(index, 1).front() : nullptr;
    }

    [[nodiscard]] auto begin() const {
        return objects().begin();
    }

    [[nodiscard]] auto end() const {
        return objects().end();
    }

   private:
    TArray<void*>* m_Objects{blcore_get_gobjects()};

    [[nodiscard]] std::span<void*> objects() const {
        return (m_Objects != nullptr) ? m_Objects->span() : std::span<void*>{};
    }
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_GOBJECTS_H
