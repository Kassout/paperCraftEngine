#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

/// Structure responsible for holding the data linked to the sprite rendering of an entity.
/// @file SpriteComponent.h
/// @author Maxime Héliot
/// @version 0.1.0 12/10/2021
struct SpriteComponent {
    /// Integer value representing the width of the sprite to render.
    int width;
    /// Integer value representing the height of the sprite to render.
    int height;

    /// @brief Default SpriteComponent constructor
    /// @details Base constructor of the SpriteComponent class taking width and height integer values as parameters.
    SpriteComponent(int width = 0, int height = 0) : width(width), height(height) {}
};

#endif // SPRITECOMPONENT_H //
