#include "qm.h"
#include <stdio.h>

implements::implements()
{ 
    builded = false;
    implemented = false;
}

int implements::generate(int size)
{
    builded = true;
    element = new ELEMENT[size];
    length = size;
    return 0;
}

int implements::set_element(int index, ELEMENT value)
{
    if(index < 0 || index >= length) return 1;
    element[index] = value;
    return 0;
}

implements::~implements()
{
    if(builded)
    {
        delete [] element;
        builded = false;
    }
}

int implements::set_value(int value)
{
    int i;
    for(i = 0; i < length; i++)
    {
        if(value & 0x00000001)
            element[i] = '1';
        else
            element[i] = '0';
        value = value >> 1;
    }
    return 0;
}

bool implements::operator==(implements& t)
{
    bool same = true;
    int i;
    for(i = 0; i < length; i++)
    {
        if(element[i] != t.element[i])
        {
            same = false;
            break;
        }
    }
    return same;
}

bool implements::similar(implements &t, int &index)
{
    int diff = 0;
    int i;
    for(i = 0; i < length; i++)
    {
        if(element[i] != t.element[i])
        {
            if(diff == 1) return false;
            diff++;
            index = i;
        }
    }
    if(diff == 1)
        return true;
    return false;
}

int implements::print()
{
    int i;
    for(i = length-1; i >= 0; i--)
    {
        printf("%c", element[i]);
    }
    return 0;
}

int implements::num_one()
{
    int i, accu;
    accu = 0;
    for(i = length-1; i >= 0; i--)
    {
        if(element[i] == '1') accu++;
    }
    return accu;
}

int implements::fprint(FILE* file)
{
    int i;
    for(i = length-1; i >= 0; i--)
    {
        fprintf(file, "%c", element[i]);
    }
    return 0;
}

void implements::generate_and_copy(implements &t)
{
    generate(t.length);
    for(int i = 0; i < length; i++)
    {
        element[i] = t.element[i];
    }
}

void implements::clear()
{
    element = 0;
    builded = false;
}