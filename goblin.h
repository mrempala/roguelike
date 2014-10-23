#ifndef GOBLIN_H
#define GOBLIN_H

class game;

class goblin {
   public:
      void setX(int a){x = a;}
      void setY(int a){y = a;}
      int getX(){return x;}
      int getY(){return y;}
      void moveRandomly(const game *mainGame);
      
   private:
      int health; //not used
      int x;
      int y;
};

#endif
