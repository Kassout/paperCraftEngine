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
    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, SDL_Rect& camera) {
        // Create a vector with both Sprite and Transform component of all entities
        struct RenderableEntity {
            TransformComponent transformComponent;
            SpriteComponent spriteComponent;
        };
        std::vector<RenderableEntity> renderableEntities;
        for (auto entity: GetSystemEntities()) {
            RenderableEntity renderableEntity;
            renderableEntity.spriteComponent = entity.GetComponent<SpriteComponent>();
            renderableEntity.transformComponent = entity.GetComponent<TransformComponent>();

            // Bypass rendering entities if they're outside the camera view
            bool isEntityOutsideCameraView = (
                    renderableEntity.transformComponent.position.x + (renderableEntity.spriteComponent.width * renderableEntity.transformComponent.scale.x) < camera.x ||
                    renderableEntity.transformComponent.position.x > camera.x + camera.w ||
                    renderableEntity.transformComponent.position.y + (renderableEntity.spriteComponent.height * renderableEntity.transformComponent.scale.y) < camera.y ||
                    renderableEntity.transformComponent.position.y > camera.y + camera.h
                    );

            // Cull sprites that are outside the camera view (and are not fixed)
            if (isEntityOutsideCameraView && !renderableEntity.spriteComponent.isFixed) {
                continue;
            }

            renderableEntities.emplace_back(renderableEntity);
        }

        // Sort the vector by the z-index value
        std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity& a, const RenderableEntity& b) -> bool {
            return a.spriteComponent.layerIndex < b.spriteComponent.layerIndex;
        });

        // Loop all entities that the system is interested in
        for (auto entity: renderableEntities) {
            const auto transform = entity.transformComponent;
            const auto sprite = entity.spriteComponent;

            // Set the source rectangle of our original sprite texture
            SDL_Rect srcRect = sprite.srcRect;

            // Set the destination rectangle with the x, y position to be rendered
            SDL_Rect dstRect = {
                    static_cast<int>(transform.position.x - (sprite.isFixed ? 0 : camera.x)),
                    static_cast<int>(transform.position.y - (sprite.isFixed ? 0 : camera.y)),
                    static_cast<int>(sprite.width * transform.scale.x),
                    static_cast<int>(sprite.height * transform.scale.y)
            };

            SDL_RenderCopyEx(renderer,
                           assetStore->GetTexture(sprite.assetId), &srcRect, &dstRect, transform.rotation.x, NULL, sprite.flip);
        }
    }
};

#endif // RENDERSYSTEM_H //