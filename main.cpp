#include "game.h"
#include <termios.h>
#include <unistd.h> //Needed for STDIN_FILENO when using gcc 4.7

int main(int argc,char *argv[]){
    //Some code I copied to get unbuffered input on linux
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSADRAIN, &t);

    game game1;
    game1.setGobNum(20); //L: ah so this is why, why not pass 20 into the play function, then use that parameter to pass into the spawn goblins function.
    //L: OMG dawg, readTerrain returns a bool. use that to check if it is loaded!
    game1.readTerrainFile("maps/map2.txt");
    game1.play();

    return 0;
}

