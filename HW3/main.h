#ifndef _MAIN_H
#define _MAIN_H

#include "stack.h"

typedef enum{
    one         = '1',
    zero        = '0',
    donotcare   = '-'
}ELEMENT;

class implements
{
private: 
    bool builded;
    int length;
    ELEMENT* element;
public:
    implements();
    ~implements();
    int generate(int size);
    int set_element(int index, ELEMENT value);
};

implements::implements()
{ 
    builded = false;
}

int implements::generate(int size)
{
    element = new ELEMENT[size];
    length = size;
    return 0;
}

int implements::set_element(int index, ELEMENT value)
{
    if(index < 0 || index >= length) return 1;
    element[index] = value;
}

implements::~implements()
{
    if(builded)
        delete [] element;
}


#endif