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
      int setGobNum(int a){numGoblins = a;}
      bool readTerrainFile(const char *mapFileName);
      void spawnGoblins();
      void clearScreen();
      void printDeath();
      void printGame();
      bool validMove(int x, int y)const;
      //bool isWall(int x, int y);
      bool goblinCollison();
      void play();
   
   private:
      friend class player;
      char terrain[24][81];
      char printBuff[24][81];
      player player1;
      int numGoblins;
      std::vector<goblin> goblinVec;
      //Idea: Keep two seperate class that keeps track of items
      //and enemies. Reports back if there is an enemy/item in that location.
};

#endif
