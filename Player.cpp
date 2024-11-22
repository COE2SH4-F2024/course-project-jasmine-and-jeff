#include "Player.h"
#include <iostream>
#include "MacUILib.h"

// Constructor
// ===================================================
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP; // Set the initial direction of the player to STOP

    // more actions to be included

    // Construct player 
    // Starting player position is at middle of board
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2; 
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2; 
    playerPos.symbol = '@';
}

// Destructor
// ===================================================
Player::~Player()
{
    // delete any heap members here
    // no keyword "new" in the constructor
    // leave the descructor empty FOR NOW
}

// Other
// ===================================================
objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos array list
    return playerPos; // playerPos holds x, y and symbol 
}

void Player::updatePlayerDir()
{
    // Get input from the GameMechs object
    char input = mainGameMechsRef -> getInput();

    // PPA2 input processing logic   
    switch(input)
    {                      
        case ' ':  // exit on space key
            mainGameMechsRef->setExitTrue(); // Set exit flag
            break;

        case 'i':  // Debug key: Increment score
            mainGameMechsRef->incrementScore();
            break;

        case 'l':  // Debug key: test lose flag
            mainGameMechsRef->setLoseFlag();
            break;

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

        default: 
            break;
    }
    mainGameMechsRef->clearInput(); // Clear the input after processing
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();
    
    // Define valid ranges for player movement (excluding boundary)
    int validMinX = 1;
    int validMaxX = boardSizeX - 2;
    int validMinY = 1;
    int validMaxY = boardSizeY - 2;

    switch (myDir) {
        case UP:
            // Move player up but ensure we don't go past the boundary
            if (playerPos.pos->y > validMinY) {
                playerPos.pos->y -= 1;
            } else {
                // Wrap around to the bottom (valid area)
                playerPos.pos->y = validMaxY;
            }
            MacUILib_printf("Y Position: %d", playerPos.pos->y);
            break;

        case DOWN:
            // Move player down but ensure we don't go past the boundary
            if (playerPos.pos->y <= validMaxY) {
                playerPos.pos->y += 1;
            } else {
                // Wrap around to the top (valid area)
                playerPos.pos->y = validMinY;
            }
            MacUILib_printf("Y Position: %d", playerPos.pos->y);
            break;

        case LEFT:
            // Move player left but ensure we don't go past the boundary
            if (playerPos.pos->x > validMinX) {
                playerPos.pos->x -= 1;
            } else {
                // Wrap around to the right (valid area)
                playerPos.pos->x = validMaxX;
            }
            MacUILib_printf("X Position: %d", playerPos.pos->x);
            break;

        case RIGHT:
            // Move player right but ensure we don't go past the boundary
            if (playerPos.pos->x <= validMaxX) {
                playerPos.pos->x += 1;
            } else {
                // Wrap around to the left (valid area)
                playerPos.pos->x = validMinX;
            }
            MacUILib_printf("X Position: %d", playerPos.pos->x);
            break;

        default:
            // No movement if the direction is invalid
            break;
    }
}

// More methods to be added