#ifndef COLLISIONEVENTS_H
#define COLLISIONEVENTS_H

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

/// Class responsible of handling all the collision event notifications.
/// @file CollisionEvent.h
/// @author Maxime Héliot
/// @version 0.1.0 16/10/2021
class CollisionEvent: public Event {
public:
    /// Entity object representing the first colliding entity.
    Entity a;
    /// Entity object representing the second colliding entity.
    Entity b;

    /// @brief Default CollisionEvent constructor
    /// @details Base constructor of the CollisionEvent class taking base values for the different class attributes as parameters.
    CollisionEvent(Entity a, Entity b): a(a), b(b) {}
};

#endif // COLLISIONEVENTS_H //
