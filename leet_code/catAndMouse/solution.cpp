#include <bits/stdc++.h>
#include <algorithm>

namespace
{
    using GameState = std::tuple<int /*mouseMove*/, int /*mouse idx*/, int /*cat idx*/>;
    using GameResult = std::pair<GameState, int /*outcome*/>;

    const int UNDEFINED = -1, DRAW = 0, MOUSE_WIN = 1, CAT_WIN = 2,
              HOLE_IDX = 0, MOUSE_IDX = 1, CAT_IDX = 2;

    class Solution
    {
    public:
        int catMouseGame(const std::vector<std::vector<int>> &graph)
        {
            int n = graph.size();

            // directed graph to perform topological traversal
            int graphDegrees[50][50][2];
            std::map<GameState, int /*outcome*/> dp;
            std::deque<GameResult> gameStates;
            for (int i = 0; i < n; i++)
            {
                for (int j = 1; j < n; j++)
                {

                    graphDegrees[i][j][0] = graph[i].size();
                    graphDegrees[i][j][1] = graph[j].size();
                    for (int k : graph[j])
                    {
                        if (k == HOLE_IDX)
                        {
                            graphDegrees[i][j][1]--;
                            break;
                        }
                    }

                    for (int k = 0; k < 2; k++)
                    {
                        if (i == HOLE_IDX)
                        {
                            dp.insert({{k, i, j}, MOUSE_WIN});
                            gameStates.push_back({{k, i, j}, MOUSE_WIN});
                        }
                        else if (i == j)
                        {
                            dp.insert({{k, i, j}, CAT_WIN});
                            gameStates.push_back({{k, i, j}, CAT_WIN});
                        }
                        else
                        {
                            dp.insert({{k, i, j}, DRAW});
                        }
                    }
                }
            }

            for (; !gameStates.empty(); gameStates.pop_front())
            {
                const auto &[gameState, outcome] = gameStates.front();
                const auto &[turn, mouseIdx, catIdx] = gameState;
                if (catIdx == CAT_IDX && mouseIdx == MOUSE_IDX && turn == 0)
                {
                    // at the start point
                    return outcome;
                }
                int prevTurn = 1 - turn; // turn % 2
                for (int prevMove : graph[prevTurn == 1 ? catIdx : mouseIdx])
                {
                    int prevCatIdx = prevTurn == 1 ? prevMove : catIdx;
                    int prevMouseIdx = prevTurn == 1 ? mouseIdx : prevMove;
                    if (prevCatIdx == HOLE_IDX)
                    {
                        continue;
                    }
                    const auto prevOutcome = dp.find({prevTurn, prevMouseIdx, prevCatIdx});
#ifdef DEBUG
                    if (prevOutcome == dp.end())
                    {
                        std::cerr << "something went wrong" << std::endl;
                        exit(1);
                    }
#endif // #ifdef DEBUG
                    if (prevOutcome->second == MOUSE_WIN || prevOutcome->second == CAT_WIN)
                    {
                        continue;
                    }
                    if ((prevTurn == 1 && outcome == CAT_WIN) ||
                        (prevTurn == 0 && outcome == MOUSE_WIN) ||
                        --graphDegrees[prevMouseIdx][prevCatIdx][prevTurn] == 0)
                    {
                        dp.insert({{prevTurn, prevMouseIdx, prevCatIdx}, outcome});
                        gameStates.push_back({{prevTurn, prevMouseIdx, prevCatIdx}, outcome});
                    }
                }
            }

            const auto initialOutcome = dp.find({0, MOUSE_IDX, CAT_IDX});
#ifdef DEBUG
            if (initialOutcome == dp.end())
            {
                std::cerr << "initial outcome not defined" << std::endl;
                exit(1);
            }
#endif // ifdef DEBUG
            return initialOutcome->second;
        }
    }; // class Solution

    int readNumTestCases(void)
    {
        int numTestCases = 0;
        std::cin >> numTestCases;
        return numTestCases;
    }

    void consumeUntilDigit(void)
    {
        char c = '\0';
        while ((c = std::cin.peek()) != EOF && !std::isdigit(static_cast<unsigned char>(c)))
        {
            std::cin.get();
        }
    }

    std::vector<int> readline(void)
    {
        while (std::cin.peek() != EOF && std::isspace(std::cin.peek()))
        {
            std::cin.get();
        }
        std::vector<int> terms;
        std::stack<int> digits;
        while (std::cin.peek() != EOF)
        {
            const char c = std::cin.get();
            if (std::isdigit(static_cast<unsigned char>(c)))
            {
                int digit = std::atoi(&c);
                digits.push(digit);
            }
            else
            {
                if (!digits.empty())
                {
                    int term = 0;
                    for (int magnitude = 0; !digits.empty(); digits.pop(), magnitude++)
                    {
                        int digit = digits.top();
                        term += magnitude == 0 ? digit : digit * magnitude * 10;
                    }
                    terms.push_back(term);
                }

                if (c == '\n')
                {
                    break;
                }
            }
        }
        return terms;
    }

    std::vector<std::vector<int>> readGraph(void)
    {
        consumeUntilDigit();
        int numNodes = 0;
        std::cin >> numNodes;

        std::vector<std::vector<int>> graph;
        for (int idx = 0; idx < numNodes; idx++)
        {
            graph.push_back(readline());
        }
        return graph;
    }

    void printGraph(const std::vector<std::vector<int>> &graph)
    {
        std::cout << " --- " << std::endl;
        for (const auto &row : graph)
        {
            for (const auto &n : row)
            {
                std::cout << n << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << " --- " << std::endl;
    }
} // end namespace

int main(int argc, char **argv)
{
#ifdef DEBUG
    const int numTestCases = ::readNumTestCases();
    for (auto i = 0; i < numTestCases; i++)
    {
        auto s = ::Solution();
        const std::vector<std::vector<int>> graph = ::readGraph();
        ::printGraph(graph);
        std::cout << "Result: " << s.catMouseGame(graph) << std::endl;
    }
#endif // ifdef DEBUG

    return 0;
}
