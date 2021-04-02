#include <iostream>
#include <cstdlib>
#include <csignal>
#include <unistd.h>
#include <vector>
#include "linked_list.hpp"
#include "linked_list.cpp" // linker issue

void signal_callback_handler(int);
int test_linked_list(LinkedList<int>&);