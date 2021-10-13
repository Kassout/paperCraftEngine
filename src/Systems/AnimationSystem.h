#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"

/// Class responsible to animate entities.
/// @file AnimationSystem.h
/// @author Maxime Héliot
/// @version 0.1.0 13/10/2021
class AnimationSystem: public System {
public:
    /// @brief Default AnimationSystem constructor
    /// @details Base constructor of the AnimationSystem class, defining the different required components an entity needs so the system can be interested in.
    AnimationSystem() {
        RequireComponent<AnimationComponent>();
        RequireComponent<SpriteComponent>();
    }

    /// @brief System update animation method
    /// @details This method is responsible for updating the animation frame on all its entities when called.
    void Update() {
        for (auto entity: GetSystemEntities()) {
            auto& animation = entity.GetComponent<AnimationComponent>();
            auto& sprite = entity.GetComponent<SpriteComponent>();

            animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameSpeedRate / 1000) % animation.numFrames;
            sprite.srcRect.x = animation.currentFrame * sprite.width;
        }
    }
};

#endif // ANIMATIONSYSTEM_H //
