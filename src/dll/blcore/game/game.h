#ifndef BLCORE_GAME_GAME_H
#define BLCORE_GAME_GAME_H

#include "blcore/blcore.h"
#include "blcore/plugin/plugin_runtime.h"

namespace blcore::game {

struct AddressTable {
    void* gobjects{nullptr};
    void* gnames{nullptr};
    void* gmalloc{nullptr};
    void* gnatives{nullptr};
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

    [[nodiscard]] virtual const AddressTable& address_table() const = 0;

   private:
    virtual void initialise() = 0;

    PluginRuntime m_Plugins;
};

Game& current();

}  // namespace blcore::game

#endif  // BLCORE_GAME_GAME_H
