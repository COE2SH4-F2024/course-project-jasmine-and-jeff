#include <iostream>
#include "MacUILib.h" // not using cout because it is synchronous printing, whereas MacUILIb_printf is asynchronous
#include "objPos.h" 
#include "Player.h" 
#include "Food.h" 

using namespace std;

// Global pointers meant to instantiate Objects on the heap
Player *myPlayer;
GameMechs *myGM;
Food *myFood; 

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{
    Initialize();

    while(myGM->getExitFlagStatus() == false || myGM->getLoseFlagStatus() == false)
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

    // Instantiate pointer to object on heap 
    myGM = new GameMechs(); 
    myFood = new Food(myGM); 
    myPlayer = new Player(myGM, myFood);

    myFood->generateFood(myPlayer->getPlayerPos()); // Randomly generate food 
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
    if(myPlayer->checkSelfCollision())
    {
        myGM->setLoseFlag();
        myGM->setExitTrue();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); // asynchronous non-blocking input
    
    objPos playerPos = myPlayer->getPlayerPos(); // Create an object that will receive player position
    objPos foodPos = myFood->getFoodPos();

    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();

    // GAME BOARD PRINTING LOGIC
    //=====================================================

    // Iterate through each character location on the game board
    for(int row = 0; row <= boardY; row++)  // y-direction
    {
        for(int col = 0; col <= boardX; col++)  // x-direction
        {
            bool isSnakeBody = false;
            // Check if current position is part of snake body
            for(int k = 0; k < myPlayer->getSize(); k++)
            {
                playerPos = myPlayer->getSnakeBody(k);  // New method needed in Player class
                if(row == playerPos.pos->y && col == playerPos.pos->x)
                {
                    MacUILib_printf("%c", playerPos.symbol);
                    isSnakeBody = true;
                    break;
                }
            }
            
            if(!isSnakeBody)
            {
                if(row == 0 || row == boardY || col == 0 || col == boardX)
                    MacUILib_printf("%c", '#');
                else if(row == foodPos.pos->y && col == foodPos.pos->x)
                    MacUILib_printf("%c", foodPos.symbol);
                else
                    MacUILib_printf("%c", ' ');
            }
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
    MacUILib_printf("Current Size of Snake: %d\n", myPlayer->getSize());
    MacUILib_printf("Collision Status: %d\n", myPlayer->checkSelfCollision());
    // Temporary Debug keys
    MacUILib_printf("Current Score: %d\n", myGM->getScore());
    MacUILib_printf("Press 'i' to increment the Score\n");  
    MacUILib_printf("Press 'l' to test the Lose Flag. (CURRENTLY NOT FUNCTIONAL)\n");
    MacUILib_printf("Press 'g' to test the random Food generation. \n");
    MacUILib_printf("Press ' ' to Exit the Program\n"); 
    MacUILib_printf("Press 'q' to add segments to snake\n");
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
    if(myGM->getLoseFlagStatus() == true) 
    {
        MacUILib_printf("\n===End of Game Message===\n");   
        MacUILib_printf("Game Over! The Snake Bumped Into Itself.\n");
    }else if(myGM->getExitFlagStatus() == true)
    {
        MacUILib_printf("\n===End of Game Message===\n");
        MacUILib_printf("Game Over! You have exited the game.\n");
    }
    
    
    // Continue clean up below
    delete myPlayer; 
    delete myGM;
    delete myFood;    
    MacUILib_uninit();
}

