#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <cstdlib>
#include <unistd.h>

template <typename T>
struct Node {
    T element;
    Node *next;
}; // struct Node

template<class T>
class LinkedList {
    private:
        Node<T> *first;
        size_t length;
    public:    
        LinkedList();
	~LinkedList();

        void queue(T);
        T* dequeue();
        T* peek();
        bool isEmpty();
}; // class LinkedList

#endif // _LINKED_LIST_H
