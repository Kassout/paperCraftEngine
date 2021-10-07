#ifndef GAME_H
#define GAME_H

#include <SDL.h>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

/// Class responsible for calling all of our game code and keeping the game running.
/// @file Game.h
/// @author Maxime Héliot
/// @version 0.1.0 07/10/2021
class Game
{
private:
    bool isRunning;
    int millisecsPreviousFrame = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    // Constructor
    Game();

    // Destructor
    ~Game();

    void Initialize();
    void Run();
    void Setup();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

    int windowWidth;
    int windowHeight;
};

#endif // GAME_H //
