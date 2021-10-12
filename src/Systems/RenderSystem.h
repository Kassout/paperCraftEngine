#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include <SDL.h>

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
    void Update(SDL_Renderer* renderer) {
        // Loop all entities that the system is interested in
        for (auto entity: GetSystemEntities()) {
            const auto transform = entity.GetComponent<TransformComponent>();
            const auto sprite = entity.GetComponent<SpriteComponent>();

            SDL_Rect objRect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    sprite.width,
                    sprite.height
            };
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &objRect);
        }
    }
};

#endif // RENDERSYSTEM_H //