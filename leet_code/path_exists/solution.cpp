#include <bits/stdc++.h>

bool validPath(int n, std::vector<std::vector<int>> &edges, int source, int destination)
{
    std::set<int> seen = {source};
    std::queue<int> bfs = std::queue<int>({source});

    while (!bfs.empty())
    {
        auto current = bfs.front();
        bfs.pop();
        if (current == destination)
            return true;
        // else
        for (auto i = 0; i < n; i++)
        {
            if (edges[current][i])
                continue; // no edge
            else if (seen.find(i) != seen.end())
                continue; // already seen
            // else
            bfs.push(i);
            seen.insert(i);
        }
    }
    return false;
}

/// -- input --
/// 3
/// 0 1
/// 1 2
/// 2 0
/// 0
/// 2
/// -- output --
/// (true|false)
int main(int argc, char **argv)
{

    int n, source, destination;
    std::cin >> n;
    std::vector<std::vector<int>> edges;
    for (int i = 0; i < n; i++)
    {
        edges.push_back(std::vector<int>(n));
    }

    for (int i = 0; i < n; i++)
    {
        int from, to;
        std::cin >> from >> to;
        edges[from][to] = 1;
        edges[to][from] = 1;
    }

    std::cin >> source >> destination;
    std::cout << (validPath(n, edges, source, destination) ? "true" : "false") << std::endl;
}