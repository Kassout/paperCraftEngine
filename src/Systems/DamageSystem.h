#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/HealthComponent.h"
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
        Entity a = event.a;
        Entity b = event.b;

        if (a.BelongsToGroup("projectiles") && b.HasTag("player")) {
            OnProjectileHitsPlayer(a, b); // "a" is the projectile, "b" is the player
        }

        if (b.BelongsToGroup("projectiles") && a.HasTag("player")) {
            OnProjectileHitsPlayer(b, a); // "b" is the projectile, "a" is the player
        }

        if (a.BelongsToGroup("projectiles") && b.BelongsToGroup("enemies")) {
            OnProjectileHitsEnemy(a, b);
        }

        if (b.BelongsToGroup("projectiles") && a.BelongsToGroup("enemies")) {
            OnProjectileHitsEnemy(b, a);
        }
    }

    /// @brief Action triggered on projectile hits player
    /// @details This method is responsible for handling the actions related to an on collision event notification between the player and a projectile.
    /// @param player: The player entity object.
    /// @param projectile: The projectile entity object.
    void OnProjectileHitsPlayer(Entity projectile, Entity player) {
        auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

        if (!projectileComponent.isFriendly) {
            // Reduce the health of the player by the projectile hitPercentDamage
            auto health = player.GetComponent<HealthComponent>();

            health.healthPercentage -= projectileComponent.hitPercentDamage;

            // Kills the player when health reaches zero
            if (health.healthPercentage <= 0) {
                player.Kill();
            }

            // Kill the projectile
            projectile.Kill();
        }
    }

    /// @brief Action triggered on projectile hits enemy
    /// @details This method is responsible for handling the actions related to an on collision event notification between an enemy and a projectile.
    /// @param enemy: The enemy entity object.
    /// @param projectile: The projectile entity object.
    void OnProjectileHitsEnemy(Entity projectile, Entity enemy) {
        const auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

        if (projectileComponent.isFriendly) {
            // Reduce the health of the enemy by the projectile hitPercentDamage
            auto& health = enemy.GetComponent<HealthComponent>();

            health.healthPercentage -= projectileComponent.hitPercentDamage;

            // Kills the enemy when health reaches zero
            if (health.healthPercentage <= 0) {
                enemy.Kill();
            }

            // Kill the projectile
            projectile.Kill();
        }
    }
};

#endif /* DAMAGESYSTEM_H */
