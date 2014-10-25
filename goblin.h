#ifndef GOBLIN_H
#define GOBLIN_H

class game;

class goblin {
   public:
      bool validMove(int x, int y, const game* mainGame);
      void moveRandomly(const game *mainGame);
      void spawn(const game* mainGame); //Not implemented
      
      void setX(int a){x = a;}
      void setY(int a){y = a;}
      int getX()const{return x;}
      int getY()const{return y;}
      
   private:
      int health; //not used
      int x;
      int y;
};

#endif
