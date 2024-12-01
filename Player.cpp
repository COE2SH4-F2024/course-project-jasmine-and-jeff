#include "Player.h"
#include <iostream>
#include "MacUILib.h"

// Constructor
// ===================================================
Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    playerPosList = new objPosArrayList();
    playerFoodRef = thisFoodRef;

    myDir = STOP; // Set the initial direction of the player to STOP

    // Insert temporary head position into list (Starting at middle of board)
    objPos headPos(mainGameMechsRef->getBoardSizeX() / 2,
                   mainGameMechsRef->getBoardSizeY() / 2,
                '@');

    playerPosList->insertHead(headPos); // list contains only one element
}

// Destructor
// ===================================================
Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

// Other
// ===================================================
objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the player objPos array list
    return playerPosList; 
}

void Player::updatePlayerDir()
{
    // Get input from the GameMechs object
    char input = mainGameMechsRef -> getInput();

    // PPA2 input processing logic   
    switch(input)
    {              
        // TEMPORARY DEBUG KEYS
        //=====================================================        
        // case 'i':  // test increment score
        //     mainGameMechsRef->incrementScore();
        //     break;

        case 'g':  // test generate food
            playerFoodRef->generateFood(getPlayerPos());
            //mainGameMechsRef->mainGameFoodRef(getPlayerPos());
            break;
        //======================================================

        case 'w':  // Move Up
        case 'W':
            if(myDir != UP && myDir != DOWN) // Move UP only if currently moving horizontally
                myDir = UP;
            break;

        case 'a':  // Move Left
        case 'A':
            if(myDir != LEFT && myDir != RIGHT) // Move LEFT only if currently moving vertically
                myDir = LEFT;  
            break; 

        case 's':  // Move Down
        case 'S':
            if(myDir != UP && myDir != DOWN) // Move DOWN only if currently moving horizontally
                myDir = DOWN;  
            break; 

        case 'd':  // Move Right
        case 'D':
            if(myDir != LEFT && myDir != RIGHT) // Move RIGHT only if currently moving vertically
                myDir = RIGHT;  
            break;

        case '=':  // Increase speed
            mainGameMechsRef->increaseSpeed();
            break;

        case '-':  // Decrease speed
            mainGameMechsRef->decreaseSpeed();
            break;

        default: 
            break;
    }
    mainGameMechsRef->clearInput(); // Clear the input after processing

}

void Player::movePlayer()
{
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();

    // Step 1: Create a temporary objPos to calculate the new head position
    objPos tmpHead = playerPosList->getHeadElement();  // get head element of playerPosList
    
    switch(myDir) 
    {
        // Step 2: Calculate the new position of the head using the tmpHead objPos 
        case UP:
            tmpHead.pos->y--;
             
            if(tmpHead.pos->y == 0) { // if at top boundary wraparound to bottom
                tmpHead.pos->y = boardSizeY - 2; // 10 - 2 = 8
            }
            break;

        case DOWN:
            tmpHead.pos->y++;

            if(tmpHead.pos->y == boardSizeY - 1){ // if at bottom boundary wraparound to top
                tmpHead.pos->y = 1; 
            }
            break;

        case LEFT:
            tmpHead.pos->x--;

            if(tmpHead.pos->x == 0) { // if at left boundary wraparound to right
                tmpHead.pos->x = boardSizeX - 2; // 10-2 = 18
            }
            break;

        case RIGHT:
            tmpHead.pos->x++;

            if(tmpHead.pos->x == boardSizeX-1){ // if at right boundary wraparound to left
                tmpHead.pos->x = 1;
            }
            break;

        case STOP: // No movement
        default: 
            break;
    }

    // Step 3: Insert tmpHead objPos at the head of the list and remove the tail 
    // This simulates the movement effect by:
    // - Adding a new head segment (the snake moves forward in the new direction).
    // - Removing the tail segment (maintains the same length).

    /* i.e. Before insertHead:          playerPosList = [(5, 14, '*'), (5, 13, '*')]

            After insertHead(tmpHead)                 = [(5, 15, '*'), (5, 14, '*'), (5, 13, '*')]
            (new head at (5, 15))

            After removeTail()                        = [(5, 15, '*'), (5, 14, '*')]  
            (tail segment removed)                                                      
            
                              ****** MOVEMENT MAGIC COMPLETE ******    */
    playerPosList->insertHead(tmpHead);  
     
    // Step 4: COLLISION LOGIC  
    //===============================================
    objPos foodPos = playerFoodRef->getFoodPos();

    // Check if the new head position collides with the food
    if(checkFoodConsumption(tmpHead, foodPos)) // If food is eaten
    {
        increasePlayerLength();  // Increase the snake's length
        mainGameMechsRef->incrementScore();  // Increase score
        playerFoodRef->generateFood(playerPosList); // Generate new food
    }
    else // No food consumed
    {
        if(checkSelfCollision(tmpHead, *playerPosList)) // If self-collision occurs
        {
            // If the snake collides with itself, don't remove the tail and end the game
            mainGameMechsRef->setLoseFlag();  // Set lose flag
            mainGameMechsRef->setExitTrue();  // Exit the game loop
        }
        else
            playerPosList->removeTail(); // Remove tail to maintain constant length
    }

}


// More methods to be added
bool Player::checkFoodConsumption(objPos &newHeadPos, objPos &foodPos)
{
    return newHeadPos.isPosEqual(&foodPos);
}

void Player::increasePlayerLength()
{
    int listSize = playerPosList->getSize();
    listSize++;
}

bool Player::checkSelfCollision(objPos &newHeadPos, objPosArrayList &playerPosList)
{
    // Only check for collisions if snake is moving
    if(myDir == STOP) return false;

    bool selfCollision = false;

    // Check for collisions with the snake's body
    for(int i = 1; i < playerPosList.getSize(); i++) // Start from 1 to avoid checking the head
    {
        objPos thisSeg = playerPosList.getElement(i);  // Get the i-th segment of the snake

        if(newHeadPos.isPosEqual(&thisSeg)) // Check if head position matches any body segment
        {
            selfCollision = true; // if so, then collision occured
            break;
        }      
    }
    return selfCollision;
}