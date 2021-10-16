#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include <glm/glm.hpp>

/// Structure responsible for holding the data linked to the collision box of the entity.
/// @file BoxColliderComponent.h
/// @author Maxime Héliot
/// @version 0.1.0 16/10/2021
struct BoxColliderComponent {
    /// Integer value representing the width of the box collider.
    int width;
    /// Integer value representing the height of the box collider.
    int height;
    /// Vector2 object containing the offset values of the box collider position.
    glm::vec2 offset;

    /// @brief Default BoxColliderComponent constructor
    /// @details Base constructor of the BoxColliderComponent class taking the width, height and offset vector values of the box collider as parameters.
    BoxColliderComponent(int width = 0, int height = 0, glm::vec2 offset = glm::vec2(0)) :
    width(width), height(height), offset(offset) {}
};

#endif /* BOXCOLLIDERCOMPONENT_H */
