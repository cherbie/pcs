#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <memory>

/**
TODO:
 - stdin will be using the index values of integers starting at 1 and not 0 ... this currently breaks the program
 - Implement the fibonacci queue logic
 - handle node value updates
 - test node value updates
**/

int main(int argc, char* argv[]);

class AdjacencyList {
    private:
        std::vector<std::shared_ptr<long>> _nodes;
        std::vector<std::list<unsigned int>> _edges;
    
    public:
        AdjacencyList();
        AdjacencyList(unsigned int);
        ~AdjacencyList();

    public:
        void add_edge(unsigned int, unsigned int);
        std::shared_ptr<long> get(unsigned int);
};

// struct Node {
//     std::shared_ptr<long> value;
//     std::list<std::shared_ptr<Node>> children;
// }

class FibonacciHeap {
    private:
        // std::shared_ptr<Node> _head; // TODO - priority queue / queue of trees required!
        AdjacencyList _adjacency_list;
    
    private:
        /** Organise into fibonacci heap */
        void _sort();
    
    public:
        FibonacciHeap();
        FibonacciHeap(unsigned int);
        ~FibonacciHeap();
    
    public:
        // friend class AdjacencyList; // needed ?
        // // TODO
        // friend class Iterator; // safe traversal of tree / graph

    public:
        /** Update node value */
        void update_node(unsigned int, long);
        /** Add edge to graph */
        void add_edge(unsigned int, unsigned int);
        /** Traverse through graph calculating minimum flow between two vertices */
        long min_flow(unsigned int, unsigned int);
};

int main(int argc, char* argv[]) {
    unsigned int num_tests;
    std::cin >> num_tests;
    for (unsigned int i = 0; i < num_tests; ++i) {
        unsigned int num_nodes, num_queries;
        std::cin >> num_nodes >> num_queries;
        FibonacciHeap fib_heap = FibonacciHeap(num_nodes);

        // -- Graph initialisation
        for (unsigned int j = 0; j < num_nodes - 1; ++j) {
            unsigned int parent, child;
            std::cin >> parent >> child;
            fib_heap.add_edge(parent, child);
        }

        // -- Queries
        for (unsigned int j = 0; j < num_queries; ++j) {
            unsigned int parent, child;
            unsigned long query_value;
            std::cin >> parent >> child >> query_value;
            if ( query_value == 0) {
                std::cout << "DEBUG: sort and find minimum flow between (" << parent << ", " << child << ")" << std::endl;
            } else {
                std::cout << "DEBUG: update value for the following nodes: (" << parent << ", " << child << ") :: to -> " << query_value << std::endl;
            }
        }
    }
    std::exit(EXIT_SUCCESS);
}

AdjacencyList::AdjacencyList() { }

AdjacencyList::AdjacencyList(unsigned int num_nodes) {
    this->_nodes = std::vector<std::shared_ptr<long>> (num_nodes);
    for (unsigned int i = 0; i < num_nodes; ++i) {
        this->_nodes.push_back( std::make_shared<long>(0) ); // initialize
    }
    this->_edges = std::vector<std::list<unsigned int>> (num_nodes);
}

AdjacencyList::~AdjacencyList() { }

// Add edge to node graph
void AdjacencyList::add_edge(unsigned int parent, unsigned int child) {
    this->_edges.at(parent).push_back(child); // todo -- does this work ... get might return a copy?
    this->_edges.at(child).push_back(parent);
}

// Get the value / weight of a particular node
std::shared_ptr<long> AdjacencyList::get(unsigned int node_id) {
    return this->_nodes.at(node_id);
}

FibonacciHeap::FibonacciHeap() { }

FibonacciHeap::FibonacciHeap(unsigned int num_nodes) {
    this->_adjacency_list = AdjacencyList (num_nodes);
    // this->_head = nullptr; // todo priority queue
}

FibonacciHeap::~FibonacciHeap() { }

void FibonacciHeap::add_edge(unsigned int parent, unsigned int child) {
    this->_adjacency_list.add_edge(parent, child);
    
    // Perform this operation in sort ... no point constructing graph when it will be broken down in the sort
    // std::shared_ptr<long> value = this->_adjacency_list.get(child);

    // std::shared_ptr<Node> new_node = std::make_shared<Node>();
    // new_node->value = value;
    // new_node->children = std::list<std::shared_ptr<Node>>();

    // if (this->_head == nullptr) {
    //     this->_head = new_node;
    // } else if (*this->_head->value > *value) { // TODO - convert to do {} while(); ?
    //     new_node->children.push_back(this->_head);
    //     this->_head = new_node;
    // } else {
    //     // TODO - Traverse until value is greater than or empty children node is reached
    //     this->_head->children.push_back(new_node);
    // }
}

void FibonacciHeap::update_node(unsigned int node_id, long sum) {
    std::shared_ptr<long> p_node_value = this->_adjacency_list.get(node_id);
    *p_node_value += sum;
}