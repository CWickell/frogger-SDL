/* 
 * File:   GameObject.h
 * Author: Chris
 *
 * Created on September 29, 2016, 9:37 PM
 */

#ifndef GAMEOBJECT_H
#define	GAMEOBJECT_H

typedef enum {FROG_TYPE, LOG_TYPE, VEHICLE_TYPE} GameObjectType;

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct GameObject
{
    SDL_Rect dest;
    
    int direction;
    int location;
    int currentRow;
    int alive;
    int riding;
    int ridingType;
    int deathType;
    int deathCount;

    SDL_Rect src;
    SDL_Rect dst;

} GameObject;


#endif	/* GAMEOBJECT_H */

