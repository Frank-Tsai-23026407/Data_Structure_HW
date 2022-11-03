#ifndef _STACK_H
#define _STACK_H

#include<stdio.h>

template <class T> class stack;
template <class T> class stackNode;
template <class T> class stackIterater;

template <class T>
class stackNode
{
    friend class stack<T>;
    friend class stackIterater<T>;
private:
    T data;
    stackNode<T> *link;
};

template <class T>
class stack{
    friend class stackIterater<T>;
private:
    stackNode<T> *first; 
public:
    stack();
    ~stack();
    int push(T data);
    bool pop(T &data);
    int print();
    bool isEmpty();
    int fprint(FILE *file);
    void inherient(stack<T> i);
    void clear();
};

template <class T>
class stackIterater
{
private:
    stackNode<T> *first;
    stackNode<T> *here;
public:
    stackIterater();
    ~stackIterater();
    void iterater(stack<T> s);
    bool next(T &data);
    void re();
};

#include "stack.tpp"

#endif
