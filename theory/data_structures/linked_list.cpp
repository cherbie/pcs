#include "linked_list.h"

template <class T>
LinkedList<T>::LinkedList(void): first(nullptr), length(0) {}

template <class T>
void LinkedList<T>::queue(T element) {
    Node<T> last{ element, nullptr};
    if (this->first == nullptr)
        this->first = &last;
    else {
        Node<T> *current = this->first;
        while ( current->next != nullptr)
            current = current->next;
        current->next = &last;
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
    Node<T> *head = this->first;
    this->first = this->first->next;
    this->length--;
    return &head->element;
}

template <class T>
T* LinkedList<T>::peek(void) {
    if (this->length == 0)
        return nullptr;
    else return this.first->element;
}

int main(int argc, char *argv[]) {
    LinkedList<int> list;
    int element; 
    std::cin >> element;
    list.queue(element);
    
    if (list.isEmpty())
        std::cout << "List is empty";
    else std::cout << *list.dequeue();

    std::cout << std::endl;
    return EXIT_SUCCESS;
}
