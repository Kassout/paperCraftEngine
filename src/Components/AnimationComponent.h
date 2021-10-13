#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <SDL.h>

/// Structure responsible for holding the data linked to the animation of the entity.
/// @file AnimationComponent.h
/// @author Maxime Héliot
/// @version 0.1.0 13/10/2021
struct AnimationComponent {
    /// Integer value representing the number of frames of the animation.
    int numFrames;
    /// Integer value representing the index of the current frame.
    int currentFrame;
    /// Integer value representing the animation frame rate speed.
    int frameSpeedRate;
    /// Boolean value representing the looping status of the animation.
    bool isLoop;
    /// Integer value representing the starting time of the animation at play.
    int startTime;

    /// @brief Default AnimationComponent constructor
    /// @details Base constructor of the AnimationComponent class taking number of frames, frame speed rate and looping status as parameters.
    AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true) :
    numFrames(numFrames), frameSpeedRate(frameSpeedRate), isLoop(isLoop), currentFrame(1), startTime(SDL_GetTicks()) {}
};

#endif // ANIMATIONCOMPONENT_H //
