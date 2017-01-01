/* 
 * File:   mainFunctions.c
 * Author: Chris
 *
 * Created on September 28, 2016, 3:25 PM
 */

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "mainFunctions.h"
#include "GameObject.h"

Mix_Chunk *loadSound(char *filename)
{
    char *basePath = SDL_GetBasePath();
    if(!basePath) return NULL;
    char fullPath[strlen(filename) + strlen(basePath) + 1];
    strcpy(fullPath, basePath);
    SDL_free(basePath);
    strcat(fullPath, filename);
    
    return Mix_LoadWAV(fullPath);
}

SDL_Surface *loadFile(char *filename){
    SDL_Surface* bmpfile;
    char *basePath = SDL_GetBasePath();
    if(!basePath) return NULL;
    char fullPath[strlen(filename) + strlen(basePath) + 1];
    strcpy(fullPath, basePath);
    SDL_free(basePath);
    strcat(fullPath, filename);
    bmpfile = SDL_LoadBMP(fullPath);

    return bmpfile;
}

SDL_Texture *loadImage(GameState *state, char *filename)
{
    // Get the full path to the requested file in case the program was not
    // run from within its base directory.
    char *basePath = SDL_GetBasePath();
    if(!basePath) return false;
    char fullPath[strlen(filename) + strlen(basePath) + 1];
    strcpy(fullPath, basePath);
    SDL_free(basePath);
    strcat(fullPath, filename);

    // Load the image into memory
    return IMG_LoadTexture(state->renderer, filename);
}

bool setupSDL(char *title, int width, int height, GameState *state)
{
    assert(title != NULL);
    assert(width > 0);
    assert(height > 0);
    assert(state != NULL);

    // Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)) return false;

    // Create a window centered on the screen with the given title and size
    if(!(state->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN)))
        return false;

    // Create renderer
    if(!(state->renderer = SDL_CreateRenderer(state->window, -1,
                                              SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC)))
        return false;
    
    return true;
}

bool loadInitialGraphics(GameState *state){
    //Create background
    
    state->image1 = loadFile("BackGround.bmp");
    if(!(state->image1)){
        (printf("%s", SDL_GetError()));
        return false;
    }
    
    state->background = SDL_CreateTextureFromSurface(state->renderer, 
                                    state->image1);
    SDL_FreeSurface(state->image1);
    
    state->image2 = loadFile("frog.bmp");
    if(!(state->image2)){
        (printf("%s", SDL_GetError()));
        return false;
    }
    
    state->frog = SDL_CreateTextureFromSurface(state->renderer, 
                                    state->image2);
    SDL_FreeSurface(state->image2);
    
    state->image3 = loadFile("LongLog.bmp");
    if(!(state->image3)){
        (printf("%s", SDL_GetError()));
        return false;
    }
    
    state->log = SDL_CreateTextureFromSurface(state->renderer, 
                                    state->image3);
    SDL_FreeSurface(state->image3);
    
    state->car = loadImage(state, "Car.png");
    
    return true;
}

bool setupSound(GameState *state)
{    
    // Try to load support for all music formats
    int flags = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
    int result = Mix_Init(flags);
    if((result & flags) != flags) return false;

    // Start the mixer
    if(Mix_OpenAudio(MIX_DEFAULT_FORMAT, MIX_DEFAULT_FORMAT, 2, 1024)) 
        return false;

    // Make some channels to play our sounds
    if(Mix_AllocateChannels(7) != 7) return false;

    // Load the sounds
    if(!(state->crash = loadSound("crash.wav")))   return false;
    if(!(state->cheer = loadSound("cheer.wav")))    return false;
    if(!(state->splash = loadSound("splash.wav")))   return false;
    if(!(state->jump = loadSound("jump.wav")))   return false;

    assert(state->crash != NULL);
    assert(state->cheer != NULL);
    assert(state->splash != NULL);
    assert(state->jump != NULL);

    return true;
}

bool handleEvents(GameState *state)
{
    assert(state != NULL);

    // A place to hold any events that happen
    SDL_Event event;

    // Should the game quit
    bool run = true;

    // Any events? (think about why this is a while loop)
    while(run && SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                run = false;
                break;
            case SDL_KEYDOWN:
                run = run && handleKey(state, &event);
                break;
            case SDL_KEYUP:
                run = run && handleKey(state, &event);
                break;
            default:
                break;
        }
    }
    return run;
}

