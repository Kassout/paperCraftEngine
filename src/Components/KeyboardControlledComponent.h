#ifndef KEYBOARDCONTROLLEDCOMPONENT_H
#define KEYBOARDCONTROLLEDCOMPONENT_H

#include <glm/glm.hpp>

/// Structure responsible for holding the data linked to the keyboard controls of the entity.
/// @file KeyboardControlledComponent.h
/// @author Maxime Héliot
/// @version 0.1.0 18/10/2021
struct KeyboardControlledComponent {
    /// Vector object representing the up velocity of the keyboard controlled entity.
    glm::vec2 upVelocity;
    /// Vector object representing the right velocity of the keyboard controlled entity.
    glm::vec2 rightVelocity;
    /// Vector object representing the down velocity of the keyboard controlled entity.
    glm::vec2 downVelocity;
    /// Vector object representing the left velocity of the keyboard controlled entity.
    glm::vec2 leftVelocity;

    /// @brief Default KeyboardControlledComponent constructor
    /// @details Base constructor of the KeyboardControlledComponent class taking base values for the different class attributes as parameters.
    KeyboardControlledComponent(glm::vec2 upVelocity = glm::vec2(0), glm::vec2 rightVelocity = glm::vec2(0),
                                glm::vec2 downVelocity = glm::vec2(0), glm::vec2 leftVelocity = glm::vec2(0)) :
                                upVelocity(upVelocity), rightVelocity(rightVelocity), downVelocity(downVelocity),
                                leftVelocity(leftVelocity) {}
};

#endif // KEYBOARDCONTROLLEDCOMPONENT_H //
