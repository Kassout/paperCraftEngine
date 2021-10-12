#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>

/// Structure responsible for holding the data linked to the rigid body of the entity.
/// @file RigidBodyComponent.h
/// @author Maxime Héliot
/// @version 0.1.0 11/10/2021
struct RigidBodyComponent {
    /// Vector2 object representing the velocity values of the entity along the different world axes.
    glm::vec2 velocity;

    /// @brief Default RigidBodyComponent constructor
    /// @details Base constructor of the RigidBodyComponent class taking a velocity vector as parameter.
    RigidBodyComponent(glm::vec2 velocity = glm::vec2(0.0, 0.0)) : velocity(velocity) {}
};

#endif // RIGIDBODYCOMPONENT_H //
