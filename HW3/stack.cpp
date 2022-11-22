#include "stack.h"
#include <stdio.h>

integer::integer()
{
    data = 0;
}

integer::~integer()
{
}

int integer::print()
{
    printf("%d ", data);
    return 0;
}

int integer::set_value(int in)
{
    data = in;
    return data;
}