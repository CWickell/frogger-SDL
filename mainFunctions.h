/* 
 * File:   mainFunctions.h
 * Author: Chris
 *
 * Created on September 28, 2016, 10:30 PM
 */

#ifndef MAINFUNCTIONS_H
#define	MAINFUNCTIONS_H

#include "GlobalVariables.h"
#include "GameObjectFunctions.h"

bool setupSDL(char *title, int width, int height, GameState *state);
bool setupSound(GameState *state);
bool handleKey(GameState *state, const SDL_Event *event);
void close(GameState *state);
bool handleEvents(GameState *state);
void playSound(Mix_Chunk *sound);
void draw(GameState *state);
Mix_Chunk *loadSound(char *filename);
SDL_Surface *loadFile(char *filename);
SDL_Texture *loadImage(GameState *state, char *filename);
bool loadInitialGraphics(GameState *state);


#endif	/* MAINFUNCTIONS_H */

