#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

/// Class responsible for managing all type of assets and store them.
/// @file AssetStore.h
/// @author Maxime Héliot
/// @version 0.1.0 12/10/2021
class AssetStore {
private:
    /// A map of the different game sprites - textures
    std::map<std::string, SDL_Texture*> textures;
    // A map of the different game fonts
    std::map<std::string, TTF_Font*> fonts;
    // TODO: create a map for audio

public:
    /// @brief Default AssetStore constructor
    /// @details Base constructor of the AssetStore class.
    AssetStore();

    /// @brief Default AssetStore destructor
    /// @details Base destructor of the AssetStore class.
    ~AssetStore();

    /// @brief Clear asset type maps
    /// @details This method is responsible for clear all the different assets of all the asset maps type.
    void ClearAssets();

    /// @brief Add texture type asset
    /// @details This method is responsible for adding a texture to the asset store.
    void AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath);

    /// @brief Texture asset getter by id
    /// @details This method is responsible for returning the texture associated to a given id in the texture assets map.
    SDL_Texture* GetTexture(const std::string& assetId);

    /// @brief Add font type asset
    /// @details This method is responsible for adding a font to the asset store.
    void AddFont(const std::string& assetId, const std::string& filePath, int fontSize);

    /// @brief Font asset getter by id
    /// @details This method is responsible for returning the font associated to a given id in the font assets map.
    TTF_Font* GetFont(const std::string& assetId);
};

#endif // ASSETSTORE_H //
