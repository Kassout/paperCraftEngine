#ifndef TEXTLABELCOMPONENT_H
#define TEXTLABELCOMPONENT_H

#include <glm/glm.hpp>
#include <SDL.h>

/// Structure responsible for holding the data linked to text labels display.
/// @file TextLabelComponent.h
/// @author Maxime Héliot
/// @version 0.1.0 21/10/2021
struct TextLabelComponent {
    /// Vector object representing the position of the text label.
    glm::vec2 position;

    /// String object representing the core text to display of the text label.
    std::string text;

    /// String object representing the asset id of the text font.
    std::string assetId;

    /// SDL_Color object representing the color of the text to display.
    SDL_Color color;

    /// Boolean value representing the fixed position status of the text label.
    bool isFixed;

    /// @brief Default TextLabelComponent constructor
    /// @details Base constructor of the TextLabelComponent class taking base values for the different class attributes as parameters.
    TextLabelComponent(glm::vec2 position = glm::vec2(0), std::string text = "" , std::string assetId = "",
                       const SDL_Color& color = {0, 0, 0}, bool isFixed = true): position(position),
                       text(text), assetId(assetId), color(color), isFixed(isFixed) {}


};

#endif // TEXTLABELCOMPONENT_H //
