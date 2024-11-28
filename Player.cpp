#include "Player.h"
#include <iostream>
#include "MacUILib.h"

// Constructor
// ===================================================
Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    playerFoodRef = thisFoodRef;
    myDir = STOP; // Set the initial direction of the player to STOP

    // more actions to be included

    // Construct player 
    // Starting player position is at middle of board
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2; 
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2; 
    playerPos.symbol = '*';
    
    // Construct snake body
    snakeBody.insertTail(playerPos);  // Using snakeBody instead of myPlayer
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
        // TEMPORARY DEBUG KEYS
        //=====================================================        
        case 'i':  // test increment score
            mainGameMechsRef->incrementScore();
            break;

        case 'l':  // test lose flag
            mainGameMechsRef->setLoseFlag();
            break;

        case 'g':  // test generate food
            playerFoodRef->generateFood(getPlayerPos());
            break;
        case 'q': // add segments
            snakeBody.insertTail(playerPos);
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
    // PPA3 Finite State Machine logic
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();
    
    // Define valid ranges for player movement (excluding boundary)
    int validMinX = 1;
    int validMaxX = boardSizeX - 1;
    int validMinY = 1;
    int validMaxY = boardSizeY - 1;

    switch (myDir) {
        case UP:
            // Move player up but ensure we don't go past the boundary
            if (playerPos.pos->y > validMinY) {
                playerPos.pos->y -= 1;
            } else {
                // Wrap around to the bottom (valid area)
                playerPos.pos->y = validMaxY;
            }
            break;

        case DOWN:
            // Move player down but ensure we don't go past the boundary
            if (playerPos.pos->y < validMaxY) {
                playerPos.pos->y += 1;
            } else {
                // Wrap around to the top (valid area)
                playerPos.pos->y = validMinY;
            }
            break;

        case LEFT:
            // Move player left but ensure we don't go past the boundary
            if (playerPos.pos->x > validMinX) {
                playerPos.pos->x -= 1;
            } else {
                // Wrap around to the right (valid area)
                playerPos.pos->x = validMaxX;
            }
            break;

        case RIGHT:
            // Move player right but ensure we don't go past the boundary
            if (playerPos.pos->x < validMaxX) {
                playerPos.pos->x += 1;
            } else {
                // Wrap around to the left (valid area)
                playerPos.pos->x = validMinX;
            }
            break;

        default:
            // No movement if the direction is invalid
            break;
    }

    // Update the player's position in the snake body
    snakeBody.insertHead(playerPos);

    // Check for self-collision
    if (checkSelfCollision()) {
        mainGameMechsRef->setLoseFlag();
        return;
    }

    // Check for collision with food
    objPos foodPos = playerFoodRef->getFoodPos();
    // Check for collision with food
    if(this->foodCollision(foodPos)) {
        // Grow the snake
        growSnake();
    }else{
        snakeBody.removeTail();
    }

}


// More methods to be added
void  Player::growSnake(){
    // INcrement the score
    mainGameMechsRef->incrementScore();
    // Generate new food
    playerFoodRef->generateFood(getPlayerPos());
}

bool Player::foodCollision(objPos foodPos){
    // Check for collision with food
    if (playerPos.pos->x == foodPos.pos->x && playerPos.pos->y == foodPos.pos->y) {
        size++;
        return true;
    }
    return false;
}

bool Player::checkSelfCollision() {
    // Only check for collisions if snake is moving
    if(myDir == STOP) return false;
    // Check for collisions with the snake's body
    for(int i = 1; i < snakeBody.getSize(); i++) {
        objPos currentSegment = snakeBody.getElement(i);
        if (currentSegment.pos->x == playerPos.pos->x && currentSegment.pos->y == playerPos.pos->y) {
            mainGameMechsRef->setLoseFlag();
            return true; // Collision detected
        }
    }
    return false; // No collision detected
}

int Player::getSize(){
    return size;
}
