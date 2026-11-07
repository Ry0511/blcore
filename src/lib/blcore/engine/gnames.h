#ifndef BLCORE_ENGINE_GNAMES_H
#define BLCORE_ENGINE_GNAMES_H

#include "blcore/blcore.h"
#include "blcore/ue3/mapping/fwd.h"
#include "blcore/ue3/tarray.h"

#include <span>

namespace blcore::engine {

class GNames {
   public:
    GNames();

    [[nodiscard]] size_t size() const {
        return entries().size();
    }

    [[nodiscard]] ue3::FNameEntry* at(size_t index) const {
        const std::span<ue3::FNameEntry*> entries = this->entries();
        return (index < entries.size()) ? entries.subspan(index, 1).front() : nullptr;
    }

    [[nodiscard]] auto begin() const {
        return entries().begin();
    }

    [[nodiscard]] auto end() const {
        return entries().end();
    }

   private:
    ue3::TArray<ue3::FNameEntry*>* m_Entries{nullptr};

    [[nodiscard]] std::span<ue3::FNameEntry*> entries() const;
};

}  // namespace blcore::engine

#endif  // BLCORE_ENGINE_GNAMES_H
