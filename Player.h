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

        Player(GameMechs* thisGMRef, Food* thisFoodRef); // Constructor
        ~Player();

        objPosArrayList* getPlayerPos() const; // Upgrade this in iteration 3.      
        void updatePlayerDir();
        void movePlayer();
        
        // More methods to be added here
        bool checkFoodConsumption(objPos &newHeadPos, objPos &foodPos);
        void increasePlayerLength();
        bool checkSelfCollision(objPos &newHeadPos, objPosArrayList &playerPosList);

    private:
        // objPos playerPos;  // Upgrade this in iteration 3.   
        objPosArrayList* playerPosList;    
        // i.e. aList[] = [(5, 3, '*'), (5, 4, '*'), (5, 5, '*')]

        enum Dir myDir;  // Declare a variable "myDir" to hold the current direction

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* playerFoodRef;
};

#endif