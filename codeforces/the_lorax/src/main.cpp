#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <cstdlib>
#include <memory>
#include <iterator>
#include <set>
// #include "tests.hpp"

/**
TODO:
 - stdin will be using the index values of integers starting at 1 and not 0 ... this currently breaks the program
 - Implement the traversal logic
 - handle node value updates
 - test node value updates
**/

int main(int argc, char *argv[]);

struct Node
{
    unsigned int id;
    std::shared_ptr<long> value;
    std::list<std::shared_ptr<Node>> edges; // adjacency list
};

class Tree
{
private:
    std::vector<std::shared_ptr<Node>> _nodes;
    std::vector<std::shared_ptr<Node>> _bfs; // breadth first search sequence

public:
    Tree();
    Tree(unsigned int num_nodes);
    ~Tree();

private:
    void _set_fibonacci_heap();

public:
    void add_edge(unsigned int parent, unsigned int child);
    std::shared_ptr<Node> get(unsigned int node_id);
    std::vector<std::shared_ptr<Node>>::iterator begin();
    std::vector<std::shared_ptr<Node>>::iterator end();
};

class LoraxAlgorithm
{
private:
    Tree _tree;

public:
    LoraxAlgorithm();
    LoraxAlgorithm(unsigned int num_nodes);
    ~LoraxAlgorithm();

public:
    /** Number of roots crossing edge */
    long search(unsigned int parent_id, unsigned int child_id);
    /** Update node value */
    void update_node(unsigned int node_id, long value);
    /** Add edge to graph */
    void add_edge(unsigned int parent_id, unsigned int child_id);
};

Tree::Tree() : _nodes(), _bfs() {}

Tree::Tree(unsigned int num_nodes) : _nodes(num_nodes + 1), _bfs()
{
    for (unsigned int index = 1; index <= num_nodes; ++index)
    {
        std::shared_ptr<Node> node = std::make_shared<Node>();
        node->id = index;
        node->value = std::make_shared<long>(0);
        this->_nodes.push_back(node);
    }
}

Tree::~Tree() {}

// Add edge to node graph
void Tree::add_edge(unsigned int parent_id, unsigned int child_id)
{
    std::shared_ptr<Node> parent_node = this->_nodes.at(parent_id - 1);
    std::shared_ptr<Node> child_node = this->_nodes.at(child_id - 1);
    parent_node->edges.push_back(child_node); // could be a problem here ... circular deconstruction
    child_node->edges.push_back(parent_node);
}

// Get the value / weight of a particular node
std::shared_ptr<Node> Tree::get(unsigned int node_id)
{
    return this->_nodes.at(node_id - 1);
}

std::vector<std::shared_ptr<Node>>::iterator Tree::begin()
{
    this->_set_fibonacci_heap();
    return this->_bfs.begin();
}

std::vector<std::shared_ptr<Node>>::iterator Tree::end()
{
    return this->_bfs.end();
}

/**
 Note:
 - Graph assumed to consist entirely of connected components (expand by implementing priority queue of trees)
*/
void Tree::_set_fibonacci_heap()
{
    unsigned int num_nodes = this->_nodes.size();
    auto less_than_cmp_nodes = [=](std::shared_ptr<Node> left, std::shared_ptr<Node> right) { return *(left->value) < *(right->value); };
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, decltype(less_than_cmp_nodes)> p_queue(less_than_cmp_nodes);

    for (auto it = this->_nodes.begin(); it != this->_nodes.end(); ++it)
    {
        p_queue.push(*it);
    }

    this->_bfs.clear();

    {
        std::set<unsigned int> seen = std::set<unsigned int>();
        std::queue<std::shared_ptr<Node>> queue = std::queue<std::shared_ptr<Node>>();

        while (seen.size() < num_nodes && p_queue.size() > 0)
        {
            std::shared_ptr<Node> node = p_queue.top();
            this->_bfs.push_back(node);
            auto edge_it_begin = node->edges.begin();
            auto edge_it_end = node->edges.end();
            for (auto edge_it = edge_it_begin; edge_it != edge_it_end; ++edge_it)
            {
                std::shared_ptr<Node> child = *edge_it;
                if (seen.find(child->id) == seen.end())
                {
                    this->_bfs.push_back(child);
                    seen.insert(child->id);
                }
            }
            p_queue.pop();
        }
    }
}

LoraxAlgorithm::LoraxAlgorithm() : _tree() {}

LoraxAlgorithm::LoraxAlgorithm(unsigned int num_nodes) : _tree(num_nodes) {}

LoraxAlgorithm::~LoraxAlgorithm() {}

void LoraxAlgorithm::add_edge(unsigned int parent, unsigned int child)
{
    this->_tree.add_edge(parent, child);
}

void LoraxAlgorithm::update_node(unsigned int node_id, long sum)
{
    std::shared_ptr<Node> node = this->_tree.get(node_id);
    *(node->value) += sum;
}

long LoraxAlgorithm::search(unsigned int parent, unsigned int child)
{
    auto begin_it = this->_tree.begin();
    auto end_it = this->_tree.end();
    long sum = 0;
    for (auto it = begin_it; it != end_it; ++it)
    {
        std::shared_ptr<Node> node_ptr = *begin_it;
        sum += *(node_ptr->value);
        if (node_ptr->id == parent - 1 || node_ptr->id == child - 1)
        {
            break;
        }
    }
    return sum;
}

#ifndef _TESTS_H

int main(int argc, char *argv[])
{
    unsigned int num_tests;
    std::cin >> num_tests;
    for (unsigned int i = 0; i < num_tests; ++i)
    {
        unsigned int num_nodes, num_queries;
        std::cin >> num_nodes >> num_queries;
        LoraxAlgorithm lorax_alg(num_nodes);

        // -- Graph initialisation
        for (unsigned int j = 0; j < num_nodes - 1; ++j)
        {
            unsigned int parent, child;
            std::cin >> parent >> child;
            lorax_alg.add_edge(parent, child);
        }

        // -- Queries
        for (unsigned int j = 0; j < num_queries; ++j)
        {
            unsigned int parent, child;
            unsigned long query_value;
            std::cin >> parent >> child >> query_value;
            if (query_value == 0)
            {
                std::cout << "DEBUG: sort and find minimum flow between (" << parent << ", " << child << ")" << std::endl;
            }
            else
            {
                std::cout << "DEBUG: update value for the following nodes: (" << parent << ", " << child << ") :: to -> " << query_value << std::endl;
            }
        }
    }
    std::exit(EXIT_SUCCESS);
}

#else

int main(int argc, char *argv[])
{
    std::exit(EXIT_SUCCESS);
}

#endif