/* 
 * File:   main.c
 * Author: Chris
 *
 * Created on September 29, 2016, 4:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_framerate.h>
#include "mainFunctions.h"
#include "GlobalVariables.h"
#include "GameObjectFunctions.h"

/// The target frame rate in Hz
#define FRAME_RATE 60


/*
 * 
 */
int main(int argc, char* args[] ) {
   
    GameState state = {.window=NULL, .renderer=NULL, .background=NULL};  
    
     // Start SDL successfully or quit
    if(!setupSDL("Frogger", WIDTH, HEIGHT, &state)){
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        close(&state);
    }
    
    // Start the audio mixer
    if(!setupSound(&state)){
        fprintf(stderr, "Sound Error: %s\n", Mix_GetError());
        close(&state);
    }
    
    if(!loadInitialGraphics(&state)){
        fprintf(stderr, "Graphics Error: %s\n", SDL_GetError());
        close(&state);
    }

    // Setup a frame rate manager for the requested frame rate
    FPSmanager frameManager;
    SDL_initFramerate(&frameManager);
    SDL_setFramerate(&frameManager, FRAME_RATE);
    
    //Initialize starting locations of images and allocate the memory
    initializeObjects(&state);

  
    // Keep running, while trying to keep the requested frame rate until we are
    // asked to quit
    bool running = true;
    while(running)
    {       
        running = handleEvents(&state);
        changeSpeed(&state);
        SDL_framerateDelay(&frameManager);
        draw(&state);
    }
    
    close(&state);
    
    return (EXIT_SUCCESS);
}

