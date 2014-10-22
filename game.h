#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <vector>

class player {
   public:
      void setX(int a){x = a;}
      void setY(int a){y = a;}
      int getX(){return x;}
      int getY(){return y;}
      //void printPlayer();
      
   private:
      int x;
      int y;
};

class goblin {
   public:
      void setX(int a){x = a;}
      void setY(int a){y = a;}
      int getX(){return x;}
      int getY(){return y;}
      void moveRandomly();
      
   private:
      int x;
      int y;
};

class game {
   public:
      game(int gobNum = 20);
      ~game();
      bool readMapFile(char *mapFileName);
      void printGame();
      bool validMove(int x, int y);
      //bool isWall(int x, int y);
      bool goblinCollison();
      void movePlayer(char input);
      void moveGoblinRandomly(goblin &aGoblin);
      void spawnGoblins();
      void play();
   
   private:
      char map[24][81];
      char printBuff[24][81];
      player player1;
      int numGoblins;
      std::vector<goblin> goblinVec;
};




