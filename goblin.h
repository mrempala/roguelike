#ifndef GOBLIN_H
#define GOBLIN_H

class game;

class goblin {
   public:
      //L: Constructors dawg!
      bool validMove(int x, int y, const game* mainGame);
      void moveRandomly(const game *mainGame);
      void spawn(const game* mainGame); //Not implemented
      
      //L: setters are only being used in the instantiation of a goblin. why not just use a constructor thus having to save you from having a setter in the class
      void setX(int a){x = a;}
      void setY(int a){y = a;}
      int getX()const{return x;}
      int getY()const{return y;}
      
   private:
      //V: take it out for now, since it can so easily be added it once we do decide to have health
      int health; //not used
      int x; //L: bad variable name
      int y; //L: bad variable name
};

#endif
