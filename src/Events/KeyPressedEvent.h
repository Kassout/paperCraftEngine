#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"
#include "SDL.h"

/// Class responsible of handling all the keyboard key pressed event notifications.
/// @file KeyPressedEvent.h
/// @author Maxime Héliot
/// @version 0.1.0 16/10/2021
class KeyPressedEvent: public Event {
public:
    /// SDL_Keycode object containing the different data related to the keyboard key pressed.
    SDL_Keycode symbol;

    /// @brief Default KeyPressedEvent constructor
    /// @details Base constructor of the KeyPressedEvent class taking base values for the different class attributes as parameters.
    KeyPressedEvent(SDL_Keycode symbol): symbol(symbol) {}
};

#endif // KEYPRESSEDEVENT_H //
