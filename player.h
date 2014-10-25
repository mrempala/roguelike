#ifndef PLAYER_H
#define PLAYER_H

class game;

//V: turns out, this is similar to goblin, so lets explore whether we should combine them.

class player {
   public:
      void setX(int a){x = a;}
      void setY(int a){y = a;}
      int getX(){return x;}
      int getY(){return y;}
      bool isAlive(); //V: should be const
      
      bool validMove(int x, int y, const game *mainGame); //V: should be const
      void move(char input, const game *mainGame);
      
   private:
      int health; //not used
      int x;
      int y;
};

#endif
