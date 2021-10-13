#ifndef GAME_H
#define GAME_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include <SDL.h>

/// Expected frame per seconds value.
const int FPS = 60;

/// Computed expected time between two frames for a given number of frame per seconds.
const int MILLISECS_PER_FRAME = 1000 / FPS;

/// Class responsible for calling all of our game code and keeping the game running.
/// @file Game.h
/// @author Maxime Héliot
/// @version 0.1.0 07/10/2021
class Game {
private:
    /// Game running status indicator.
    bool isRunning;
    /// Time elapsed since last game frame.
    int millisecsPreviousFrame = 0;
    /// Window object to display render buffers.
    SDL_Window* window;
    /// Renderer object to draw texture.
    SDL_Renderer* renderer;
    /// Registry object of the game.
    std::unique_ptr<Registry> registry; // Registry* registry smart pointer
    /// Asset store of the game.
    std::unique_ptr<AssetStore> assetStore;

public:
    /// Game window width value.
    int windowWidth;
    /// Game window height value.
    int windowHeight;

    /// @brief Default constructor
    /// @details Base constructor of the Game class.
    Game();

    /// @brief Default destructor
    /// @details Base destructor of the Game class.
    ~Game();

    /// @brief Default constructor
    /// @details Base constructor of the Game class.
    void Initialize();

    /// @brief Default constructor
    /// @details Base constructor of the Game class.
    void Run();

    /// @brief Game setup method
    /// @details This method is responsible for building the different static and default elements of the game at run.
    void Setup();

    /// @brief Game load level method
    /// @details This method is responsible for loading the different element constituting of the targeted level.
    /// @param level: Integer value representing the index of the level scene to load.
    void LoadLevel(int level);

    /// @brief Game process input method
    /// @details This method is responsible for building the different static and default elements of the game at run.
    void ProcessInput();

    /// @brief Game update method
    /// @details This method is responsible for processing the different actions - systems of the game at every frame.
    void Update();

    /// @brief Game render method
    /// @details This method is responsible for rendering all the entity of the game at every frame.
    void Render();

    /// @brief Game destroy method
    /// @details This method is responsible for cleaning the screen and clearing all the different elements constituting of the game.
    void Destroy();
};

#endif // GAME_H //
