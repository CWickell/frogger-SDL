/* 
 * File:   main.c
 * Author: Chris
 *
 * Created on September 29, 2016, 4:21 PM
 */

#include "GameObjectFunctions.h"
#include "GlobalVariables.h"
#include <assert.h>
 
void initializeObjects(GameState *state){
    assert(state != NULL);
    
    state->frogger = (GameObject*) malloc(sizeof(GameObject));
    state->logA = (GameObject*) malloc(sizeof(GameObject));
    state->logB = (GameObject*) malloc(sizeof(GameObject));
    state->logC = (GameObject*) malloc(sizeof(GameObject));
    state->logD = (GameObject*) malloc(sizeof(GameObject));
    state->logE = (GameObject*) malloc(sizeof(GameObject));
    state->logF = (GameObject*) malloc(sizeof(GameObject));
    state->logG = (GameObject*) malloc(sizeof(GameObject));
    
    state->carA = (GameObject*) malloc(sizeof(GameObject));
    assert(state->carA != NULL);
    state->carB = (GameObject*) malloc(sizeof(GameObject));
    state->carC = (GameObject*) malloc(sizeof(GameObject));
    state->carD = (GameObject*) malloc(sizeof(GameObject));
    state->carE = (GameObject*) malloc(sizeof(GameObject));
    
    assert(state->carA != NULL);
    
    state->frogger->dest.x = 200; //Frog
    state->frogger->dest.y = 400; 
    state->frogger->dest.w = 50;
    state->frogger->dest.h = 50;

    state->logA->dest.x = 0;      //Row 1 water
    state->logA->dest.y = 150;
    state->logA->dest.w = 150;
    state->logA->dest.h = 50; 
    
    state->logB->dest.x = 50;  //Row 2 water
    state->logB->dest.y = 100;
    state->logB->dest.w = 100;
    state->logB->dest.h = 50; 
    
    state->logC->dest.x = 250;  //Row 3 water
    state->logC->dest.y = 50;
    state->logC->dest.w = 50;
    state->logC->dest.h = 50; 
    
    state->logD->dest.x = 250;  //Row 1 water
    state->logD->dest.y = 150;
    state->logD->dest.w = 150;
    state->logD->dest.h = 50;
    
    state->logE->dest.x = 300;  //Row 2 water
    state->logE->dest.y = 100;
    state->logE->dest.w = 100;
    state->logE->dest.h = 50;
    
    state->logF->dest.x = 100;  //Row 3 water
    state->logF->dest.y = 50;
    state->logF->dest.w = 50;
    state->logF->dest.h = 50;
    
    state->logG->dest.x = 400;  //Row 3 water
    state->logG->dest.y = 50;
    state->logG->dest.w = 50;
    state->logG->dest.h = 50;
    
    state->carA->dest.x = 0;  //Row 1 road
    state->carA->dest.y = 250;
    state->carA->dest.w = 100;
    state->carA->dest.h = 50;
    
    state->carB->dest.x = 300;  //Row 1 road
    state->carB->dest.y = 250;
    state->carB->dest.w = 100;
    state->carB->dest.h = 50;
    
    state->carC->dest.x = 175;  //Row 2 road
    state->carC->dest.y = 300;
    state->carC->dest.w = 100;
    state->carC->dest.h = 50;
    
    state->carD->dest.x = 0;  //Row 3 road
    state->carD->dest.y = 350;
    state->carD->dest.w = 100;
    state->carD->dest.h = 50;
    
    state->carE->dest.x = 200;  //Row 3 road
    state->carE->dest.y = 350;
    state->carE->dest.w = 100;
    state->carE->dest.h = 50;
}

// Changes speed of images and deals with them passing the edge of the window
// by starting them at the left
void changeSpeed(GameState *state){
    state->logA->dest.x += 1;
    if(state->logA->dest.x > 450)   state->logA->dest.x = 0;
    state->logB->dest.x -= 2;
    if(state->logB->dest.x < 0)   state->logB->dest.x = 450;
    state->logC->dest.x += 3;
    if(state->logC->dest.x > 450)   state->logC->dest.x = 0;
    state->logD->dest.x += 1;
    if(state->logD->dest.x > 450)   state->logD->dest.x = 0;
    state->logE->dest.x -= 2;
    if(state->logE->dest.x < 0)   state->logE->dest.x = 450;
    state->logF->dest.x += 3;
    if(state->logF->dest.x > 450)   state->logF->dest.x = 0;
    state->logG->dest.x += 3;
    if(state->logG->dest.x > 450)   state->logG->dest.x = 0;
    
    state->carA->dest.x += 1;
    if(state->carA->dest.x > 450)   state->carA->dest.x = 0;
    state->carB->dest.x += 1;
    if(state->carB->dest.x > 450)   state->carB->dest.x = 0;
    state->carC->dest.x += 2;
    if(state->carC->dest.x > 450)   state->carC->dest.x = 0;
    state->carD->dest.x += 1;
    if(state->carD->dest.x > 450)   state->carD->dest.x = 0;
    state->carE->dest.x += 1;
    if(state->carE->dest.x > 450)   state->carE->dest.x = 0;
}

