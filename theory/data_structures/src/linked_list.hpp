#include <cstdlib>
#include <unistd.h>

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

template <typename T>
struct Node {
    T element;
    Node *next;
};

template<class T>
class LinkedList {
    private:
        Node<T> *first;
        size_t length;
    public:    
        LinkedList(void);
        void queue(T);
        T *dequeue(void);
        T *peek(void);
        bool isEmpty(void);
};
#endif