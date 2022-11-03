#include <stdio.h>

template <class T>
int stack<T>::push(T data)
{
    stackNode<T> *new_one = new stackNode<T>;
    new_one->data = data;
    new_one->link = first;
    first = new_one;
    return 0;   
}

template <class T>
bool stack<T>::pop(T &data)
{
    if(isEmpty()) return false;
    data = first->data;
    first = first->link;
    return true;
}

template <class T>
int stack<T>::print()
{
    stackNode<T> *pointer = first;
    while(pointer)
    {
        pointer->data.print();
        printf(" ");
        pointer = pointer->link;
    }
    return 0;
}

template <class T>
bool stack<T>::isEmpty()
{
    if(first) return false;
    return true;
}

template <class T>
void stack<T>::inherient(stack<T> i)
{
    first = i.first;
}

template <class T>
void stack<T>::clear()
{
    first = 0;
}

template <class T>
stack<T>::stack()
{
	first = 0;
}

template <class T>
stack<T>::~stack()
{
    stackNode<T>* next;
    while(first)
    {
        next = first->link;
        delete first;
        first = next;
    }
}


template <class T>
int stack<T>::fprint(FILE *file)
{
    stackNode<T> *pointer = first;
    while(pointer)
    {
        pointer->data.fprint(file);
        if(pointer->link) fprintf(file, ", ");
        pointer = pointer->link;
    }
    fprintf(file, "\n");
    return 0;
}

template <class T>
stackIterater<T>::stackIterater()
{
}

template <class T>
void stackIterater<T>::iterater(stack<T> s)
{
    first = s.first;
    here  = s.first;
}

template <class T>
stackIterater<T>::~stackIterater()
{
}

template <class T>
bool stackIterater<T>::next(T &data)
{
    if(here)
    {
        data = here->data;
        here = here->link;
        return true;
    }
    else
        return false;
}

template <class T>
void stackIterater<T>::re()
{
    here = first;
}