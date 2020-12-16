#include "linked_list.hpp"

template <class T>
LinkedList<T>::LinkedList(void): first(nullptr), length(0) {}

template <class T>
void LinkedList<T>::queue(T element) {
    Node<T> *node{ new Node<T> { element, nullptr} };
    if (this->first == nullptr)
        this->first = node;
    else {
        Node<T> *current = this->first;
        while ( current->next != nullptr)
            current = current->next;
        current->next = node;
    }
    this->length++;
}

template <class T>
bool LinkedList<T>::isEmpty(void) {
    return this->length == 0;
}

template <class T>
T* LinkedList<T>::dequeue(void) {
    if (this->length == 0)
        return nullptr;
    int *element { new int }; // allocate integer worth of memory
    Node<T> *head = this->first;
    *element = head->element;
    this->first = this->first->next;
    this->length--;
    delete head; // return memory to operating system
    return element;
}

template <class T>
T* LinkedList<T>::peek(void) {
    if (this->length == 0)
        return nullptr;
    else return this->first->element;
}