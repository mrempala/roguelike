#ifndef PLAYER_H
#define PLAYER_H

class game;

class player {
   public:
      //DUDE WE NEED CONTRUCTORS MAN, Initialize your shit.
      void setX(int a){x = a;} //Why are these setters necessary. shouldn't only the player class have access to changing where the player is going?
      void setY(int a){y = a;}
      int getX(){return x;}
      int getY(){return y;}
      bool isAlive();
      
      bool validMove(int x, int y, const game *mainGame); //
      void move(char input, const game *mainGame);
      
   private:
      int health; //not used
      int x;
      int y;
};

#endif
