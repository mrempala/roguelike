#include "goblin.h"
#include "game.h"
#include "constants.h"
#include <stdlib.h>
#include <time.h>

void goblin::moveRandomly(const game *mainGame){
    int randNum = rand() % 4;
    switch(randNum){
        //Left
        case 0:
            if(mainGame->validMove(x-1, y))
                x=x-1;
            break;
            
        //Right
        case 1:
            if(mainGame->validMove(x+1, y))
                x=x+1;
            break;
        
        //Up
        case 2:
            if(mainGame->validMove(x, y-1))
                y=y-1;
            break;
        
        //Down
        case 3:
            if(mainGame->validMove(x, y+1))
                y=y+1;
            break;
    }
}

