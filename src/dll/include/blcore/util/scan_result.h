#ifndef BLCORE_UTIL_SCAN_RESULT_H
#define BLCORE_UTIL_SCAN_RESULT_H

#include "blcore/api/protected_memory.h"
#include "blcore/blcore.h"
#include "blcore/util/logging.h"

#include <span>

namespace blcore::sigscan {

class ScanResult {
   public:
    ScanResult() = default;
    explicit ScanResult(void* address) : m_Address{static_cast<uint8_t*>(address)} {}

    [[nodiscard]] bool has_result() const {
        return m_Address != nullptr;
    }

    [[nodiscard]] uint8_t* get() const {
        return m_Address;
    }

    bool write(ptrdiff_t offset, uint8_t value) const {
        return write(offset, std::span<const uint8_t>{&value, 1});
    }

    bool write(ptrdiff_t offset, std::span<const uint8_t> bytes) const {
        if (!has_result()) {
            BLCORE_ERROR("Can't write {} bytes to an empty scan result", bytes.size());
            return false;
        }
        return blcore_write_protected_memory(m_Address + offset, bytes.data(), bytes.size()) == API_OK;
    }

   private:
    uint8_t* m_Address{nullptr};
};

}  // namespace blcore::sigscan

#endif  // BLCORE_UTIL_SCAN_RESULT_H
