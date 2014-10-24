#ifndef GOBLIN_H
#define GOBLIN_H

class game;

class goblin {
   public:
      void setX(int a){x = a;}
      void setY(int a){y = a;}
      int getX()const{return x;}
      int getY()const{return y;}
      bool validMove(int x, int y, const game* mainGame);
      void moveRandomly(const game *mainGame);
      
   private:
      int health; //not used
      int x;
      int y;
};

#endif
