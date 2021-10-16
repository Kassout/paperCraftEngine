#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

/// Class responsible to compute collision detection of the interesting entities.
/// @file CollisionSystem.h
/// @author Maxime Héliot
/// @version 0.1.0 16/10/2021
class CollisionSystem: public System {
public:
    /// @brief Default CollisionSystem constructor
    /// @details Base constructor of the CollisionSystem class, defining the different required components an entity needs so the system can be interested in.
    CollisionSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<BoxColliderComponent>();
    }

    /// @brief System update collision method
    /// @details This method is responsible for checking entity collisions at any frame of the game and if any, trigger an event.
    void Update() {
        auto entities = GetSystemEntities();

        // Loop all the entities that the system is interested in
        for (auto i = entities.begin(); i != entities.end(); i++) {
            // Value the iterator pointer is pointing to
            Entity a = *i;
            auto aTransform = a.GetComponent<TransformComponent>();
            auto aCollider = a.GetComponent<BoxColliderComponent>();

            // Loop all the entities that still need to be checked (to the right of i)
            for (auto j = i+1; j != entities.end(); j++) {
                Entity b = *j;

                auto bTransform = b.GetComponent<TransformComponent>();
                auto bCollider = b.GetComponent<BoxColliderComponent>();

                // Check collision between a and b
                bool collisionHappened = CheckAABBCollision(aTransform.position.x + aCollider.offset.x,
                                                            aTransform.position.y + aCollider.offset.y,
                                                            aCollider.width, aCollider.height,
                                                            bTransform.position.x + bCollider.offset.x,
                                                            bTransform.position.y + bCollider.offset.y,
                                                            bCollider.width, bCollider.height);

                if (collisionHappened) {
                    Logger::Log("Entity " + std::to_string(a.GetId()) + " is colliding with entity " + std::to_string(b.GetId()));

                    // TODO: emit an event
                }
            }
        }
    }

private:
    /// @brief System check collision method
    /// @details This method is responsible for checking if two entities collides regarding their transform and box collider components.
    bool CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH) {
        return (aX < bX + bW &&
                aX + aW > bX &&
                aY < bY + bH &&
                aY + aH > bY
        );
    }
};

#endif // COLLISIONSYSTEM_H //
