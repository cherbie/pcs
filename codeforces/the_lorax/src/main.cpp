#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <cstdlib>
#include <memory>
#include <iterator>
#include <set>
#include "tests.h"

/**
TODO:
 - stdin will be using the index values of integers starting at 1 and not 0 ... this currently breaks the program
 - Implement the traversal logic
 - handle node value updates
 - test node value updates
**/

int main(int argc, char* argv[]);

struct Node {
    unsigned int id;
    std::shared_ptr<long> value;
    std::list<std::shared_ptr<Node>> edges; // adjacency list
}

class Traversal {
    // TODO
    private:
        std::vector<std::shared_ptr<Node>> _bfs; // breadth first search sequence

    private:
        void _set_fibonacci_heap();
    
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = long;
        using difference_type = long;
        using pointer = long*;
        using reference = long&;
    
    public:
        Traversal();
        ~Traversal();
        operator++();
        operator--();
}

class Tree {
    private:
        std::vector<std::shared_ptr<Node>> _nodes;

        friend class Traversal;
    
    public:
        Tree();
        Tree(unsigned int);
        ~Tree();

    public:
        void add_edge(unsigned int, unsigned int);
        std::shared_ptr<Node> get(unsigned int);
}

Traversal::Traversal(): _bfs(std::vector<std::shared_ptr<Node>>()) { 
    this->_set_fibonacci_heap();
}

Traversal::Traversal(unsigned int num_nodes): _bfs(std::vector<std::shared_ptr<Node>>(num_nodes)) {
    this->_set_fibonacci_heap();
}

Traversal::~Traversal() { }

/**
 Note:
 - Graph assumed to consist entirely of connected components (expand by implementing priority queue of trees)
*/
void Traversal::_set_fibonacci_heap() {
    auto less_than_cmp_nodes = [=](std::shared_ptr<Node> left, std::shared_ptr<Node> right) { return *(left->value) < *(right->value) };
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, decltype(less_than_cmp_nodes)> p_queue(less_than_cmp_nodes);

    for (auto it = this->_nodes.begin(); it != this->_nodes.end(); ++it) {
        p_queue.push(*it);
    }

    this->_bfs.clear();
    {
        std::set<unsigned int> seen = std::set<unsigned int>(this->_nodes.size());
        std::queue<std::shared_ptr<Node>> queue = std::queue<std::shared_ptr<Node>>(this->_nodes.size());

        auto it_window = p_queue.begin();
        auto it_end = p_queue.end();
        while (seen.size() < num_nodes && it_window != it_end) {
            std::shared_ptr<Node> node = *it_window;
            this->_bfs.push_back(node);
            auto edge_it_begin = node->edges.begin();
            auto edge_it_end = node->edges.end();
            for (auto edge_it = edge_it_begin; edge_it != edge_it_end; ++edge_it) {
                std::shared_ptr<Node> child = *edge_it;
                if (seen.find(child->id) == seen.end()) { // not yet seen
                    this->_bfs.push_back(child);
                    seen.insert(child->id);
                }
            }
            ++it_window;
        }
    }
}

class LoraxAlgorithm {
    private:
        Tree _tree;
    
    public:
        LoraxAlgorithm();
        LoraxAlgorithm(unsigned int);
        ~LoraxAlgorithm();

    public:
        /** Number of roots crossing edge */
        void search(unsigned int, unsigned int);
        /** Update node value */
        void update_node(unsigned int, long);
        /** Add edge to graph */
        void add_edge(unsigned int, unsigned int);
};

Tree::Tree(): _nodes(std::vector<shared_ptr<Node>>()) { }

Tree::Tree(unsigned int num_nodes): _nodes(std::vector<shared_ptr<Node>>()) {
    for (unsigned int i = 0; i < num_nodes; ++i) {
        std::shared_ptr<Node> node = std::make_shared<Node>();
        node->id = i;
        node->value = std::make_shared<long>(0);
        node->edges = std::list<std::shared_ptr<Node>>();
        this->_nodes.push_back(node);
    }
}

Tree::~Tree() { }

// Add edge to node graph
void Tree::add_edge(unsigned int parent_id, unsigned int child_id) {
    std::shared_ptr<Node> parent_node = this->_nodes.at(parent_id);
    std::shared_ptr<Node> child_node = this->_nodes.at(child_id);
    parent_node->edges.push(child_node);
    child_node->edges.push(parent_node);
}

// Get the value / weight of a particular node
std::shared_ptr<Node> AdjacencyList::get(unsigned int node_id) {
    return this->_nodes.at(node_id);
}

LoraxAlgorithm::LoraxAlgorithm(): _tree(Tree()) { }

LoraxAlgorithm::LoraxAlgorithm(unsigned int num_nodes): _tree(Tree(num_nodes)) { }

LoraxAlgorithm::~LoraxAlgorithm() { }

void LoraxAlgorithm::add_edge(unsigned int parent, unsigned int child) {
    this->_tree.add_edge(parent, child);
}

void LoraxAlgorithm::update_node(unsigned int node_id, long sum) {
    std::shared_ptr<Node> node = this->_tree.get(node_id);
    *(node->value) += sum;
}

long LoraxAlgorithm::search(unsigned int parent, unsigned int child) {
    // TODO
}

#ifndef _TESTS_H

int main(int argc, char* argv[]) {
    unsigned int num_tests;
    std::cin >> num_tests;
    for (unsigned int i = 0; i < num_tests; ++i) {
        unsigned int num_nodes, num_queries;
        std::cin >> num_nodes >> num_queries;
        LoraxAlgorithm fib_heap = LoraxAlgorithm(num_nodes);

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

#else

int main(int argc, char* argv[]) {
    
}

#endif