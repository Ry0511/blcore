#ifndef BLCORE_GAME_GAME_H
#define BLCORE_GAME_GAME_H

#include "blcore/blcore.h"
#include "blcore/engine/gmalloc.h"
#include "blcore/engine/gnames.h"
#include "blcore/engine/gobjects.h"
#include "blcore/plugin/plugin_runtime.h"
#include "blcore/ue3/mapping/fwd.h"

namespace blcore::game {

class Game {
   public:
    using StaticFindObjectFn = ue3::UObject*(__cdecl*)(ue3::UClass*, ue3::UObject*, const wchar_t*, uint32_t);

    virtual ~Game() = default;

    void start(const fs::path& plugin_dir);
    void shutdown();

    [[nodiscard]] virtual std::string_view name() const = 0;
    [[nodiscard]] virtual bool is_unpacked() const = 0;

    [[nodiscard]] virtual engine::GObjects gobjects() const = 0;
    [[nodiscard]] virtual engine::GNames gnames() const = 0;
    [[nodiscard]] virtual engine::GMalloc gmalloc() const = 0;

    [[nodiscard]] virtual StaticFindObjectFn static_find_object() const = 0;

   private:
    virtual void find_globals() = 0;
    virtual void apply_patches() const = 0;

    PluginRuntime m_Plugins;
};

Game& current();

}  // namespace blcore::game

#endif  // BLCORE_GAME_GAME_H
