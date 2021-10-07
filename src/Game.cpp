#include "Game.h"
#include <iostream>
#include <SDL.h>

Game::Game() {
    isRunning = false;
    std::cout << "Game constructor called!" << std::endl;
}

Game::~Game() {
    std::cout << "Game destructor called!" << std::endl;
}

void Game::Initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }

    SDL_DisplayMode displayMode;
    // use reference to get the memory address of the struct
    // the method will populate the value inside the struct
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = 800;
    windowHeight = 600;

    // SDL_Window* -> Pointer to a struct
    // window -> pointer to a memory address where the struct is located
    window = SDL_CreateWindow("Paper Craft Engine",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        std::cerr << "Error creating SDL rederer." << std::endl;
        return;
    }

    // Change video mode to real fullscreen
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;
}

void Game::Run() {
    while (isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::ProcessInput() {
    SDL_Event sdlEvent;
    // &sdlEvent -> reference of the sdlEvent struct.
    while(SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type) {
            // Event of closing the window;
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
                break;
        }
    }
}

void Game::Update() {
    std::cout << "Game update called!" << std::endl;
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    // TODO: Render all game objects...

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

