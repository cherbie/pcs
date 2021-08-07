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

public:
    Tie() = default;
    Tie(const std::string &s)
    {
        m_root = std::make_shared<Node>(Node{
            -1,
            0, // tier of 0
            0,
            nullptr,
            std::vector<NodeSPtr>{}});
        std::cerr << "Debugging" << std::endl;
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
        for (const char &c : s)
        {
            NodeSPtr parent = parent_wp.lock();
            temp_char[0] = c;
            int value = atoi(temp_char.cbegin());
            if (value < 0)
                std::cerr << "Incorrect value read: " << value;
            Node node = Node{
                value,
                1,
                0,
                parent,
                std::vector<NodeSPtr>{}};
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
            std::cerr << x << "|" << y << "|";
            NodeSPtr node_sp = node_wp.lock();
            std::cerr << "now|" << node_sp->value << "|";
            std::vector<NodeSPtr> parents = node_sp->parent->parent != nullptr ? node_sp->parent->parent->children
                                                                               : std::vector<NodeSPtr>{node_sp->parent};
            for (const NodeSPtr &parent : parents)
            {
                NodeSPtr nnode_sp = std::make_shared<Node>(Node{
                    y,
                    node_sp->tier,
                    parent->weight + w,
                    parent,
                    std::vector<NodeSPtr>(node_sp->children)});
                parent->children.push_back(nnode_sp);
                std::cerr << "parent|" << parent->value << "|";
                m_lookup[y].push_back(std::weak_ptr<Node>(nnode_sp));
            }
            std::cerr << std::endl;
        }
    }

    class PalindromicIterator
    {
    private:
        std::vector<PalindromicNumber> m_values;

        /**
         * Recursive depth-first traversal of graph
         */
        void dfs(const Node &window, std::stringstream &stream)
        {
            if (window.children.empty())
            {
                std::string seq = stream.str();
                if (!is_palindrome(seq))
                    return;
                m_values.push_back(std::make_tuple(seq, window.weight));
            }
            else
            {
                for (const auto &child : window.children)
                {
                    stream.seekg(window.tier, std::stringstream::beg); // input stream
                    stream.ignore(std::numeric_limits<std::streamsize>::max());
                    stream.seekp(window.tier); // output stream
                    stream.clear();
                    stream << child->value;
                    dfs(*child, stream);
                }
            }
        }

    public:
        PalindromicIterator() = default;
        PalindromicIterator(const Tie &graph)
        {
            auto ss = std::stringstream();
            dfs(*graph.m_root, ss);
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
        Tie graph = Tie(s);
        for (int i = 0; i < m; i++)
        {
            // operations to perform
            int x; // character to replace
            int y; // character to replace with
            int w; // "coint" cost of operation
            std::cin >> x >> y >> w;

            std::cerr << "Insert: " << x << std::endl;
            graph.insert(x, y, w);
        }
        auto palindromic_it = Tie::PalindromicIterator(graph);
        auto min_element = std::min_element(palindromic_it.cbegin(),
                                            palindromic_it.cend(),
                                            [](const PalindromicNumber &l, const PalindromicNumber &r) -> bool
                                            { return std::get<1>(l) < std::get<1>(r); });
        if (min_element != palindromic_it.cend())
            std::cout << std::get<0>(*min_element);
        else
            std::cout << -1;
        std::cout << "\n";
        t--;
    }
}