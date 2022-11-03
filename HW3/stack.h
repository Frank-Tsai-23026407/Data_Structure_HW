#ifndef _STACK_H
#define _STACK_H

template <class T> class stack;

template <class T>
class stackNode
{
    friend class stack<T>;
private:
    T data;
    stackNode<T> *link;
};

template <class T>
class stack{
private:
    stackNode<T> *first; 
public:
    stack();
    ~stack();
    int push(T data);
    int pop(T &data);
    int print();
};

#include "stack.tpp"

#endif
