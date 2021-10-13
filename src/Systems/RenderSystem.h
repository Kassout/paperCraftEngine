#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../AssetStore/AssetStore.h"
#include <SDL.h>
#include <algorithm>

/// Class responsible to render and display the entities on the screen.
/// @file RenderSystem.h
/// @author Maxime Héliot
/// @version 0.1.0 12/10/2021
class RenderSystem: public System {
public:
    /// @brief Default RenderSystem constructor
    /// @details Base constructor of the RenderSystem class, defining the different required components an entity needs so the system can be interested in.
    RenderSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    }

    /// @brief System update render method
    /// @details This method is responsible for updating the render on all its entities when called.
    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore) {
        // Sort the vector by the z-index value
        std::vector<Entity> layer_sorted_entities = GetSystemEntities();
        std::sort(layer_sorted_entities.begin(), layer_sorted_entities.end(), [](const Entity& a, const Entity& b) -> bool {
            return a.GetComponent<SpriteComponent>().layerIndex < b.GetComponent<SpriteComponent>().layerIndex;
        });

        // Loop all entities that the system is interested in
        for (auto entity: GetSystemEntities()) {
            const auto transform = entity.GetComponent<TransformComponent>();
            const auto sprite = entity.GetComponent<SpriteComponent>();

            // Set the source rectangle of our original sprite texture
            SDL_Rect srcRect = sprite.srcRect;

            // Set the destination rectangle with the x, y position to be rendered
            SDL_Rect dstRect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    static_cast<int>(sprite.width * transform.scale.x),
                    static_cast<int>(sprite.height * transform.scale.y)
            };

            SDL_RenderCopyEx(renderer,
                           assetStore->GetTexture(sprite.assetId), &srcRect, &dstRect, transform.rotation.x, NULL, SDL_FLIP_NONE);

            // TODO: Draw the PNG texture
        }
    }
};

#endif // RENDERSYSTEM_H //