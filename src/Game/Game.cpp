#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>


Game::Game() {
    isRunning = false;
    registry = std::make_unique<Registry>();
    Logger::Log("Game constructor called!");
}

Game::~Game() {
    Logger::Log("Game destructor called!");
}

void Game::Initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Logger::Err("Error initializing SDL.");
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
        Logger::Err("Error creating SDL window.");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        Logger::Err("Error creating SDL rederer.");
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

void Game::Setup() {
    // Create an entity
    Entity tank = registry->CreateEntity();

    // Add some components to that entity
    tank.AddComponent<TransformComponent>(glm::vec2(10.0, 30.0), glm::vec2(1.0, 1.0), glm::vec2(0.0, 0.0));
    tank.AddComponent<RigidBodyComponent>(glm::vec2(50.0, 0.0));
    tank.RemoveComponent<TransformComponent>();
}

void Game::Update() {
    // If we are too fast, waste some time cycle loops to reach the millisecs per frame value
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
    {
        SDL_Delay(timeToWait);
    }

    // The difference in ticks since the last frame, converted to seconds.
    double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0f;

    // Store the current frame time
    millisecsPreviousFrame = SDL_GetTicks();

    // TODO:
    // MovementSystem.Update();
    // CollisionSystem.Update();
    // DamageSystem.Update();
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // TODO: Render game objects...

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

