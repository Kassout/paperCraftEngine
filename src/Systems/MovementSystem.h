#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"

/// Class responsible to move the entities it is linked to.
/// @file MovementSystem.h
/// @author Maxime Héliot
/// @version 0.1.0 12/10/2021
class MovementSystem: public System {
public:
    /// @brief Default MovementSystem constructor
    /// @details Base constructor of the MovementSystem class, defining the different required components an entity needs so the system can be interested in.
    MovementSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    /// @brief System update movement method
    /// @details This method is responsible for updating the position on all its entities when called.
    void Update(double deltaTime) {
        // Loop all entities that the system is interested in
        for (auto entity: GetSystemEntities()) {
            // Update entity position based on it's velocity
            auto& transform = entity.GetComponent<TransformComponent>();
            const auto rigidBody = entity.GetComponent<RigidBodyComponent>();

            transform.position.x += rigidBody.velocity.x * deltaTime;
            transform.position.y += rigidBody.velocity.y * deltaTime;
        }
    }
};

#endif /* MOVEMENTSYSTEM_H */
