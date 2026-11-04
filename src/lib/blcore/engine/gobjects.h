#ifndef BLCORE_ENGINE_GOBJECTS_H
#define BLCORE_ENGINE_GOBJECTS_H

#include "blcore/blcore.h"
#include "blcore/ue3/fwd.h"
#include "blcore/ue3/tarray.h"

#include <span>

namespace blcore::engine {

class GObjects {
   public:
    GObjects();

    [[nodiscard]] size_t size() const {
        return objects().size();
    }

    [[nodiscard]] ue3::UObject* at(size_t index) const {
        const std::span<ue3::UObject*> objects = this->objects();
        return (index < objects.size()) ? objects.subspan(index, 1).front() : nullptr;
    }

    [[nodiscard]] auto begin() const {
        return objects().begin();
    }

    [[nodiscard]] auto end() const {
        return objects().end();
    }

   private:
    ue3::TArray<ue3::UObject*>* m_Objects{nullptr};

    [[nodiscard]] std::span<ue3::UObject*> objects() const;
};

}  // namespace blcore::engine

#endif  // BLCORE_ENGINE_GOBJECTS_H
