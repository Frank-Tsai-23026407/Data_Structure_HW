#include <string> 

#ifndef _STACK_H
#define _STACK_H
// #include "stack.cpp"
class STACK
{
private:
    int capacity;
    int top_index;
    int* stack;
public:
    STACK(int stack_capacity);
    ~STACK();

	int top();
    bool isEmpty();
    void push(int item);
    int pop();
};

typedef struct CITY
{
    char name[1000];
    int source;
    int index;
    int cost;
    int num_direction;
    int direction[10000];
 }CITY;

#endif
