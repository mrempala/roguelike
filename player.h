#ifndef PLAYER_H
#define PLAYER_H

class game;

//V: turns out, this is similar to goblin, so lets explore whether we should combine them.
class player {
   public:
      //L: DUDE WE NEED CONTRUCTORS MAN, Initialize your shit.
      void setX(int a){x = a;} 
         //L: Why are these setters necessary. shouldn't only the player class have access to changing where the player is going?
      void setY(int a){y = a;}
      int getX(){return x;}
      int getY(){return y;}
      bool isAlive(); //L: unimplemented
      //V: should be const
      
      bool validMove(int x, int y, const game *mainGame); //V: should be const
      void move(char input, const game *mainGame);
      
   private:
      int health; //not used
      int x; //L: bad variable name
      int y; //L: bad variable name
};

#endif
