#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include <SDL.h>
#include <glm/glm.hpp>

/// Structure responsible for holding the data linked to the projectile emitter of an entity.
/// @file ProjectileEmitterComponent.h
/// @author Maxime Héliot
/// @version 0.1.0 18/10/2021
struct ProjectileEmitterComponent {
    /// Vector object representing the velocity of the projectile emitted by the entity.
    glm::vec2 projectileVelocity;
    /// Integer value representing the fire rate, in milliseconds between 2 shots, of the projectile emitter entity.
    int repeatFrequency;
    /// Integer value representing the life duration, in milliseconds, of the projectile emitted by the entity.
    int projectileDuration;
    /// Integer value representing the damage, in percentage, dealt by the projectile emitted by the entity.
    int hitPercentDamage;
    /// Boolean value representing the friendly status of the projectile emitted by entity.
    bool isFriendly;
    /// Integer value representing the time since the last tick, in milliseconds, of the last projectile emission of the emitter.
    int lastEmissionTime;

    /// @brief Default ProjectileEmitterComponent constructor
    /// @details Base constructor of the ProjectileEmitterComponent class taking base values for the different class attributes as parameters.
    ProjectileEmitterComponent(glm::vec2 projectileVelocity = glm::vec2(0), int repeatFrequency = 0,
                               int projectileDuration = 10000, int hitPercentDamage = 10, bool isFriendly = false):
                               projectileVelocity(projectileVelocity), repeatFrequency(repeatFrequency),
                               projectileDuration(projectileDuration), hitPercentDamage(hitPercentDamage),
                               isFriendly(isFriendly) {
        this->lastEmissionTime = SDL_GetTicks();
    }
};

#endif // PROJECTILEEMITTERCOMPONENT_H //
