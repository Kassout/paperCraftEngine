#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include <SDL.h>
#include <sol/sol.hpp>
#include <memory>

/// TODO: comments
class LevelLoader {
public:
    /// TODO: comments
    LevelLoader();

    /// TODO: comments
    ~LevelLoader();

    /// @brief Load level method
    /// @details This method is responsible for loading the different element constituting of the targeted level.
    /// @param level: Integer value representing the index of the level scene to load.
    void LoadLevel(sol::state& lua, const std::unique_ptr<Registry>& registry, const std::unique_ptr<AssetStore>& assetStore, SDL_Renderer* renderer, int levelNumber);
};

#endif // LEVELLOADER_H //
