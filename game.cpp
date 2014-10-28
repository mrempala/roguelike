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
    //Intialize random seed
    srand (time(NULL)); //srand time null is bad for testing
    numGoblins = 0;
    player1 = new player;
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
      std::cout << line << '\n'; // huh? whats the purpose of outputting on an input function
      strcpy(terrain[i],line.c_str()); //Can't you increase readibility if you inputted directly into the terrain
      int j = 0;
      while(terrain[i][j]!='\0'){ //could get inefficient if you don't stop searching when the player is found.
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

  //THERES NO REATURN VALUE HORRY CRAPS
}

void game::spawnGoblins(){ 
  //I really would rather have this take in the number of goblins and not hae numGoblins as extra state.
  //This is mostly because, what if you forget to decrement the goblin counter after you kill a goblin in the future.
  //your program is fucked

  //These variables needa be initialized.
  //I also dislike the use of x and y. They are nowhere near descriptive enough as variables.
  //I think newGoblinRow and newGoblinCol would be better.
    int x, y; // These can be declared inside the for loop to decrease the scope of the x and y
    goblin temp; // This can be declared inside the if statement below to decrease scope
    //Decrease the likelyhood that someone else comes in here and FUCKs your code
    //Using goblinvec.size instead of 0 incase there are already goblins
    for(int i = goblinVec.size(); goblinVec.size()<numGoblins; i++){
        x = rand() % CONSOLE_WIDTH;
        y = rand() % CONSOLE_HEIGHT;
        
        bool goblinPresent = false;
        //This looks ultra inefficient. Why do you have to check every single goblin if it's there
        //Cant you just look at the spot and ask if there is something there?
        //The new goblin only needs to know the information about the spot and not every other goblin
        for(int j = 0; j < goblinVec.size(); j++){
            if (goblinVec[j].getX() == x && goblinVec[j].getY() == y ){
                goblinPresent = true;
                break;
            }
        }
        
        //Need to break this down for readability
        if(terrain[y][x] == FLOOR && !goblinPresent &&
        !(x==player1->getX() && y==player1->getY())){
            temp.setX(x);
            temp.setY(y);
            goblinVec.push_back(temp);
        }
    }
}

bool game::goblinPlayerCollison(){ 
    //I would reevaluate the way the data is stored to make things like this not necessary
    //Having each goblin check if it collided with the player seems like it would be a problem for
    //scalability
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
    char input; // this should be initialized
    std::cin>>input;
    while(input != 'q'){
        player1->move(input, this);
        
        //Quick copy & paste here, felt wrong that a player
        //and goblin could walk past each other
        //Figure out a way to make this work!
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
        
        std::cin>>input;
    }
    
}


void game::clearScreen(){
    for(int i = 0; i < CONSOLE_HEIGHT; i++){
        std::cout<<std::endl;
    }
}

void game::printDeath(){
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
    printBuff[player1->getY()][player1->getX()] = PLAYER; //print buffer doesnt have to be global if it only used in print

    //Print to Screen
    for(int i = 0; i < CONSOLE_HEIGHT; i++){
        std::cout<<printBuff[i]<<std::endl;
    }
}








