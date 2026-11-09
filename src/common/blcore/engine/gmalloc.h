#ifndef BLCORE_ENGINE_GMALLOC_H
#define BLCORE_ENGINE_GMALLOC_H

#include "blcore/blcore.h"
#include "blcore/ue3/fmalloc.h"

namespace blcore::engine {

// this is here for abi reasons, but BL1 and BL1E both ignore the alignment parameter and always
//  align GMalloc to 16
inline constexpr uint32_t DEFAULT_ALIGNMENT = 8;

class GMalloc {
   public:
    explicit GMalloc(ue3::FMalloc** gmalloc) : m_GMalloc{gmalloc} {}

    [[nodiscard]] ue3::FMalloc** data() const {
        return m_GMalloc;
    }

    [[nodiscard]] ue3::FMalloc* get() const {
        return (m_GMalloc != nullptr) ? *m_GMalloc : nullptr;
    }

    [[nodiscard]] void* malloc(
        size_t size,
        uint32_t alignment = DEFAULT_ALIGNMENT
    ) const {
        ue3::FMalloc* fmalloc = get();
        return (fmalloc != nullptr)
                   ? fmalloc->Malloc(static_cast<uint32_t>(size), alignment)
                   : nullptr;
    }

    [[nodiscard]] void* realloc(
        void* original,
        size_t size,
        uint32_t alignment = DEFAULT_ALIGNMENT
    ) const {
        ue3::FMalloc* fmalloc = get();
        return (fmalloc != nullptr)
                   ? fmalloc->Realloc(original, static_cast<uint32_t>(size), alignment)
                   : nullptr;
    }

    void free(void* data) const {
        ue3::FMalloc* fmalloc = get();
        if (fmalloc != nullptr && data != nullptr) {
            fmalloc->Free(data);
        }
    }

   private:
    ue3::FMalloc** m_GMalloc{nullptr};
};

}  // namespace blcore::engine

#endif  // BLCORE_ENGINE_GMALLOC_H
