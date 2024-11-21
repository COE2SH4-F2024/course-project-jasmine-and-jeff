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

    myGM = new GameMechs(); // instantiate GM object on heap
    myPlayer = new Player(myGM); // instantiate player object on heap
}

void GetInput(void)
{
    // Collect input from GameMechs
    char user_input = myGM->getInput();

    // Check if a valid input was collected
    if(user_input != 0)  // `0` indicates no input was collected
    {
        myGM->setInput(user_input); // Store the input in the GameMechs object
    }
}

void RunLogic(void)
{
    // Update the player's direction based on input
    myPlayer->updatePlayerDir();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); // asynchronous non-blocking input
    
    objPos playerPos = myPlayer->getPlayerPos(); // Create an object that will receive player position

    // GAME BOARD PRINTING LOGIC
    //=====================================================
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

    // Debugging messages
    //=====================================================
    MacUILib_printf("\n\n");
    MacUILib_printf("===Debugging Messages===\n");
    MacUILib_printf("Key pressed: %c\n", myGM->getInput());  

    // Print player coordinates 
    MacUILib_printf("Current Player Coordinates [x, y, sym]: [%d, %d, %c]\n", playerPos.pos->x, playerPos.pos->y, playerPos.symbol); 

    // Score Debug
    MacUILib_printf("Current Score: %d\n", myGM->getScore());
    MacUILib_printf("Press 'i' to increment the Score\n");  

    // Lose flag debug
    MacUILib_printf("Press 'l' to test the Lose Flag.\n");
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();   

    // End Game Messages
    //=====================================================
    if(myGM->getExitFlagStatus() == true) 
    {
        MacUILib_printf("\n===End of Game Message===\n");   
        MacUILib_printf("Game Ended by Player Command.\n");
    }
    else if(myGM->getLoseFlagStatus() == true) 
    {
        MacUILib_printf("\n===End of Game Message===\n");   
        MacUILib_printf("You lost! The snake bumped into itself.\n");
        myGM->setExitTrue(); // Exit the game loop
    }
    
    // Continue clean up below
    delete myPlayer; 
    delete myGM;

    MacUILib_uninit();
}
