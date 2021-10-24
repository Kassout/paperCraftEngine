#ifndef KEYBOARDMOVEMENTSYSTEM_H
#define KEYBOARDMOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/SpriteComponent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"

/// Class responsible to process actions related to key pressed events for every interested entity.
/// @file KeyboardControlSystem.h
/// @author Maxime Héliot
/// @version 0.1.0 16/10/2021
class KeyboardControlSystem: public System {
public:
    /// @brief Default KeyboardControlSystem constructor
    /// @details Base constructor of the KeyboardControlSystem class, defining the different required components an entity needs so the system can be interested in.
    KeyboardControlSystem() {
        RequireComponent<KeyboardControlledComponent>();
        RequireComponent<SpriteComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    /// @brief Event subscribing method
    /// @details This method is responsible for subscribing the class to its interested events.
    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
        eventBus->SubscribeEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyPressed);
    }

    /// @brief On key pressed event handler
    /// @details This method is responsible for handling the actions related to a keyboard key pressed event notification.
    void OnKeyPressed(KeyPressedEvent& event) {
        for (auto entity: GetSystemEntities()) {
            const auto keyboardControl = entity.GetComponent<KeyboardControlledComponent>();
            auto& sprite = entity.GetComponent<SpriteComponent>();
            auto& rigidBody = entity.GetComponent<RigidBodyComponent>();

            switch (event.symbol) {
                case SDLK_UP:
                    rigidBody.velocity = keyboardControl.upVelocity;
                    sprite.srcRect.y = sprite.height * 0;
                    break;
                case SDLK_RIGHT:
                    rigidBody.velocity = keyboardControl.rightVelocity;
                    sprite.srcRect.y = sprite.height * 1;
                    break;
                case SDLK_DOWN:
                    rigidBody.velocity = keyboardControl.downVelocity;
                    sprite.srcRect.y = sprite.height * 2;
                    break;
                case SDLK_LEFT:
                    rigidBody.velocity = keyboardControl.leftVelocity;
                    sprite.srcRect.y = sprite.height * 3;
                    break;
            }
        }
    }
};

#endif // KEYBOARDMOVEMENTSYSTEM_H //