/// Update the current game state based on the given key event
bool handleKey(GameState *state, const SDL_Event *event){
    assert(state != NULL);
    assert(event != NULL);
    assert(SDL_KEYDOWN == event->type || SDL_KEYUP == event->type);
    
    bool keyDown = event->type == SDL_KEYDOWN;
    if(keyDown == true){
        switch(event->key.keysym.sym) {
            case SDLK_UP:
                moveFrogger(state, UP);
                playSound(state->jump); 
                break;
            case SDLK_DOWN:
                moveFrogger(state, DOWN);
                playSound(state->jump);
                break;
            case SDLK_LEFT:
                moveFrogger(state, LEFT);
                playSound(state->jump);
                break;
            case SDLK_RIGHT:
                moveFrogger(state, RIGHT);
                playSound(state->jump);
                break;
            default:
                break;
        }
    }    

    return true;
}

void playSound(Mix_Chunk *sound){
	Mix_PlayChannel(-1, sound, 0);
}

void draw(GameState *state)
{
    assert(state != NULL);

    // Clear the window to black.
    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
    SDL_RenderClear(state->renderer);

    // Get the height and width of the renderer and image
    int rendererW, rendererH;
    SDL_GetRendererOutputSize(state->renderer, &rendererW, &rendererH);

    // Draw the background in our window
    SDL_RenderCopy(state->renderer, state->background, NULL, NULL);
    
    // Draw the frog in our window
    SDL_RenderCopy(state->renderer, state->frog, NULL, &state->frogger->dest);
    
    // Draw the first log in our window
    SDL_RenderCopy(state->renderer, state->log, NULL, &state->logA->dest);
    
    // Draw the second log in our window
    SDL_RenderCopy(state->renderer, state->log, NULL, &state->logB->dest);
    
    // Draw the third log in our window
    SDL_RenderCopy(state->renderer, state->log, NULL, &state->logC->dest);
    
    // Draw the fourth log in our window
    SDL_RenderCopy(state->renderer, state->log, NULL, &state->logD->dest);
    
    // Draw the fifth log in our window
    SDL_RenderCopy(state->renderer, state->log, NULL, &state->logE->dest);
    
    // Draw the sixth log in our window
    SDL_RenderCopy(state->renderer, state->log, NULL, &state->logF->dest);
    
    // Draw the seventh log in our window
    SDL_RenderCopy(state->renderer, state->log, NULL, &state->logG->dest);
    
    // Draw the first car in our window
    SDL_RenderCopy(state->renderer, state->car, NULL, &state->carA->dest);
    
    // Draw the second car in our window
    SDL_RenderCopy(state->renderer, state->car, NULL, &state->carB->dest);
    
    // Draw the third car in our window
    SDL_RenderCopy(state->renderer, state->car, NULL, &state->carC->dest);
    
    // Draw the fourth car in our window
    SDL_RenderCopy(state->renderer, state->car, NULL, &state->carD->dest);
    
    // Draw the fifth car in our window
    SDL_RenderCopy(state->renderer, state->car, NULL, &state->carE->dest);
    
    if(collisionWithCar(state) != true){
                    playSound(state->crash); 
                    SDL_Delay(2000);
                    close(state);
                }
    /*
    if(landedOnLog(state) == true){
                    playSound(state->splash); 
                    SDL_Delay(2000);
                    close(state);
                }
    */
    SDL_RenderPresent(state->renderer);

}

void close(GameState *state)
{
    Mix_CloseAudio();
    while(Mix_Init(0))     Mix_Quit();
    if(state->crash)       
        Mix_FreeChunk(state->crash);
    if(state->cheer)       
        Mix_FreeChunk(state->cheer);
    if(state->splash)      
        Mix_FreeChunk(state->splash);
    if(state->jump)        
        Mix_FreeChunk(state->jump);
    if(state->renderer)    
        SDL_DestroyRenderer(state->renderer);
    if(state->window)
        SDL_DestroyWindow(state->window);     
    if(SDL_WasInit(0))     
        SDL_Quit();

    free(state->logA);
    free(state->logB);
    free(state->logC);
    free(state->logD);
    free(state->logE);
    free(state->logF);
    free(state->logG);
    
    free(state->carA);
    free(state->carB);
    free(state->carC);
    free(state->carD);
    free(state->carE);
    
    exit(EXIT_SUCCESS);
}
