#include "game.h"
#include "goblin.h"
#include "player.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "constants.h"

//Class implementation
game::game(){
    //V: prefer not seeding with time, do something more deterministic
    //Intialize random seed
    srand (time(NULL));
    numGoblins = 0;
    player1 = new player; //V: its unusual to see without (), best put those in.
}

game::~game(){
    delete player1;
}

bool game::readTerrainFile(const char *fileName){
  //Sloppy and hacked together, will fix later
  std::ifstream myfile (fileName);
  std::string line;
  int i=0;
  if (myfile.is_open()){
    while ( std::getline (myfile, line) ){
      std::cout << line << '\n';
      strcpy(terrain[i],line.c_str());
      int j = 0;
      while(terrain[i][j]!='\0'){
        if(terrain[i][j] == PLAYER){
            player1->setX(j);
            player1->setY(i);
            terrain[i][j] = FLOOR;
        }
        j++;
      }
      i++;
    }
    myfile.close();
  }
}

//V: quiz question: what are all the inputs, hidden and otherwise, to this function?
void game::spawnGoblins(){
    int x, y;
    goblin temp;
    //Using goblinvec.size instead of 0 incase there are already goblins
    for(int i = goblinVec.size(); goblinVec.size()<numGoblins; i++){
        x = rand() % CONSOLE_WIDTH;
        y = rand() % CONSOLE_HEIGHT;
        
        bool goblinPresent = false;
        for(int j = 0; j < goblinVec.size(); j++){
            if (goblinVec[j].getX() == x && goblinVec[j].getY() == y ){
                goblinPresent = true;
                break;
            }
        }
        
        //Need to break this down for readability
        //V: agreed. two more boolean variables should be good.
        if(terrain[y][x] == FLOOR && !goblinPresent &&
        !(x==player1->getX() && y==player1->getY())){
            temp.setX(x);
            temp.setY(y);
            goblinVec.push_back(temp); //V: hope youre aware of the copy going on here
        }
    }
}

bool game::goblinPlayerCollison(){
    for(int i = 0; i<goblinVec.size(); i++){
        if(goblinVec[i].getX() == player1->getX() &&
           goblinVec[i].getY() == player1->getY()){
             return true;
           }
        }
    return false;
}

void game::play(){
    spawnGoblins();
    printGame();
    char input;
    std::cin>>input;
    while(input != 'q'){
        player1->move(input, this);
        
        //Quick copy & paste here, felt wrong that a player
        //and goblin could walk past each other
        if(goblinPlayerCollison()){
           clearScreen();
           printDeath();
           std::cout<<"You have been eaten by a grue :("<<std::endl;
           std::cout<<"Don't go north next time, dummy"<<std::endl;
           std::cout<<"http://xkcd.com/91/"<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
           break;
        }
        
        for(int i = 0; i<goblinVec.size(); i++){
        goblinVec[i].moveRandomly(this);
        }
        
        printGame();
        
        if(goblinPlayerCollison()){
           clearScreen();
           printDeath();
           std::cout<<"You have been eaten by a grue :("<<std::endl;
           std::cout<<"Don't go north next time, dummy"<<std::endl;
           std::cout<<"http://xkcd.com/91/"<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
           break;
       }
        
        //V: This should happen once, not twice. ask me for the better way
        std::cin>>input;
    }
    
}


void game::clearScreen(){
    for(int i = 0; i < CONSOLE_HEIGHT; i++){
        std::cout<<std::endl;
    }
}

void game::printDeath(){
    //V: LOL NICE
    std::cout<<" __      __                         _______   __                  __ "<<std::endl;
    std::cout<<"/  \\    /  |                       /       \\ /  |                /  |"<<std::endl;
    std::cout<<"$$  \\  /$$/______   __    __       $$$$$$$  |$$/   ______    ____$$ |"<<std::endl;
    std::cout<<" $$  \\/$$//      \\ /  |  /  |      $$ |  $$ |/  | /      \\  /    $$ |"<<std::endl;
    std::cout<<"  $$  $$//$$$$$$  |$$ |  $$ |      $$ |  $$ |$$ |/$$$$$$  |/$$$$$$$ |"<<std::endl;
    std::cout<<"   $$$$/ $$ |  $$ |$$ |  $$ |      $$ |  $$ |$$ |$$    $$ |$$ |  $$ |"<<std::endl;
    std::cout<<"    $$ | $$ \\__$$ |$$ \\__$$ |      $$ |__$$ |$$ |$$$$$$$$/ $$ \\__$$ |"<<std::endl;
    std::cout<<"    $$ | $$    $$/ $$    $$/       $$    $$/ $$ |$$       |$$    $$ |"<<std::endl;
    std::cout<<"    $$/   $$$$$$/   $$$$$$/        $$$$$$$/  $$/  $$$$$$$/  $$$$$$$/ "<<std::endl;
    std::cout<<std::endl<<std::endl<<std::endl;
}

void game::printGame(){
    //Copy map to printbuffer
    for(int i = 0; i < CONSOLE_HEIGHT; i++)
        for(int j =0; j < CONSOLE_WIDTH + 1; j++)
            printBuff[i][j] = terrain[i][j];
    
    //Add goblins to printbuff
    for(int i = 0; i<goblinVec.size(); i++){
        printBuff[goblinVec[i].getY()][goblinVec[i].getX()] = GOBLIN;
    }
             
    //Add player to printbuff
    printBuff[player1->getY()][player1->getX()] = PLAYER;

    //Print to Screen
    for(int i = 0; i < CONSOLE_HEIGHT; i++){
        std::cout<<printBuff[i]<<std::endl;
    }
}








