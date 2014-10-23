#include "player.h"
#include "game.h"
#include "constants.h"

bool player::validMove(int x, int y, const game *mainGame){
    //Check screen boundaries
    if( x < 0 || x > CONSOLE_WIDTH)
        return false;
    
    else if( y < 0 || y > CONSOLE_HEIGHT)
        return false;
        
    //Check for wall
    else if(mainGame->terrain[y][x] == WALL)
        return false;
        
    else
        return true;
}

void player::move(char input, const game *mainGame){
    switch(input){
        case KB_LEFT:
            if(validMove(x-1, y, mainGame))
                x=x-1;
            break;
            
        case KB_RIGHT:
            if(validMove(x+1, y, mainGame))
                x=x+1;
            break;
        
        case KB_UP:
            if(validMove(x, y-1, mainGame))
                y=y-1;
            break;
        
        case KB_DOWN:
            if(validMove(x, y+1, mainGame))
                y=y+1;
            break;
        }
}
