#ifndef KEYBOARDMOVEMENTSYSTEM_H
#define KEYBOARDMOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/SpriteComponent.h"
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
        std::string keyCode = std::to_string(event.symbol);
        std::string keySymbol(1, event.symbol);
        Logger::Log("Key pressed event emitted: [" + keyCode + "] " + keySymbol);
    }

    /// @brief System update control method
    /// @details This method is responsible for managing entity controls received at any frame of the game.
    void Update() {
        // TODO: ...
    }
};

#endif // KEYBOARDMOVEMENTSYSTEM_H //
