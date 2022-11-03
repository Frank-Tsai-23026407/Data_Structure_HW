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
        pointer = pointer->link;
    }
    return 0;
}

template <class T>
stack<T>::stack()
{
	first = 0;
}

template <class T>
stack<T>::~stack()
{
    stackNode* next;
    while(first)
    {
        next = first->link;
        delete first;
        first = next;
    }
}
