#include "game.h"

int main(int argc,char *argv[]){
    game game1;
    game1.readMapFile("maps/map2.txt");
    game1.play();

    return 0;
}

