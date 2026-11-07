#ifndef BLCORE_GAME_BL1_GAME_IMPL_H
#define BLCORE_GAME_BL1_GAME_IMPL_H

#include "blcore/game/game.h"

namespace blcore::game::bl1 {

class GameImpl final : public Game {
   public:
    [[nodiscard]] std::string_view name() const override;
    [[nodiscard]] bool is_unpacked() const override;

    void* malloc(void* gmalloc, size_t size, uint32_t alignment) const override;
    void* realloc(void* gmalloc, void* original, size_t size, uint32_t alignment) const override;
    void free(void* gmalloc, void* data) const override;

   private:
    void find_globals(Globals& out) const override;
    void apply_patches() const override;
};

}  // namespace blcore::game::bl1

#endif  // BLCORE_GAME_BL1_GAME_IMPL_H
