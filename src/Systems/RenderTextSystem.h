#ifndef RENDERTEXTSYSTEM_H
#define RENDERTEXTSYSTEM_H

#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"
#include "../Components/TextLabelComponent.h"
#include <SDL.h>

/// Class responsible to process text label display to any entity its interested in.
/// @file RenderTextSystem.h
/// @author Maxime Héliot
/// @version 0.1.0 21/10/2021
class RenderTextSystem: public System {
public:
    /// @brief Default RenderTextSystem constructor
    /// @details Base constructor of the RenderTextSystem class, defining the different required components an entity needs so the system can be interested in.
    RenderTextSystem() {
        RequireComponent<TextLabelComponent>();
    }

    /// @brief System update text display method
    /// @details This method is responsible for managing text label render at any frame of the game.
    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, const SDL_Rect camera) {
        for (auto entity: GetSystemEntities()) {
            const auto textLabel = entity.GetComponent<TextLabelComponent>();

            SDL_Surface* surface = TTF_RenderText_Blended(assetStore->GetFont(textLabel.assetId), textLabel.text.c_str(), textLabel.color);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            int labelWidth = 0;
            int labelHeight = 0;

            SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

            SDL_Rect dstRect = {
                    static_cast<int>(textLabel.position.x - (textLabel.isFixed ? 0 : camera.x)),
                    static_cast<int>(textLabel.position.y - (textLabel.isFixed ? 0 : camera.y)),
                    labelWidth,
                    labelHeight
            };

            SDL_RenderCopy(renderer, texture, NULL, &dstRect);

            SDL_DestroyTexture(texture);
        }
    }
};

#endif // RENDERTEXTSYSTEM_H //
