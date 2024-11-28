#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "Food.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* thisFoodRe); // Constructor
        
        ~Player();

        objPos getPlayerPos() const; // Upgrade this in iteration 3.       
        void updatePlayerDir();
        void movePlayer();
        void growSnake();
        // More methods to be added here
        bool foodCollision(objPos foodPos);
        bool checkSelfCollision();
        int getSize();
        objPos getSnakeBody(int index) { return snakeBody.getElement(index); }

    private:
        objPos playerPos;  // Upgrade this in iteration 3.       
        objPosArrayList snakeBody;
        objPos currentHead;
        objPos newHead;
        enum Dir myDir;  // Declare a variable "myDir" to hold the current direction
        int size = 1;
        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* playerFoodRef;
};

#endif
