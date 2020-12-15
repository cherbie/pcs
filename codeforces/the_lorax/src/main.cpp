#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <cstdlib>
#include <memory>
#include <iterator>
#include <set>
#include <algorithm>
#include <cmath>
#include <stdexcept>

class Tree
{
public:
    Tree();
    Tree(unsigned int num_nodes);
    ~Tree();

    friend class FibonacciTree;

    struct Node
    {
        unsigned int id;
        long value = 0;
        std::list<std::weak_ptr<Node>> edges; // adjacency list
        friend bool operator<(const Tree::Node &l, const Tree::Node &r)
        {
            return l.value < r.value; // keep the same order
        }
    };

    void add_edge(unsigned int parent, unsigned int child);
    std::shared_ptr<Tree::Node> get(unsigned int node_id) const;
    unsigned int size() const;

    static bool compare(std::shared_ptr<Tree::Node> largest, std::shared_ptr<Tree::Node> next)
    {
        return largest->value < next->value;
    }

private:
    std::vector<std::shared_ptr<Node>> _nodes;
};

class FibonacciTree
{
public:
    struct Node
    {
        unsigned int id;
        long value;
        std::priority_queue<std::shared_ptr<FibonacciTree::Node>, std::vector<std::shared_ptr<FibonacciTree::Node>>> edges;
        friend bool operator<(const FibonacciTree::Node &l, const FibonacciTree::Node &r)
        {
            return l.value < r.value;
        }
    };

public:
    FibonacciTree();
    FibonacciTree(Tree tree);
    ~FibonacciTree();

    std::shared_ptr<FibonacciTree::Node> get_head() const;
    static bool compare(std::shared_ptr<FibonacciTree::Node> largest, std::shared_ptr<FibonacciTree::Node> next)
    {
        return largest->value < next->value;
    };

private:
    std::shared_ptr<FibonacciTree::Node> _head;
    unsigned int _num_nodes;
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
    long search(unsigned int parent_id, unsigned int child_id) const;
    /** Update node value */
    void update_node(unsigned int node_id, long value);
    /** Add edge to graph */
    void add_edge(unsigned int parent_id, unsigned int child_id);
};

// >> FibonacciTree >>

FibonacciTree::FibonacciTree() : _head(nullptr), _num_nodes(0)
{
}

FibonacciTree::FibonacciTree(Tree tree) : _head(nullptr), _num_nodes(tree._nodes.size())
{
    auto max_node_p = std::max_element(tree._nodes.begin(), tree._nodes.end(), Tree::compare);

    if (max_node_p == tree._nodes.end())
        return;

    std::set<unsigned int> seen;
    std::queue<std::shared_ptr<FibonacciTree::Node>> bfs_queue;

    this->_head = std::make_shared<FibonacciTree::Node>();
    this->_head->id = (*max_node_p)->id;
    this->_head->value = (*max_node_p)->value;
    bfs_queue.push(this->_head);
    seen.insert(this->_head->id);

    while (seen.size() < this->_num_nodes && !bfs_queue.empty())
    {
        std::shared_ptr<FibonacciTree::Node> ft_node_p = bfs_queue.front();
        bfs_queue.pop();
        std::shared_ptr<Tree::Node> t_node_p = tree._nodes.at(ft_node_p->id - 1);

        auto begin_it = t_node_p->edges.begin();
        auto end_it = t_node_p->edges.end();
        for (auto edge_it = begin_it; edge_it != end_it; ++edge_it)
        {
            std::shared_ptr<Tree::Node> t_node_p_child = edge_it->lock();

            if (seen.find(t_node_p_child->id) != seen.end())
                continue;

            // create fibonacci tree child node
            std::shared_ptr<FibonacciTree::Node> ft_node_p_child = std::make_shared<FibonacciTree::Node>();
            ft_node_p_child->id = t_node_p_child->id;
            ft_node_p_child->value = t_node_p_child->value;
            ft_node_p->edges.push(ft_node_p_child); // push onto priority queue of edges
            bfs_queue.push(ft_node_p_child);
            seen.insert(ft_node_p_child->id);
        }
    }
}

FibonacciTree::~FibonacciTree() {}

std::shared_ptr<FibonacciTree::Node> FibonacciTree::get_head() const
{
    return this->_head;
}

// << FibonacciTree <<

// >> Tree >>

Tree::Tree() : _nodes() {}

