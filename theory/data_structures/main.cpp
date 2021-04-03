#include <iostream>
#include <cstdlib>
#include <csignal>
#include <unistd.h>
#include <vector>

#include "lib/linked_list.hpp"

void signal_callback_handler(int);
int test_linked_list(LinkedList<int>&);

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

int main() {
    signal(SIGINT, signal_callback_handler); // register signal and signal handler
    std::cout << "<Ctrl-C> to exit program" << std::endl;
    LinkedList<int> list;
    return test_linked_list(list);
}
