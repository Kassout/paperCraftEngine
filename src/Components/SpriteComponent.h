#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>

/// Structure responsible for holding the data linked to the sprite rendering of an entity.
/// @file SpriteComponent.h
/// @author Maxime Héliot
/// @version 0.1.0 12/10/2021
struct SpriteComponent {
    /// String object representing the id of the asset.
    std::string assetId;
    /// Integer value representing the width of the sprite to render.
    int width;
    /// Integer value representing the height of the sprite to render.
    int height;
    /// Integer value representing the sorting z layer index to render the sprite on.
    int layerIndex;
    /// SDL_Rect object representing the definition of the rectangle containing the sprite to render.
    SDL_Rect srcRect;

    /// @brief Default SpriteComponent constructor
    /// @details Base constructor of the SpriteComponent class taking base values for the different class attributes as parameters.
    SpriteComponent(std::string assetId = "", int width = 0, int height = 0, int layerIndex = 0, int srcRectX = 0, int srcRectY = 0) :
    assetId(assetId), width(width), height(height), layerIndex(layerIndex) {
        this->srcRect = {srcRectX, srcRectY, width, height};
    }
};

#endif // SPRITECOMPONENT_H //
