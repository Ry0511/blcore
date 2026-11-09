#ifndef BLCORE_ENGINE_GOBJECTS_H
#define BLCORE_ENGINE_GOBJECTS_H

#include "blcore/blcore.h"
#include "blcore/ue3/mapping/fwd.h"
#include "blcore/ue3/tarray.h"

#include <span>

namespace blcore::engine {

class GObjects {
   public:
    explicit GObjects(ue3::TArray<ue3::UObject*>* array) : m_Objects{array} {}

    [[nodiscard]] ue3::TArray<ue3::UObject*>* data() const { return m_Objects; }
    [[nodiscard]] size_t size() const { return objects().size(); }
    [[nodiscard]] auto begin() const { return objects().begin(); }
    [[nodiscard]] auto end() const { return objects().end(); }

    [[nodiscard]] ue3::UObject* at(size_t index) const {
        const std::span<ue3::UObject*> items = objects();
        return (index < items.size())
                   ? items.subspan(index, 1).front()
                   : nullptr;
    }

   private:
    ue3::TArray<ue3::UObject*>* m_Objects{nullptr};

    [[nodiscard]] std::span<ue3::UObject*> objects() const {
        return (m_Objects != nullptr) ? m_Objects->span() : std::span<ue3::UObject*>{};
    }
};

}  // namespace blcore::engine

#endif  // BLCORE_ENGINE_GOBJECTS_H
