#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "GameMechs.h"


class Food
{
    private:
        // Need a reference to the Main Game Mechanisms
        GameMechs* myGM;
        objPos foodPos;
    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList* blockOffList);
        objPos getFoodPos() const;

};

#endif