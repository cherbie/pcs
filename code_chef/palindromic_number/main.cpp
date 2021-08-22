#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <memory>
#include <sstream>
#include <limits>
#include <algorithm>

using PalindromicNumber = std::tuple<std::string, int>;

bool is_palindrome(const std::string &seq)
{
    auto rit = seq.rbegin();
    for (auto c : seq)
    {
        if (*rit != c)
            return false;
        rit++;
    }
    return true;
}

class Tie
{
public:
    struct Node
    {
        int value;
        unsigned int tier;
        int weight;
        std::shared_ptr<Node> parent;
        std::vector<std::shared_ptr<Node>> children;
    };
    using NodeSPtr = std::shared_ptr<Node>;
    using NodeWPtr = std::weak_ptr<Node>;

private:
    NodeSPtr m_root;
    /** Lookup to nodes based on values **/
    std::array<std::vector<NodeWPtr>, 10> m_lookup;
    unsigned int m_maxWeight;

public:
    Tie() = default;
    Tie(const std::string &s, unsigned int maxWeight)
    {
        m_maxWeight = maxWeight;
        m_root = std::make_shared<Node>(Node{
            -1,      // value
            0,       // tier
            0,       // weight
            nullptr, // parent
            std::vector<NodeSPtr>{} /** children */});
        m_lookup = std::array<std::vector<NodeWPtr>, 10>{
            std::vector<NodeWPtr>(),
            std::vector<NodeWPtr>(),
            std::vector<NodeWPtr>(),
            std::vector<NodeWPtr>(),
            std::vector<NodeWPtr>(),
            std::vector<NodeWPtr>(),
            std::vector<NodeWPtr>(),
            std::vector<NodeWPtr>(),
            std::vector<NodeWPtr>(),
            std::vector<NodeWPtr>()};
        NodeWPtr parent_wp = std::weak_ptr(m_root);
        auto temp_char = std::array<char, 2>{'\n', '\n'};
        unsigned int tier = 1;
        for (const char &c : s)
        {
            NodeSPtr parent = parent_wp.lock();
            temp_char[0] = c;
            int value = atoi(temp_char.cbegin());
            if (value < 0)
                exit(EXIT_FAILURE);
            Node node = Node{
                value,  /** value */
                tier++, /** tier */
                0,      /** weight */
                parent, /** parent */
                std::vector<NodeSPtr>{} /** children */};
            NodeSPtr node_sp = std::make_shared<Node>(node);
            parent->children.push_back(node_sp);
            parent_wp = std::weak_ptr(node_sp);
            m_lookup[value].push_back(parent_wp);
        }
    }
    ~Tie() {}

    /**
     * Insert a node replacing into the tie graph formed
     * @param x - character id to replace
     * @param y - character to replace the id with
     * @param w - cost of operation
     */
    void insert(int x, int y, int w)
    {
        std::vector<NodeWPtr> nodes = m_lookup.at(x);
        for (const auto &node_wp : nodes)
        {
            NodeSPtr node_sp = node_wp.lock();
            std::vector<NodeSPtr> parents = node_sp->parent->parent != nullptr ? node_sp->parent->parent->children
                                                                               : std::vector<NodeSPtr>{node_sp->parent};
            for (const NodeSPtr &parent : parents)
            {
                NodeSPtr nnode_sp = std::make_shared<Node>(Node{
                    y,                   /** value */
                    node_sp->tier,       /** tier */
                    node_sp->weight + w, /** weight */
                    parent,              /** parent */
                    std::vector<NodeSPtr>(node_sp->children) /** children */});
                parent->children.push_back(nnode_sp);
                m_lookup[y].push_back(std::weak_ptr<Node>(nnode_sp));
            }
        }
    }

    class PalindromicIterator
    {
    private:
        using WeightedNode = std::pair<unsigned int /** accumulated weight */, Tie::Node /** window */>;
        std::vector<PalindromicNumber> m_values;
        unsigned int m_maxWeight;

        /**
         * Recursive depth-first traversal of graph
         */
        void dfs(const WeightedNode &&window, std::stringstream &stream)
        {
            if (window.second.children.empty())
            {
                std::string seq = stream.str();
                if (!is_palindrome(seq) || window.first > m_maxWeight)
                {
                    return;
                }
                m_values.push_back(std::make_tuple(seq, window.first));
            }
            else
            {
                for (const auto &child : window.second.children)
                {
                    stream.seekp(child->tier - 1, std::stringstream::beg); // input stream
                    stream << child->value;
                    dfs(WeightedNode{window.first + window.second.weight, *child}, stream);
                }
            }
        }

    public:
        PalindromicIterator() = default;
        PalindromicIterator(const Tie &graph)
        {
            auto ss = std::stringstream();
            m_maxWeight = graph.m_maxWeight;
            dfs(WeightedNode{graph.m_root->weight, *graph.m_root}, ss);
        }
        ~PalindromicIterator()
        {
        }

        std::vector<PalindromicNumber>::const_iterator cbegin() const noexcept
        {
            return m_values.cbegin();
        }

        std::vector<PalindromicNumber>::const_iterator cend() const noexcept
        {
            return m_values.cend();
        }

        std::size_t size() const noexcept
        {
            return m_values.size();
        }
    }; // class PalindromicIterator
};     // class Tie

int main(int argc, char *argv[])
{
    int t; // test cases
    std::cin >> t;
    while (t > 0)
    {
        int n; // number of characters in string
        int m; // number of "operations" to follow
        int k; // maximum number of "coins" to spend
        std::cin >> n >> m >> k;
        std::string s; // starting string
        std::cin >> s;
        Tie graph = Tie(s, k);
        for (int i = 0; i < m; i++)
        {
            // operations to perform
            int x; // character to replace
            int y; // character to replace with
            int w; // "coint" cost of operation
            std::cin >> x >> y >> w;
            graph.insert(x, y, w);
        }
        auto palindromic_it = Tie::PalindromicIterator(graph);
        // lexigraphically largest element
        auto max_element = std::max_element(palindromic_it.cbegin(),
                                            palindromic_it.cend(),
                                            [](const PalindromicNumber &l, const PalindromicNumber &r) -> bool
                                            { return std::get<0>(l) < std::get<0>(r); });
        if (max_element != palindromic_it.cend())
            std::cout << std::get<0>(*max_element) << '\n';
        else
            std::cout << -1 << '\n';
        t--;
    }
}