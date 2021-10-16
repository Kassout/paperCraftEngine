#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

/// Class responsible to process damage received to any entity its interested in.
/// @file DamageSystem.h
/// @author Maxime Héliot
/// @version 0.1.0 16/10/2021
class DamageSystem: public System {
public:
    /// @brief Default DamageSystem constructor
    /// @details Base constructor of the DamageSystem class, defining the different required components an entity needs so the system can be interested in.
    DamageSystem() {
        RequireComponent<BoxColliderComponent>();
    }

    /// @brief Event subscribing method
    /// @details This method is responsible for subscribing the class to its interested events.
    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
        eventBus->SubscribeEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
    }

    /// @brief On collision event handler
    /// @details This method is responsible for handling the actions related to an on collision event notification.
    void OnCollision(CollisionEvent& event) {
        Logger::Log("The damage system received an event collision between entities " + std::to_string(event.a.GetId()) + " and " + std::to_string(event.b.GetId()));
        event.a.Kill();
        event.b.Kill();
    }

    /// @brief System update damage method
    /// @details This method is responsible for managing entity health and damage received at any frame of the game.
    void Update() {
        // TODO: ...
    }
};

#endif /* DAMAGESYSTEM_H */
