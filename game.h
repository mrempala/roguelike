#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <map>
#include <termios.h>
#include "player.h"

//Forward Declaration
class player;
class goblin;

class game {
   public:
      game();
      ~game();
      bool readTerrainFile(const char *mapFileName);
      void clearScreen();
      void printDeath();
      void printGame();
      bool validMove(int x, int y);
      //bool isWall(int x, int y);
      bool goblinCollison();
      void movePlayer(char input);
      void moveGoblinRandomly(goblin &aGoblin);
      void spawnGoblins();
      void play();
   
   private:
      friend class player;
      char terrain[24][81];
      char printBuff[24][81];
      player player1;
      int numGoblins;
      std::vector<goblin> goblinVec;
      //std::Vector<enemy> enemy 
};

#endif
