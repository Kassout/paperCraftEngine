#ifndef GAME_H
#define GAME_H

#include <SDL.h>

/// Class responsible for calling all of our game code and keeping the game running.
/// @file Game.h
/// @author Maxime Héliot
/// @version 0.1.0 07/10/2021
class Game
{
private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    // Constructor
    Game();

    // Destructor
    ~Game();

    void Initialize();
    void Run();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

    int windowWidth;
    int windowHeight;
};

#endif // GAME_H //
