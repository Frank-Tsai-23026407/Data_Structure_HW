#include <stdio.h>
#include <stdlib.h>
#include <string> 
#include "stack.h"

STACK::STACK(int stack_capacity):capacity(stack_capacity)
{
    stack = new int[stack_capacity];
    top_index = -1;
}

STACK::~STACK()
{
    delete [] stack;
}

int STACK::top()
{
	return stack[top_index];
}

bool STACK::isEmpty()
{
    return top_index == -1;
}

void STACK::push(int item)
{
    if(top_index == capacity - 1) throw "Stack is full";
    stack[++top_index] = item;
    // printf("%d: %d\n", top_index, stack[top_index]);
}

int STACK::pop()
{
    if(isEmpty()) throw "Stack is empty";
    // printf("%d: %d\n", top_index, stack[top_index]);
    return stack[top_index--];
}
