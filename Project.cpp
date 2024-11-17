#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "Player.h"

using namespace std;

#define DELAY_CONST 100000
#define MAX_SPEED 10

Player *myPlayer;
GameMechs *myGameMechs;
objPos *mySnake;
char  input;
bool exitFlag = false;
bool loseFlag = false;
int score = 0;
int boardSizeX = 20;
int boardSizeY = 10;
int speed = 1;
enum Direction {
    STOP,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    DEFAULT = STOP
};

Direction currentDirection = Direction::STOP;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGameMechs->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    MacUILib_Delay(100000);
    myGameMechs = new GameMechs();
    myPlayer = new Player(myGameMechs);
    
}

void GetInput(void)
{
   if (MacUILib_hasChar()) { // Check for input
        myGameMechs->setInput(MacUILib_getChar());

        switch (myGameMechs->getInput()) {
            case 'w': case 'W': 
                if (currentDirection != Direction::DOWN){
                    currentDirection = UP; 
                    myPlayer->updatePlayerDir();    
                }
                break;
            case 's': case 'S': 
                if (currentDirection != Direction::UP){
                    currentDirection = DOWN; 
                    myPlayer->updatePlayerDir();
                }
                    break;
            case 'a': case 'A': 
                if (currentDirection != Direction::RIGHT){
                    currentDirection = LEFT; 
                    myPlayer->updatePlayerDir();
                }
                break;
            case 'd': case 'D': 
                if (currentDirection != Direction::LEFT) {
                currentDirection = RIGHT; 
                myPlayer->updatePlayerDir();
                }
                break;
            case ' ': 
                myGameMechs->setExitTrue(); 
                break;       // Exit on space
            case 'q': case 'Q':                  // Change speed
                speed = (speed < MAX_SPEED) ? speed + 1 : 1;
                break;
        }
        myPlayer->movePlayer();
        
    }
}


void RunLogic(void)
{
    if (currentDirection != Direction::STOP) {
        myPlayer->movePlayer();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    objPos playerPos = myPlayer->getPlayerPos();

    MacUILib_printf("Player Pos [x, y, sym]: %d, %d, %c\n", playerPos.pos->x, playerPos.pos->y, playerPos.symbol);
    MacUILib_printf("Position: (%d, %d)\n", myPlayer->getPlayerPos().pos->x,  myPlayer->getPlayerPos().pos->y);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    
    delete myPlayer;
    delete myGameMechs;

    MacUILib_uninit();
}
