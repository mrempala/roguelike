#include "game.h"
#include "goblin.h"
#include "constants.h"
std::map<char, tile> charToTile;

//Class implementation
game::game(){
    //Intialize random seed
    srand (time(NULL));
    numGoblins = 0;
}

game::~game(){
    //Do nothing, no dynamic alloc
}

bool game::validMove(int x, int y)const{
    //Check screen boundaries
    if( x < 0 || x > CONSOLE_WIDTH)
        return false;
    
    else if( y < 0 || y > CONSOLE_HEIGHT)
        return false;
        
    //Check for wall
    else if(terrain[y][x] == WALL)
        return false;
        
    else
        return true;
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
            player1.setX(j);
            player1.setY(i);
            terrain[i][j] = FLOOR;
        }
        j++;
      }
      i++;
    }
    myfile.close();
  }
}

void game::spawnGoblins(){
    //TODO: make sure goblins can't spawn on player
    int x, y;
    goblin temp;
    //Using goblinvec.size instead of 0 incase there are already goblins
    for(int i = goblinVec.size(); goblinVec.size()<numGoblins; i++){
        x = rand() % CONSOLE_WIDTH;
        y = rand() % CONSOLE_HEIGHT;
        if(terrain[y][x] == FLOOR){
            temp.setX(x);
            temp.setY(y);
            goblinVec.push_back(temp);
        }
    }
}

bool game::goblinCollison(){
    for(int i = 0; i<goblinVec.size(); i++){
        if(goblinVec[i].getX() == player1.getX() &&
           goblinVec[i].getY() == player1.getY()){
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
        player1.move(input, this);
        
        //Quick copy & paste here, felt wrong that a player
        //and goblin could walk past each other
        if(goblinCollison()){
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
        
        if(goblinCollison()){
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



/*
game::play2(){
    //Initalize Game
    spawnGoblins();
    printGame();
    char input;
    std::cin>>input;
    
    //Loop until player dies or quits
    while(player1.isAlive() && input != 'Q'){
        player.movePlayer(input);
        
    
        std::cin>>input;
    }
}*/


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
    printBuff[player1.getY()][player1.getX()] = PLAYER;

    //Print to Screen
    for(int i = 0; i < CONSOLE_HEIGHT; i++){
        std::cout<<printBuff[i]<<std::endl;
    }
}








