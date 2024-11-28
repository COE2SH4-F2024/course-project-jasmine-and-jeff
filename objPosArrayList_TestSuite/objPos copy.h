#ifndef OBJPOS_H
#define OBJPOS_H

// Not really a C++ thing
typedef struct // store x and y positions
{
    int x;
    int y;
} Pos;

class objPos
{
    public:
        Pos* pos;        
        char symbol;
        
        // Constructors
        objPos();
        objPos(int xPos, int yPos, char sym);
        
        // Respect the rule of six / minimum four
        // [TODO] Implement the missing special member functions to meet the minimum four rule

        // Destructor
        ~objPos();

        // Copy Constructor
		objPos(const objPos& o);

		// Copy Assignment Operator 
		objPos& operator=(const objPos& o);
        
        // Setters
        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  

        // Getters
        objPos getObjPos() const;
        char getSymbol() const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
        
        // Other Interface Methods (Implementors)
        bool isPosEqual(const objPos* refPos) const;
};

#endif