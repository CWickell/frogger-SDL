/* 
 * File:   GlobalVariables.h
 * Author: Chris Wickell
 *
 * Created on September 28, 2016, 8:27 PM
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include "GameObject.h"

#ifndef GLOBALVARIABLES_H
#define	GLOBALVARIABLES_H

/// The constant width of the playing surface in pixels.
#define WIDTH 450

/// The constant height of the playing surface in pixels.
#define HEIGHT 450

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


// Sound channels
#define CRASH_CHANNEL           1
#define CHEER_CHANNEL           2   
#define SPLASH_CHANNEL          3
#define JUMP_CHANNEL            4

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *image1;
    SDL_Surface *image2;
    SDL_Surface *image3;
    SDL_Surface *image4;
    
    SDL_Texture *background;
    SDL_Texture *frog;
    SDL_Texture *car;
    SDL_Texture *log;
 
    GameObject *frogger;
    
    GameObject *logA;
    GameObject *logB;
    GameObject *logC;
    GameObject *logD;
    GameObject *logE;
    GameObject *logF;
    GameObject *logG;
    
    GameObject *carA;
    GameObject *carB;
    GameObject *carC;
    GameObject *carD;
    GameObject *carE;
    
    Mix_Chunk *crash;
    Mix_Chunk *cheer;
    Mix_Chunk *splash;
    Mix_Chunk *jump;
} GameState;

#endif	/* GLOBALVARIABLES_H */

