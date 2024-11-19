#include <iostream>
#include "MacUILib.h" // not using cout because it is synchronous printing, whereas MacUILIb_printf is asynchronous
#include "objPos.h" // include objPos class
#include "Player.h" // include Player class

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; // Global pointer meant to instantiate a Player object on the heap
GameMechs *myGM; // Global pointer meant to instantiate a Game Mechanics class


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{
    Initialize();

    while(myGM->getExitFlagStatus() == false)  
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

    myGM = new GameMechs(); // instantiate GM object on heap
    myPlayer = new Player(myGM); // instantiate player object on heap
}

void GetInput(void)
{

}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); // asynchronous non-blocking input

    // Create an object that will receive player position
    objPos playerPos = myPlayer->getPlayerPos(); // use arrow cuz myPlayer is a pointer to a Player object

    // Print player coordinates 
    MacUILib_printf("Player [x, y, sym]: [%d, %d, %c]\n", playerPos.pos->x, playerPos.pos->y, playerPos.symbol);
     
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();   

    delete myPlayer; 
    delete myGM;

    MacUILib_uninit();
}
