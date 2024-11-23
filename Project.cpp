#include <iostream>
#include "MacUILib.h" // not using cout because it is synchronous printing, whereas MacUILIb_printf is asynchronous
#include "objPos.h" // include objPos class
#include "Player.h" // include Player class

using namespace std;

Player *myPlayer; // Global pointer meant to instantiate a Player object on the heap
GameMechs *myGM; // Global pointer meant to instantiate a Game Mechanics object on the heap

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

    myGM->generateFood(myPlayer->getPlayerPos()); // randomly generate food 
}

void GetInput(void)
{
    // Collect input from GameMechs
    myGM->collectAsyncInput();
}

void RunLogic(void)
{  
    myPlayer->updatePlayerDir(); 
    myPlayer->movePlayer(); 
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); // asynchronous non-blocking input
    
    objPos playerPos = myPlayer->getPlayerPos(); // Create an object that will receive player position
    objPos foodPos = myGM->getFoodPos();

    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();

    // GAME BOARD PRINTING LOGIC
    //=====================================================

    // Iterate through each character location on the game board
    for(int row = 0; row <= boardY; row++)  // y-direction
    {
        for(int col = 0; col <= boardX; col++)  // x-direction
        {
            if(row == 0 || row == boardY || col == 0 || col == boardX) // Draw Border
                MacUILib_printf("%c", '#');
            
            else if(row == playerPos.pos->y && col == playerPos.pos->x) // Draw Player Character (only if not on a boundary)
                MacUILib_printf("%c", playerPos.symbol);

            else if(row == foodPos.pos->y && col == foodPos.pos->x) // Draw Food Character (only if not on a boundary or Player)
                MacUILib_printf("%c", foodPos.symbol);

            else    // Draw Spaces
                MacUILib_printf("%c", ' ');
        }
        MacUILib_printf("%c", '\n');  // Move to the next line after printing the row
    }

    // Console Messages
    //=====================================================
    MacUILib_printf("\nCurrent Game Speed: %d\n", myGM->getSpeed());
    MacUILib_printf("Press = to increase the Game Speed\n");
    MacUILib_printf("Press - to decrease the Game Speed\n");

    // Debugging Messages
    //=====================================================
    MacUILib_printf("\n\n===Debugging Messages===\n");
    MacUILib_printf("Current Player Coordinates [x, y, sym]: [%d, %d, %c]\n", playerPos.pos->x, playerPos.pos->y, playerPos.symbol); 
    MacUILib_printf("Current Food Coordinates: [x, y]: [%d, %d, %c]\n", foodPos.pos->x, foodPos.pos->y, foodPos.symbol);

    // Temporary Debug keys
    MacUILib_printf("Current Score: %d\n", myGM->getScore());
    MacUILib_printf("Press 'i' to increment the Score\n");  
    MacUILib_printf("Press 'l' to test the Lose Flag. (CURRENTLY NOT FUNCTIONAL)\n");
    MacUILib_printf("Press 'g' to test the random Food generation. \n");
    MacUILib_printf("Press ' ' to Exit the Program\n"); 
}

void LoopDelay(void)
{
    MacUILib_Delay(myGM->getDelayAmount());  // Use delayAmount for dynamic speed
}

void CleanUp(void)
{
    //MacUILib_clearScreen();   

    // End Game Messages  
    //=====================================================
    if(myGM->getExitFlagStatus() == true) 
    {
        MacUILib_printf("\n===End of Game Message===\n");   
        MacUILib_printf("Game Ended by Player Command.\n");
    }
    else if(myGM->getExitFlagStatus() == true) // (LOSE FLAG IS CURRENTLY NOT FUNCTIONAL IN CLEANUP. WILL BECOME FUNCTIONAL IN NEXT ITER)
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

