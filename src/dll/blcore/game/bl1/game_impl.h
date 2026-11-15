#ifndef BLCORE_GAME_BL1_GAME_IMPL_H
#define BLCORE_GAME_BL1_GAME_IMPL_H

#include "blcore/game/game.h"
#include "blcore/ue3/mapping/fwd.h"
#include "blcore/ue3/tarray.h"

namespace blcore::game::bl1 {

class GameImpl final : public Game {
   public:
    [[nodiscard]] std::string_view name() const override;
    [[nodiscard]] bool is_unpacked() const override;

    [[nodiscard]] engine::GObjects gobjects() const override;
    [[nodiscard]] engine::GNames gnames() const override;
    [[nodiscard]] engine::GMalloc gmalloc() const override;

    [[nodiscard]] StaticFindObjectFn static_find_object() const override;
    [[nodiscard]] StaticLoadObjectFn static_load_object() const override;

   private:
    void find_globals() override;
    void apply_patches() const override;

    ue3::TArray<ue3::UObject*>* m_GObjects{nullptr};
    ue3::TArray<ue3::FNameEntry*>* m_GNames{nullptr};
    ue3::FMalloc** m_GMalloc{nullptr};
    void** m_GNatives{nullptr};
    StaticFindObjectFn m_StaticFindObject{nullptr};
    StaticLoadObjectFn m_StaticLoadObject{nullptr};
};

}  // namespace blcore::game::bl1

#endif  // BLCORE_GAME_BL1_GAME_IMPL_H
