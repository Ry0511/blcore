#ifndef BLCORE_GAME_GAME_H
#define BLCORE_GAME_GAME_H

#include "blcore/blcore.h"
#include "blcore/plugin/plugin_runtime.h"
#include "blcore/ue3/fwd.h"
#include "blcore/ue3/tarray.h"

namespace blcore::game {

struct Globals {
    ue3::TArray<ue3::UObject*>* gobjects{nullptr};
    ue3::TArray<ue3::FNameEntry*>* gnames{nullptr};
    void** gmalloc{nullptr};
    void** gnatives{nullptr};
};

class Game {
   public:
    virtual ~Game() = default;

    void start(const fs::path& plugin_dir);
    void shutdown();

    [[nodiscard]] const Globals& globals() const;
    [[nodiscard]] virtual std::string_view name() const = 0;
    [[nodiscard]] virtual bool is_unpacked() const = 0;

    virtual void* malloc(void* gmalloc, size_t size, uint32_t alignment) const = 0;
    virtual void* realloc(void* gmalloc, void* original, size_t size, uint32_t alignment) const = 0;
    virtual void free(void* gmalloc, void* data) const = 0;

   private:
    virtual void find_globals(Globals& out) const = 0;
    virtual void apply_patches() const = 0;

    Globals m_Globals;
    PluginRuntime m_Plugins;
};

Game& current();

}  // namespace blcore::game

#endif  // BLCORE_GAME_GAME_H
