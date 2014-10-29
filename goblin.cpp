#include "goblin.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>
#include "constants.h"

//L: I feel like this function can be a function inside the class that both player and goblin use.
bool goblin::validMove(int x, int y, const game* mainGame){
    //Not happy with this, when I convert to use independency injection
    //This will be different.
    for(int i = 0; i < mainGame->goblinVec.size(); i++){
        if (mainGame->goblinVec[i].getX() == x && mainGame->goblinVec[i].getY() == y ){
            return false;
        }
    }
    
    if( x < 0 || x > CONSOLE_WIDTH)
        return false;
    
    else if( y < 0 || y > CONSOLE_HEIGHT)
        return false;
        
    else if(mainGame->terrain[y][x] == WALL)
        return false;
        
    else
        return true;
}


void goblin::moveRandomly(const game *mainGame){
    int randNum = rand() % 4;
    switch(randNum){
        //Left
        case 0:
            if(validMove(x-1, y, mainGame))
                x=x-1;
            break;
            
        //Right
        case 1:
            if(validMove(x+1, y, mainGame))
                x=x+1;
            break;
        
        //Up
        case 2:
            if(validMove(x, y-1, mainGame))
                y=y-1;
            break;
        
        //Down
        case 3:
            if(validMove(x, y+1, mainGame))
                y=y+1;
            break;
    }
}

