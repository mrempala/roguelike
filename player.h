#ifndef PLAYER_H
#define PLAYER_H

class game;

class player {
   public:
      void setX(int a){x = a;}
      void setY(int a){y = a;}
      int getX(){return x;}
      int getY(){return y;}
      bool isAlive();
      
      bool validMove(int x, int y, const game *mainGame);
      void move(char input, const game *mainGame);
      
   private:
      int health; //not used
      int x;
      int y;
};

#endif
