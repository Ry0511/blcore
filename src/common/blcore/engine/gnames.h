#ifndef BLCORE_ENGINE_GNAMES_H
#define BLCORE_ENGINE_GNAMES_H

#include "blcore/blcore.h"
#include "blcore/ue3/mapping/fwd.h"
#include "blcore/ue3/tarray.h"

#include <span>

namespace blcore::engine {

class GNames {
   public:
    explicit GNames(ue3::TArray<ue3::FNameEntry*>* array) : m_Entries{array} {}

    [[nodiscard]] ue3::TArray<ue3::FNameEntry*>* data() const {
        return m_Entries;
    }

    [[nodiscard]] size_t size() const {
        return entries().size();
    }

    [[nodiscard]] ue3::FNameEntry* at(size_t index) const {
        const std::span<ue3::FNameEntry*> items = entries();
        return (index < items.size())
                   ? items.subspan(index, 1).front()
                   : nullptr;
    }

    [[nodiscard]] auto begin() const {
        return entries().begin();
    }

    [[nodiscard]] auto end() const {
        return entries().end();
    }

   private:
    ue3::TArray<ue3::FNameEntry*>* m_Entries{nullptr};

    [[nodiscard]] std::span<ue3::FNameEntry*> entries() const {
        return (m_Entries != nullptr)
                   ? m_Entries->span()
                   : std::span<ue3::FNameEntry*>{};
    }
};

}  // namespace blcore::engine

#endif  // BLCORE_ENGINE_GNAMES_H
