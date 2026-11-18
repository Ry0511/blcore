#include "blcore/pch.h"

#include "blcore/game/game.h"
#include "blcore/util/logging.h"

namespace blcore::game {

void Game::start(const fs::path& plugin_dir) {
    BLCORE_INFO("Starting for {}", name());
    initialise();
    m_Plugins.load(plugin_dir);
}

void Game::shutdown() {
    m_Plugins.shutdown();
}

}  // namespace blcore::game
