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
      bool readTerrainFile(const char *mapFileName); //V: would be better off injected or static
      void spawnGoblins();
      void clearScreen(); //V: should be const!
      void printDeath(); //V: should be const!
      void printGame(); //V: should be const!
      //bool isWall(int x, int y);
      bool goblinPlayerCollison(); //V: should be const!
      void play();
   
   private:
      //V: i can see why these are 81... id prefer 80, but thats just my personal weighing
      char terrain[24][81]; //make const? more work to read in from file
      //V: i agree, make const.
      char printBuff[24][81]; //L: Print buffer only needs to be int he scope of printing
      player *player1;  //L: interesting choice, any benefit on having the player be a pointer? possibly mutiple players. I would think a const reference param for the player would be better
      //V: consider an auto_ptr (or unique_ptr if in c++11) so that we don't risk ourselves
      //forgetting to delete it in the destructor.

      //V: i dont think numGoblins is needed, cant we just use goblinVec.size()?
      //V: nevermind, seems that this is the desired/target number of goblins, set
      //to instruct spawnGoblins how many to make. I don't like this variable here though,
      //since it's extra state that's unneeded after that stage. Perhaps make it const or
      //pass it in through parameters
      //V: also, bad name. should be targetNumGoblins if you were to keep it

      int numGoblins; //L: Is this necessary? wouldn't goblinVec.size be sufficient?
      std::vector<goblin> goblinVec; //V: i prefer pointers here, so we dont run into trouble when deleting one goblin (thus changing the addresses of the rest of the goblins)
      friend class player;//temporary for now, will remove when using dependency injection
      friend class goblin; //L: friend class is suspicious to me. The whole give this scope of this to that, sorta thing
      //Idea: Add two seperate class that keep track of items
      //and enemies. Reports back if there is an enemy/item in that location.
};

#endif
