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
    game1.setGobNum(20);
    game1.readTerrainFile("maps/map2.txt");
    game1.play();

    return 0;
}

