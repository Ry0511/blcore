#ifndef BLCORE_GAME_GAME_H
#define BLCORE_GAME_GAME_H

#include "blcore/blcore.h"
#include "blcore/engine/gmalloc.h"
#include "blcore/engine/gnames.h"
#include "blcore/engine/gobjects.h"
#include "blcore/plugin/plugin_runtime.h"

namespace blcore::game {

struct EngineFunctions {
    void* static_find_object{nullptr};
    void* static_load_object{nullptr};
};

class Game {
   public:
    virtual ~Game() = default;

    void start(const fs::path& plugin_dir);
    void shutdown();

    [[nodiscard]] virtual std::string_view name() const = 0;
    [[nodiscard]] virtual bool is_unpacked() const = 0;

    [[nodiscard]] virtual engine::GObjects gobjects() const = 0;
    [[nodiscard]] virtual engine::GNames gnames() const = 0;
    [[nodiscard]] virtual engine::GMalloc gmalloc() const = 0;

    [[nodiscard]] virtual const EngineFunctions& engine_functions() const = 0;

   private:
    virtual void find_globals() = 0;
    virtual void apply_patches() const = 0;

    PluginRuntime m_Plugins;
};

Game& current();

}  // namespace blcore::game

#endif  // BLCORE_GAME_GAME_H