void moveFrogger(GameState *state, int direction){
    if(direction == UP){
        if(state->frogger->dest.y == 0){
            playSound(state->cheer);
            SDL_Delay(2000);
            close(state);
        }
        state->frogger->dest.y -= 50;       
    }
    
    else if(direction == DOWN){
        if(state->frogger->dest.y == 400)   return;           
        state->frogger->dest.y += 50;        
    }
    
    else if(direction == LEFT){
        if(state->frogger->dest.x == 0)   return;
        state->frogger->dest.x -= 50;
    }
    
    else if(direction == RIGHT){
        if(state->frogger->dest.x == 400)   return;
        state->frogger->dest.x += 50;
    }
    
}

bool collisionWithCar(GameState *state){
    if((state->carA->dest.x == state->frogger->dest.x + 50
        || state->frogger->dest.x == (state->carA->dest.x + state->carA->dest.w))
        && state->carA->dest.y == state->frogger->dest.y)         
        return false;   
  
    else if((state->carB->dest.x == state->frogger->dest.x + 50
        || state->frogger->dest.x == (state->carB->dest.x + state->carB->dest.w))
        && state->carB->dest.y == state->frogger->dest.y)          
        return false; 
    
    else if((state->carC->dest.x == state->frogger->dest.x + 50
        || state->frogger->dest.x == (state->carC->dest.x + state->carC->dest.w))
        && state->carC->dest.y == state->frogger->dest.y)          
        return false; 
    
    else if((state->carD->dest.x == state->frogger->dest.x + 50
        || state->frogger->dest.x == (state->carD->dest.x + state->carD->dest.w))
        && state->carD->dest.y == state->frogger->dest.y)          
        return false; 
    
    else if((state->carE->dest.x == state->frogger->dest.x + 50
        || state->frogger->dest.x == (state->carE->dest.x + state->carE->dest.w))
        && state->carE->dest.y == state->frogger->dest.y)          
        return false; 
    
    return true;
}

bool landedOnLog(GameState *state){
    if(state->logA->dest.x <= state->frogger->dest.x
        && (state->logA->dest.x + state->logA->dest.w) >= state->frogger->dest.x + 50
        && state->logA->dest.y == state->frogger->dest.y)         
        return true;   
  
    else if(state->logB->dest.x <= state->frogger->dest.x
        && (state->logB->dest.x + state->logB->dest.w) >= state->frogger->dest.x + 50
        && state->logB->dest.y == state->frogger->dest.y)         
        return true; 
    
    else if(state->logC->dest.x <= state->frogger->dest.x
        && (state->logC->dest.x + state->logC->dest.w) >= state->frogger->dest.x + 50
        && state->logC->dest.y == state->frogger->dest.y)         
        return true; 
    
    else if(state->logD->dest.x <= state->frogger->dest.x
        && (state->logD->dest.x + state->logD->dest.w) >= state->frogger->dest.x + 50
        && state->logD->dest.y == state->frogger->dest.y)         
        return true; 
    
    else if(state->logE->dest.x <= state->frogger->dest.x
        && (state->logE->dest.x + state->logE->dest.w) >= state->frogger->dest.x + 50
        && state->logE->dest.y == state->frogger->dest.y)         
        return true; 
    
    else if(state->logF->dest.x <= state->frogger->dest.x
        && (state->logF->dest.x + state->logF->dest.w) >= state->frogger->dest.x + 50
        && state->logF->dest.y == state->frogger->dest.y)         
        return true;
    
    else if(state->logG->dest.x <= state->frogger->dest.x
        && (state->logG->dest.x + state->logG->dest.w) >= state->frogger->dest.x + 50
        && state->logG->dest.y == state->frogger->dest.y)         
        return true; 
    
    return false;
}
