#ifndef GAME_H
#define GAME_H

#include <vector>

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
      bool goblinPlayerCollison();
      void play();
   
   private:
      char terrain[24][81]; //make const? more work to read in from file
      char printBuff[24][81];
      player *player1;
      int numGoblins;
      std::vector<goblin> goblinVec;
      friend class player;
      //Idea: Add two seperate class that keep track of items
      //and enemies. Reports back if there is an enemy/item in that location.
};

#endif
