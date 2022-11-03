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
int stack<T>::pop(T &data)
{
    data = first->data;
    first = first->link;
    return 0;
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
    return first == 0;
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