#include "linked_list.h"

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
    else return this.first->element;
}

void signal_callback_handler(int signum) {
    std::cout << "Cleanly exiting program: " << signum << std::endl;
    exit(signum); // terminate
}

/**
 * Test certain use cases of the linked list ( memory leaks etc )
 */
int test_linked_list(LinkedList<int>& list) {
    int input;
    std::vector<int> inputs {1, 2, 3, 4, 5};
    
    std::cout << "Inputs:" << std::endl;
    for(std::vector<int>::iterator i = inputs.begin(); i != inputs.end(); i++) {
        list.queue(*i);
        std::cout << *i << "\x20";
    }
    std::cout << std::endl;

    std::cout << "Operation: Dequeue two elements" << std::endl;
    std::cout << *list.dequeue() << " : " << *list.dequeue() << std::endl;

    std::cout << "Operation: Enqueue one element: ";
    std::cin >> input;
    list.queue(input);

    std::cout << "Print resulting linked list" << std::endl;
    while (!list.isEmpty())
        std::cout << *list.dequeue() << "\x20";
    std::cout << std::endl;

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    signal(SIGINT, signal_callback_handler); // register signal and signal handler
    std::cout << "<Ctrl-C> to exit program" << std::endl;
    LinkedList<int> list;
    return test_linked_list(list); // infinite loop
}
