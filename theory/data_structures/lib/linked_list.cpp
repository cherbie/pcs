#include "linked_list.hpp"

template <class T>
LinkedList<T>::LinkedList()
: first(nullptr), length(0)
{
}

template <class T>
LinkedList<T>::~LinkedList()
{
    if (first != nullptr)
    {
	delete first;
	length = 0;
    }
}

template <class T>
void LinkedList<T>::queue(T element)
{
    Node<T> *node{ new Node<T> { element, nullptr} };
    if (first == nullptr)
        first = node;
    else {
        Node<T> *current = first;
        while ( current->next != nullptr)
            current = current->next;
        current->next = node;
    }
    length++;
}

template <class T>
bool LinkedList<T>::isEmpty()
{
    return length == 0;
}

template <class T>
T* LinkedList<T>::dequeue()
{
    if (length == 0)
        return nullptr;
    int *element { new int }; // allocate integer worth of memory
    Node<T> *head = first;
    *element = head->element;
    first = first->next;
    length--;
    delete head; // return memory to operating system
    return element;
}

template <class T>
T* LinkedList<T>::peek()
{
    if (length == 0)
        return nullptr;
    else return &(first->element);
}

// needs to be done to avoid linker issues.
// otherwise could place template definitions in
// the header file.
template class LinkedList<int>;

