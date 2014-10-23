#ifndef GOBLIN_H
#define GOBLIN_H

class goblin {
   public:
      void setX(int a){x = a;}
      void setY(int a){y = a;}
      int getX(){return x;}
      int getY(){return y;}
      void moveRandomly();
      
   private:
      int health; //not used
      int x;
      int y;
};

#endif
