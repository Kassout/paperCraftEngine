#ifndef PROJECTILELIFECYCLESYSTEM_H
#define PROJECTILELIFECYCLESYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/ProjectileComponent.h"

/// Class responsible to manage entity's projectile life cycle.
/// @file ProjectileLifeCycleSystem.h
/// @author Maxime Héliot
/// @version 0.1.0 19/10/2021
class ProjectileLifeCycleSystem: public System {
public:
    /// @brief Default ProjectileLifeCycleSystem constructor
    /// @details Base constructor of the ProjectileLifeCycleSystem class, defining the different required components an entity needs so the system can be interested in.
    ProjectileLifeCycleSystem() {
        RequireComponent<ProjectileComponent>();
    }

    /// @brief System update projectile life method
    /// @details This method is responsible for updating the entity's projectiles behaviour when called.
    void Update() {
        for (auto entity: GetSystemEntities()) {
            auto projectile = entity.GetComponent<ProjectileComponent>();

            // Kill projectiles after they reach their duration limit
            if (SDL_GetTicks() - projectile.startTime > projectile.duration) {
                entity.Kill();
            }
        }
    }
};

#endif // PROJECTILELIFECYCLESYSTEM_H //
