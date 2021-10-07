#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

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
    windowWidth = 1920;
    windowHeight = 1080;

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

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup() {
    playerPosition = glm::vec2(10.0, 20.0);
    playerVelocity = glm::vec2(0.5, 0.0);
}

void Game::Update() {
    // If we are too fast, waste some time cycle loops to reach the millisecs per frame value
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), millisecsPreviousFrame + MILLISECS_PER_FRAME));

    // Store the current frame time
    millisecsPreviousFrame = SDL_GetTicks();

    playerPosition.x += playerVelocity.x;
    playerPosition.y += playerVelocity.y;
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // Loads a PNG texture
    SDL_Surface* surface = IMG_Load("../assets/images/tank-tiger-right.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // What is the destination rectangle that we want to place our texture
    SDL_Rect dstRect = { static_cast<int>(playerPosition.x), static_cast<int>(playerPosition.y), 32, 32 };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}

void Game::Run() {
    Setup();
    while (isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

