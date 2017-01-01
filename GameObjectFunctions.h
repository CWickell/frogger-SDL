/* 
 * File:   TurtleObject.h
 * Author: Chris
 *
 * Created on October 2, 2016, 2:20 PM
 */
#include "GlobalVariables.h"
#include "mainFunctions.h"

#ifndef GAMEOBJECTFUNCTIONS_H
#define	GAMEOBJECTFUNCTIONS_H

/// Move and otherwise update the given object for the current frame
void initializeObjects(GameState *state);
void changeSpeed(GameState *state);
void moveFrogger(GameState *state, int direction);
bool collisionWithCar(GameState *state);
bool landedOnLog(GameState *state);

#endif	/* GAMEOBJECTFUNCTIONS_H */

