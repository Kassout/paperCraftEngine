#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Game/Game.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"
#include <SDL.h>

/// Class responsible to move the camera.
/// @file CameraMovementSystem.h
/// @author Maxime Héliot
/// @version 0.1.0 19/10/2021
class CameraMovementSystem: public System {
public:
    /// @brief Default CameraMovementSystem constructor
    /// @details Base constructor of the CameraMovementSystem class, defining the different required components an entity needs so the system can be interested in.
    CameraMovementSystem() {
        RequireComponent<CameraFollowComponent>();
        RequireComponent<TransformComponent>();
    }

    /// @brief System update camera position method
    /// @details This method is responsible for updating the camera canvas transform on all its entities when called.
    void Update(SDL_Rect& camera) {
        for (auto entity: GetSystemEntities()) {
            auto transform = entity.GetComponent<TransformComponent>();

            if (transform.position.x + (camera.w / 2) < Game::mapWidth) {
                camera.x = transform.position.x - (Game::windowWidth / 2);
            }
            if (transform.position.y + (camera.h / 2) < Game::mapHeight) {
                camera.y = transform.position.y - (Game::windowHeight / 2);
            }

            // Keep the camera rectangle view inside the screen limits
            camera.x = camera.x < 0 ? 0 : camera.x;
            camera.y = camera.y < 0 ? 0 : camera.y;
            camera.x = camera.x > camera.w ? camera.w : camera.x;
            camera.y = camera.y > camera.h ? camera.h : camera.y;
        }
    }

private:
};

#endif // CAMERAMOVEMENTSYSTEM_H //
