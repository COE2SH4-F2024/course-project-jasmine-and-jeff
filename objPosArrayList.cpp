#include "objPosArrayList.h"
#include <iostream>

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP; 
    listSize = 0; 
    aList = new objPos[arrayCapacity];
}

objPosArrayList::~objPosArrayList()
{
    delete [] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize >= arrayCapacity){
        std::cout << "Array is full." << std::endl;
        return;
    }
    for (int i = listSize; i > 0; --i){
        aList[i] = aList[i-1];
    }   
    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize >= arrayCapacity){
        std::cout << "Array is full." << std::endl;
        return;
    }
    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    if (listSize == 0){
        std::cout << "Array is empty." << std::endl;
        return;
    }
    for (int i = 0; i < listSize - 1; ++i){
        aList[i] = aList[i+1];
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
    if (listSize == 0){
        std::cout << "Array is empty." << std::endl;
        return;
    }
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    if (listSize == 0){
        std::cout << "Array is empty." << std::endl;
        return objPos();
    }
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    if (listSize == 0){
        std::cout << "Array is empty." << std::endl;
        return objPos();
    }
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    if (index < 0 || index >= listSize){
        std::cout << "Index out of range." << std::endl;
        return objPos();
    }
    return aList[index];
}