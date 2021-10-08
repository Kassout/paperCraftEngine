#ifndef GAME_H
#define GAME_H

#include <SDL.h>

/// Expected frame per seconds value.
const int FPS = 60;

/// Computed expected time between two frames for a given number of frame per seconds.
const int MILLISECS_PER_FRAME = 1000 / FPS;

/// Class responsible for calling all of our game code and keeping the game running.
/// @file Game.h
/// @author Maxime Héliot
/// @version 0.1.0 07/10/2021
class Game
{
private:
    /// Game running status indicator.
    bool isRunning;
    /// Time elapsed since last game frame.
    int millisecsPreviousFrame = 0;
    /// Window object to display render buffers.
    SDL_Window* window;
    /// Renderer object to draw texture.
    SDL_Renderer* renderer;

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

    /// @brief Default constructor
    /// @details Base constructor of the Game class.
    void Setup();

    /// @brief Default constructor
    /// @details Base constructor of the Game class.
    void ProcessInput();

    /// @brief Default constructor
    /// @details Base constructor of the Game class.
    void Update();

    /// @brief Default constructor
    /// @details Base constructor of the Game class.
    void Render();

    /// @brief Default constructor
    /// @details Base constructor of the Game class.
    void Destroy();
};

#endif // GAME_H //
