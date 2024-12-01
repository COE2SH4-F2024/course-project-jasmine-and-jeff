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
    
    srand(time(NULL));
    
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
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); // asynchronous non-blocking input
    
    objPosArrayList* playerPos = myPlayer->getPlayerPos(); // Create an object that will receive player position
    int playerSize = playerPos->getSize(); 

    objPos foodPos = myFood->getFoodPos();

    int boardX = myGM->getBoardSizeX(); // 20
    int boardY = myGM->getBoardSizeY(); // 19

    bool printFlag = false; // checks if player segment has been printed or not

    // GAME BOARD PRINTING LOGIC
    //=====================================================

    // Iterate through each character location on the game board
    for(int i = 0; i < boardY; i++)  // y-direction
    {
        for(int j = 0; j < boardX; j++)  // x-direction 
        {
            printFlag = false; // Reset flag for this cell
        
            // Step 1:  Iterate though the playerPos array list to print all the segments out
            for(int k = 0; k < playerSize; k++)
            {
                objPos thisSeg = playerPos->getElement(k); // get the segment at index k of list

                // Step 2: Check if the current segment (x, y) pos matches the (j, i) index coordinate
                if((thisSeg.pos->x == j && thisSeg.pos->y == i) && (thisSeg.pos->x != 0 && thisSeg.pos->y != 0)) // the (0,0) condition is due to bedbug issue
                {
                    // If yes, print the symbol
                    MacUILib_printf("%c", thisSeg.symbol);
                    printFlag = true;
                    break; // Exit loop since we've printed for this cell
                }   
            }

            // WATCH OUT!!
            //  We need to skip the if-else block below if we have printed something in the for loop!
            if(!printFlag)
            {
                if(i == 0 || i == boardY-1 || j == 0 || j == boardX-1) // Draw Border
                    MacUILib_printf("%c", '#');
                        
                else if(i == foodPos.pos->y && j == foodPos.pos->x) // Draw Food Character (only if not on a boundary or Player)
                    MacUILib_printf("%c", foodPos.symbol);

                else   // Draw Spaces
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
    MacUILib_printf("Score: %d\n", myGM->getScore());

    // Debugging Messages
    //=====================================================
    MacUILib_printf("\n\n===Debugging Messages===\n");
    // MacUILib_printf("Current Player Coordinates [x, y, sym]: [%d, %d, %c]\n", playerPos.pos->x, playerPos.pos->y, playerPos.symbol); 
    MacUILib_printf("Current Food Coordinates: [x, y]: [%d, %d, %c]\n", foodPos.pos->x, foodPos.pos->y, foodPos.symbol);
    MacUILib_printf("Snake (List) size: %d\n", playerPos->getSize());

    // Print snake positions
    for(int k = 0; k < playerSize; k++)
    {
        objPos seg = playerPos->getElement(k);
        MacUILib_printf("Snake[%d] = (%d, %d, %c)\n", k, seg.pos->x, seg.pos->y, seg.symbol);
    }

    // Temporary Debug keys
    //MacUILib_printf("Press 'i' to increment the Score\n");  
    MacUILib_printf("Press 'g' to test the random Food generation. \n");
    MacUILib_printf("Press ' ' to Exit the Program\n"); 
}

void LoopDelay(void)
{
    MacUILib_Delay(myGM->getDelayAmount());  // Use delayAmount for dynamic speed
}

void CleanUp(void)
{
    // End Game Messages  
    if(myGM->getExitFlagStatus() && myGM->getLoseFlagStatus()) 
        MacUILib_printf("\nYou lost! Game Over.\n");

    else if(myGM->getExitFlagStatus()) 
        MacUILib_printf("\nGame Ended by Player Command.\n");
    
    // Deallocation
    delete myPlayer; 
    delete myGM;
    delete myFood;    
    MacUILib_uninit();
}

