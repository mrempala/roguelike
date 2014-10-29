#ifndef GAME_H
#define GAME_H

#include <vector>

//Forward Declaration
class player;
class goblin;

//L: Some design things, the print is cool with the buffer. after talking to bandith, its pretty apparent to me that
//One of the better methods is to make a render object that the game spits out that another class can read
//based on the class that reads it, it will be rendered differently.

class game {
   public:
      game();
      ~game();
      int setGobNum(int a){numGoblins = a;} //L: This function seems useless, why not just pass in the integer intoy our spawn goblins function. Seems like more state.
      bool readTerrainFile(const char *mapFileName);
      void spawnGoblins();
      void clearScreen();
      void printDeath();
      void printGame();
      //bool isWall(int x, int y);
      bool goblinPlayerCollison();
      void play();
   
   private:
      char terrain[24][81]; //make const? more work to read in from file
      char printBuff[24][81]; //L: Print buffer only needs to be int he scope of printing
      player *player1;  //L: interesting choice, any benefit on having the player be a pointer? possibly mutiple players. I would think a const reference param for the player would be better
      int numGoblins; //L: Is this necessary? wouldn't goblinVec.size be sufficient?
      std::vector<goblin> goblinVec;
      friend class player;//temporary for now, will remove when using dependency injection
      friend class goblin; //L: friend class is suspicious to me. The whole give this scope of this to that, sorta thing
      //Idea: Add two seperate class that keep track of items
      //and enemies. Reports back if there is an enemy/item in that location.
};

#endif
