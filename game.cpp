#include "game.h"

//Global constants
const int CONSOLE_HEIGHT = 24;
const int CONSOLE_WIDTH  = 80;

const char WALL   = '#';
const char FLOOR  = '.';
const char PLAYER = '@';
const char GOBLIN = 'g';

const char KB_LEFT = 'a';
const char KB_RIGHT = 'd';
const char KB_UP = 'w';
const char KB_DOWN = 's';


//Class implementation
game::game(int gobNum){
    //Intialize random seed
    srand (time(NULL));
    numGoblins = gobNum;
}

game::~game(){
    //Do nothing, no dynamic alloc
}

bool game::validMove(int x, int y){
    //Check screen boundaries
    if( x < 0 || x > CONSOLE_WIDTH)
        return false;
    
    else if( y < 0 || y > CONSOLE_HEIGHT)
        return false;
        
    //Check for wall
    else if(map[y][x] == WALL)
        return false;
        
    else
        return true;
}

bool game::readMapFile(char *mapFileName){
  //Sloppy and hacked together, will fix later
  std::ifstream myfile (mapFileName);
  std::string line;
  int i=0;
  if (myfile.is_open()){
    while ( std::getline (myfile, line) ){
      std::cout << line << '\n';
      strcpy(map[i],line.c_str());
      int j = 0;
      while(map[i][j]!='\0'){
        if(map[i][j] == PLAYER){
            player1.setX(j);
            player1.setY(i);
            map[i][j] = FLOOR;
        }
        j++;
      }
      i++;
    }
    myfile.close();
  }
}


void game::moveGoblinRandomly(goblin &aGoblin){
    int randNum = rand() % 4;
    switch(randNum){
        //Left
        case 0:
            if(validMove(aGoblin.getX()-1, aGoblin.getY()))
                aGoblin.setX(aGoblin.getX()-1);
            break;
            
        //Right
        case 1:
            if(validMove(aGoblin.getX()+1, aGoblin.getY()))
                aGoblin.setX(aGoblin.getX()+1);
            break;
        
        //Up
        case 2:
            if(validMove(aGoblin.getX(), aGoblin.getY()-1))
                aGoblin.setY(aGoblin.getY()-1);
            break;
        
        //Down
        case 3:
            if(validMove(aGoblin.getX(), aGoblin.getY()+1))
                aGoblin.setY(aGoblin.getY()+1);
            break;
    }
}

void game::spawnGoblins(){
    int x, y;
    goblin temp;
    //Using goblinvec.size instead of 0 incase there are already goblins
    for(int i = goblinVec.size(); goblinVec.size()<numGoblins; i++){
        x = rand() % CONSOLE_WIDTH;
        y = rand() % CONSOLE_HEIGHT;
        if(map[y][x] == FLOOR){
            temp.setX(x);
            temp.setY(y);
            goblinVec.push_back(temp);
        }
    }
}

void game::printGame(){
    //Copy map to printbuffer
    //Probably not the most efficent way to do things
    for(int i = 0; i < CONSOLE_HEIGHT; i++)
        for(int j =0; j < CONSOLE_WIDTH + 1; j++)
            printBuff[i][j] = map[i][j];
    
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

void game::movePlayer(char input){
    switch(input){
        case KB_LEFT:
            if(validMove(player1.getX()-1, player1.getY()))
                player1.setX(player1.getX() -1);
            break;
            
        case KB_RIGHT:
            if(validMove(player1.getX()+1, player1.getY()))
                player1.setX(player1.getX() + 1);
            break;
        
        case KB_UP:
            if(validMove(player1.getX(), player1.getY()-1))
                player1.setY(player1.getY() - 1);
            break;
        
        case KB_DOWN:
            if(validMove(player1.getX(), player1.getY()+1))
                player1.setY(player1.getY() + 1);
            break;
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
    while(input != 'Q'){
        movePlayer(input);
        
        //Quick copy & paste here, felt wrong that a player
        //and goblin could walk past each other
        if(goblinCollison()){
           std::cout<<"You have been eaten by a grue :("<<std::endl;
           std::cout<<"Don't go north next time, dummy"<<std::endl;
           std::cout<<"http://www.explainxkcd.com/wiki/index.php/91:_Pwned"<<std::endl;
           break;
        }
        
        for(int i = 0; i<goblinVec.size(); i++){
        moveGoblinRandomly(goblinVec[i]);
        }
        
        printGame();
        
        if(goblinCollison()){
           std::cout<<"You have been eaten by a grue :("<<std::endl;
           std::cout<<"Don't go north next time, dummy"<<std::endl;
           std::cout<<"http://www.explainxkcd.com/wiki/index.php/91:_Pwned"<<std::endl;
           break;
       }
        
        std::cin>>input;
    }
    
}



