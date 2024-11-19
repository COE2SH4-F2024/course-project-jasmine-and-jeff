#include "objPos.h"

// Constructor Methods
//=====================================================================

// Default Constructor
objPos::objPos() 
{
    pos = new Pos; // Create pointer to struct on heap
                   // stores single object of type pos -> (pos.x = _ , pos.y = _ )
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

// Parameterized Constructor
objPos::objPos(int xPos, int yPos, char sym) 
{
    pos = new Pos;
    pos->x = xPos; 
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule
//=====================================================================

// Destructor
objPos::~objPos() 
{
    delete pos; // deallocation
    pos = nullptr;
}

// Copy Constructor
objPos::objPos(const objPos& o) 
{
    pos = new Pos;

    // Copy the x,y values and symbol from source object
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol; 
}

// Copy Assignment Operator 
objPos& objPos::operator=(const objPos& o)
{
    if(this != &o) // Self-assignment check
    {
        // Free the existing memory to prevent memory leaks
        delete pos;
        
        // Allocate new memory and copy contents from source object
        pos = new Pos;
        pos->x = o.pos->x;
        pos->y = o.pos->y;
        symbol = o.symbol;
    }
    return *this;
}

// Setter Methods
//=====================================================================
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Getter Methods
//=====================================================================
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
