#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

/// Class responsible for holding the data linked to the transform on an entity.
/// @file TransformComponent.h
/// @author Maxime Héliot
/// @version 0.1.0 11/10/2021
struct TransformComponent {
    /// Vector2 object representing the position values of the entity along the different world axes.
    glm::vec2 position;
    /// Vector2 object representing the scale values of the entity in the different world axes.
    glm::vec2 scale;
    /// Vector2 object representing the rotation values of the entity around the different world axes.
    glm::vec2 rotation;

    /// @brief Default TransformComponent constructor
    /// @details Base constructor of the TransformComponent class taking base values for the different attributes as parameters.
    TransformComponent(glm::vec2 position = glm::vec2(0.0, 0.0),
                       glm::vec2 scale = glm::vec2(1.0, 1.0),
                       glm::vec2 rotation = glm::vec2(0.0, 0.0)) :
                       position(position), scale(scale), rotation(rotation) {}
};

#endif // TRANSFORMCOMPONENT_H //