#ifndef PROJECTILECOMPONENT_H
#define PROJECTILECOMPONENT_H

#include <SDL.h>

/// Structure responsible for holding the data linked to the projectile of an entity.
/// @file ProjectileComponent.h
/// @author Maxime Héliot
/// @version 0.1.0 18/10/2021
struct ProjectileComponent {
    /// Boolean value representing the friendly status of the projectile entity.
    bool isFriendly;
    /// Integer value representing the damage, in percentage, dealt by the projectile entity.
    int hitPercentDamage;
    /// Integer value representing the life duration, in milliseconds, of the projectile entity.
    int duration;
    /// Integer value representing the instantiation time since the last tick, in milliseconds, of the projectile entity.
    int startTime;

    /// @brief Default ProjectileComponent constructor
    /// @details Base constructor of the ProjectileComponent class taking base values for the different class attributes as parameters.
    ProjectileComponent(bool isFriendly = false, int hitPercentDamage = 0, int duration = 0):
                        isFriendly(isFriendly), hitPercentDamage(hitPercentDamage), duration(duration){
        this->startTime = SDL_GetTicks();
    }
};

#endif // PROJECTILECOMPONENT_H //
