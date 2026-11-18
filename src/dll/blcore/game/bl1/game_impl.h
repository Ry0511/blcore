#ifndef BLCORE_GAME_BL1_GAME_IMPL_H
#define BLCORE_GAME_BL1_GAME_IMPL_H

#include "blcore/game/game.h"

namespace blcore::game::bl1 {

class GameImpl final : public Game {
   public:
    [[nodiscard]] std::string_view name() const override;
    [[nodiscard]] bool is_unpacked() const override;

    [[nodiscard]] const AddressTable& address_table() const override;

   private:
    void initialise() override;
    void find_globals();
    static void apply_patches();

    AddressTable m_AddressTable;
};

}  // namespace blcore::game::bl1

#endif  // BLCORE_GAME_BL1_GAME_IMPL_H
