#include <tuple>
#include <deque>
#include <bitset>
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace program
{
    using bitset = std::bitset<1000000>;
    using mst_path = std::tuple<bitset, std::size_t, std::size_t>;

    namespace
    {
        static bool cmp_mst_path(mst_path l, mst_path r)
        {
            return (std::get<2>(l) >= std::get<2>(r));
        }
    }

    int program(int argc, char *argv[])
    {
        long n, m; // sizes not specified (generous assumption made)
        std::cin >> n >> m;
        long num_el = n * m;
        bitset graph;
        bitset people;
        // 1 0 0 0
        // -1 1 0 1
        // 0 1 0 -1
        // 1 -1 0 0
        //
        // 1000 0101
        //
        // O(m*n)
        for (long i = 0; i < n; i++)
        {
            for (long j = 0; j < m; j++)
            {
                int t; // type
                std::cin >> t;
                std::size_t index = i * n + j;
                std::cerr << t << " | " << index << " | " << graph.size() << "\n";
                if (t >= 0)
                {
                    if (t == 1)
                    {
                        people.set(index);
                    }
                    graph.set(index);
                }
            }
        }

        // find paths to (n-1, n-1)
        std::size_t current_idx = 0;
        std::deque<mst_path> q = std::deque<mst_path>();
        {
            bitset comp_map;
            unsigned int count = 0;
            comp_map.set(current_idx);
            if (people.test(0))
            {
                count = 1;
            }
            q.push_back(std::make_tuple(comp_map, current_idx, count));
        }
        std::size_t operations = 0;
        for (int i = 0; i < m + n; i++)
        {
            if (q.empty())
                return 0; // no MST
            // else
            mst_path path_tuple = q.front();
            q.pop_front();
            const auto current_idx = std::get<1>(path_tuple);
            auto path = std::get<0>(path_tuple);

            // right
            std::size_t right_idx = current_idx + 1;
            if (right_idx < num_el && graph.test(right_idx))
            {
                auto count = std::get<2>(path_tuple);
                if (people.test(right_idx))
                {
                    count++;
                }
                path.set(right_idx);
                q.push_back(std::make_tuple(path, right_idx, count));
            }

            // down
            std::size_t down_idx = current_idx + m;
            if (down_idx < num_el && graph.test(down_idx))
            {
                auto count = std::get<2>(path_tuple);
                if (people.test(down_idx))
                {
                    count++;
                }
                path.set(down_idx);
                q.push_back(std::make_tuple(path, down_idx, count));
            }
        }
        if (q.empty())
            return 0; // no MST
        // else
        auto it = std::max_element(q.cbegin(), q.cend(), cmp_mst_path);
        if (it == q.end())
        {
            throw std::invalid_argument("error"); // error
        }

        // else
        auto max_path = std::get<0>(*it);
        auto eliminated = bitset(people & max_path); // remove people seen
        people &= ~eliminated;
        q.clear();
        q.push_back(*it);

        // -- AND BACK --
        for (int i = 0; i < m + n; i++)
        {
            if (q.empty())
                return 0; // no MST
            // else
            mst_path path_tuple = q.front();
            q.pop_front();
            const auto current_idx = std::get<1>(path_tuple);
            auto path = std::get<0>(path_tuple);

            // left
            std::size_t left_idx = current_idx - 1;
            if (left_idx >= 0 && graph.test(left_idx))
            {
                auto count = std::get<2>(path_tuple);
                if (people.test(left_idx))
                {
                    count++;
                }
                path.set(left_idx);
                q.push_back(std::make_tuple(path, left_idx, count));
            }

            // up
            std::size_t up_idx = current_idx - m;
            if (up_idx >= 0 && graph.test(up_idx))
            {
                auto count = std::get<2>(path_tuple);
                if (people.test(up_idx))
                {
                    count++;
                }
                path.set(up_idx);
                q.push_back(std::make_tuple(path, up_idx, count));
            }
        }

        if (q.empty())
            throw std::invalid_argument("error"); // error
        // else
        it = std::max_element(q.cbegin(), q.cend(), cmp_mst_path);
        if (it == q.end())
        {
            throw std::invalid_argument("error");
        }
        return std::get<2>(*it);
    }
}

int main(int argc, char *argv[])
{
    std::cout << program::program(argc, argv) << "\n";
    return 0;
}