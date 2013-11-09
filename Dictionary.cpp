#include "Dictionary.h"

Dictionary::Dictionary()
{
    for(int i=0;i<4096;i++)
        availability[i] = true;    
}

void Dictionary::setAvailability(int row, bool status)
{
    availability[row] = status;
}

bool Dictionary::getAvailability(int row)
{
    return availability[row];
}
