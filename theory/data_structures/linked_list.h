#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <vector>

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

int test_link_list(LinkedList<int>&);
void signal_callback_handler(int);