Tree::Tree(unsigned int num_nodes) : _nodes(num_nodes)
{
    for (unsigned int index = 1; index <= num_nodes; ++index)
    {
        std::shared_ptr<Tree::Node> node = std::make_shared<Tree::Node>();
        node->id = index;
        this->_nodes.at(index - 1) = node;
    }
}

Tree::~Tree() {}

// Add edge to node graph
void Tree::add_edge(unsigned int parent_id, unsigned int child_id)
{
    std::shared_ptr<Tree::Node> parent_p = this->_nodes.at(parent_id - 1);
    std::shared_ptr<Tree::Node> child_p = this->_nodes.at(child_id - 1);
    std::weak_ptr<Tree::Node> parent_wp = parent_p;
    std::weak_ptr<Tree::Node> child_wp = child_p;
    parent_p->edges.push_back(child_wp); // could be a problem here ... circular deconstruction
    child_p->edges.push_back(parent_wp);
}

// Get the value / weight of a particular node
std::shared_ptr<Tree::Node> Tree::get(unsigned int node_id) const
{
    return this->_nodes.at(node_id - 1);
}

unsigned int Tree::size() const
{
    return this->_nodes.size();
}

// << Tree <<

// >> LoraxAlgorithm >>

LoraxAlgorithm::LoraxAlgorithm() : _tree() {}

LoraxAlgorithm::LoraxAlgorithm(unsigned int num_nodes) : _tree(num_nodes) {}

LoraxAlgorithm::~LoraxAlgorithm() {}

void LoraxAlgorithm::add_edge(unsigned int parent, unsigned int child)
{
    this->_tree.add_edge(parent, child);
}

void LoraxAlgorithm::update_node(unsigned int node_id, long sum)
{
    std::shared_ptr<Tree::Node> node = this->_tree.get(node_id);
    node->value += sum;
}

long LoraxAlgorithm::search(unsigned int parent_id, unsigned int child_id) const
{
    FibonacciTree fib_tree = FibonacciTree(this->_tree);
    std::shared_ptr<FibonacciTree::Node> head_p = fib_tree.get_head();

    std::queue<std::shared_ptr<FibonacciTree::Node>> bfs_queue;
    bfs_queue.push(head_p);

    long sum = 0;
    bool seen_parent = false; // sum once the first child or parent node is reached;

    while (!bfs_queue.empty())
    {
        std::shared_ptr<FibonacciTree::Node> node_p = bfs_queue.front();
        bfs_queue.pop();
        std::cout << node_p->id << " {" << node_p->value << "} | ";
        if (!seen_parent && (node_p->id == parent_id || node_p->id == child_id))
        {
            seen_parent = true;
        }
        else if (node_p->id == parent_id || node_p->id == child_id)
        {
            std::cout << std::endl;
            if (node_p->edges.empty())
                return std::abs(node_p->value);
            else
                return std::abs(sum);
        }
        sum += node_p->value;

        while (!node_p->edges.empty())
        {
            std::shared_ptr<FibonacciTree::Node> child_p = node_p->edges.top();
            node_p->edges.pop();
            bfs_queue.push(child_p);
        }
    }

    throw std::logic_error("edge between nodes does not exist");
}

// << LoraxAlgorithm <<

#ifndef _TESTS_H

int main(int argc, char *argv[])
{
    unsigned int num_tests;
    std::cin >> num_tests;
    for (unsigned int i = 0; i < num_tests; ++i)
    {
        unsigned int num_nodes, num_queries;
        std::cin >> num_nodes >> num_queries;
        LoraxAlgorithm lorax_alg = LoraxAlgorithm(num_nodes);

        // -- Graph initialisation
        for (unsigned int j = 0; j < num_nodes - 1; ++j)
        {
            unsigned int parent, child;
            std::cin >> parent >> child;
            lorax_alg.add_edge((unsigned int)parent, (unsigned int)child);
        }

        // -- Queries
        for (unsigned int j = 0; j < num_queries; ++j)
        {
            unsigned int parent, child;
            long query_value;
            std::cin >> parent >> child >> query_value;
            if (query_value == 0)
            {
                std::cout << lorax_alg.search(parent, child) << std::endl;
            }
            else
            {
                lorax_alg.update_node(parent, -query_value);
                lorax_alg.update_node(child, query_value);
            }
        }
    }
    std::exit(EXIT_SUCCESS);
}

#endif
