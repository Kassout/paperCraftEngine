#ifndef RENDERCOLLIDERSYSTEM_H
#define RENDERCOLLIDERSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

/// Class responsible to render collider bounds of entities.
/// @file RenderColliderSystem.h
/// @author Maxime Héliot
/// @version 0.1.0 16/10/2021
class RenderColliderSystem: public System {
public:
    /// @brief Default RenderColliderSystem constructor
    /// @details Base constructor of the RenderColliderSystem class, defining the different required components an entity needs so the system can be interested in.
    RenderColliderSystem() {
        RequireComponent<BoxColliderComponent>();
        RequireComponent<TransformComponent>();
    }

    /// @brief System update render collider method
    /// @details This method is responsible for updating the collider render on all its interested entities when called.
    void Update(SDL_Renderer* renderer, SDL_Rect& camera) {
        for (auto entity: GetSystemEntities())
        {
            const auto transform = entity.GetComponent<TransformComponent>();
            const auto collider = entity.GetComponent<BoxColliderComponent>();

            SDL_Rect colliderRect = {
                    static_cast<int>(transform.position.x + collider.offset.x - camera.x),
                    static_cast<int>(transform.position.y + collider.offset.y - camera.y),
                    static_cast<int>(collider.width * transform.scale.x),
                    static_cast<int>(collider.height * transform.scale.y)
            };

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &colliderRect);
        }
    }
};

#endif // RENDERCOLLIDERSYSTEM_H //
