#include <iostream>
#include "MacUILib.h" // not using cout because it is synchronous printing, whereas MacUILIb_printf is asynchronous
#include "objPos.h" // include objPos class
#include "Player.h" // include Player class

using namespace std;

#define DELAY_CONST 100000
#define BOARD_HEIGHT 9
#define BOARD_WIDTH 19

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
    MacUILib_printf("\n");  

    // DRAWING THE GAME BOARD
    for(int y = 0; y <= BOARD_HEIGHT; y++) // Iterate through each character location on the game board
    {
        for(int x = 0; x <= BOARD_WIDTH; x++)
        {
            // Top and bottom boundaries
            if(y == 0 || y == BOARD_HEIGHT)
                MacUILib_printf("#");

            // Left and right boundaries
            else if(x == 0 || x == BOARD_WIDTH)
                MacUILib_printf("#");
            
            // Player object position (only if not on a boundary)
            else if(x == playerPos.pos->x && y == playerPos.pos->y)
                MacUILib_printf("%c", playerPos.symbol); // Print the player symbol

            // inner space
            else
                MacUILib_printf(" ");
        }
        MacUILib_printf("\n");  // Move to the next line after printing the row
    }
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
