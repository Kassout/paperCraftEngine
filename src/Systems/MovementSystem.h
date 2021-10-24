#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"

/// Class responsible to move the entities it is linked to.
/// @file MovementSystem.h
/// @author Maxime Héliot
/// @version 0.2.0 24/10/2021
class MovementSystem: public System {
public:
    /// @brief Default MovementSystem constructor
    /// @details Base constructor of the MovementSystem class, defining the different required components an entity needs so the system can be interested in.
    MovementSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    /// TODO: comments
    void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
        eventBus->SubscribeEvent<CollisionEvent>(this, &MovementSystem::OnCollision);
    }

    /// TODO: comments
    void OnCollision(CollisionEvent& event) {
        Entity a = event.a;
        Entity b = event.b;

        Logger::Log("Collision event emitted: " + std::to_string(a.GetId()) + " and " + std::to_string(b.GetId()));

        if (a.BelongsToGroup("enemies") && b.BelongsToGroup("obstacles")) {
            OnEnemyHitsObstacle(a, b); // "a" is the enemy, "b" is the obstacle
        }

        if (a.BelongsToGroup("obstacles") && b.BelongsToGroup("enemies")) {
            OnEnemyHitsObstacle(a, b); // "a" is the obstacle, "b" is the enemie
        }
    }

    /// TODO: comments
    void OnEnemyHitsObstacle(Entity enemy, Entity obstacle) {
        if (enemy.HasComponent<RigidBodyComponent>() && enemy.HasComponent<SpriteComponent>()) {
            auto& rigidBody = enemy.GetComponent<RigidBodyComponent>();
            auto& sprite = enemy.GetComponent<SpriteComponent>();

            if (rigidBody.velocity.x != 0) {
                rigidBody.velocity.x *= -1;
                sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            }

            if (rigidBody.velocity.y != 0) {
                rigidBody.velocity.y *= -1;
                sprite.flip = (sprite.flip == SDL_FLIP_NONE) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
            }
        }
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

            // Prevent the main player from moving outside the map boundaries
            if (entity.HasTag("player")) {
                int paddingLeft = 10;
                int paddingTop = 10;
                int paddingRight = 50;
                int paddingBottom = 50;
                transform.position.x = transform.position.x < paddingLeft ? paddingLeft : transform.position.x;
                transform.position.x = transform.position.x > Game::mapWidth - paddingRight ? Game::mapWidth - paddingRight : transform.position.x;
                transform.position.y = transform.position.y < paddingTop ? paddingTop : transform.position.y;
                transform.position.y = transform.position.y > Game::mapHeight - paddingBottom ? Game::mapHeight - paddingBottom : transform.position.y;
            }

            // Check if entity is outside the map boundaries (with a 100 pixels forgiving margin)
            int margin = 100;

            bool isEntityOutsideMap = (
                    transform.position.x < -margin ||
                    transform.position.x > Game::windowWidth + margin ||
                    transform.position.y < -margin ||
                    transform.position.y > Game::windowHeight + margin);

            // Kill all entities that move outside the map boundaries
            if (isEntityOutsideMap && !entity.HasTag("player")) {
                entity.Kill();
            }
        }
    }
};

#endif /* MOVEMENTSYSTEM_H */
