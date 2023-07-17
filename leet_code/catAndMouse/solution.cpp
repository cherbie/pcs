#include <bits/stdc++.h>
#include <algorithm>

namespace
{
    const int UNDEFINED = -1, DRAW = 0, MOUSE_WIN = 1, CAT_WIN = 2,
              HOLE_IDX = 0, MOUSE_IDX = 1, CAT_IDX = 2;

    class Solution
    {
    private:
        std::map<std::tuple<int /*isMouseMove*/, int /*mouse*/, int /*cat*/>, int /*state*/> dp;

    public:
        int catMouseGame(const std::vector<std::vector<int>> &graph)
        {
            const int numNodes = graph.size();
            initGameState(numNodes);

            return dfsTraversal(graph, {0, MOUSE_IDX, CAT_IDX});
        }

    private:
        void initGameState(int numNodes)
        {
            // initialize dp
            for (auto i = 0; i < numNodes; i++)
            {
                for (auto j = 0; j < numNodes; j++)
                {
                    // undirected graph
                    dp.insert({{0, i, j}, UNDEFINED});
                    dp.insert({{1, i, j}, UNDEFINED});
                }
            }
        }

        int dfsTraversal(const std::vector<std::vector<int>> &graph, std::tuple<int, int, int> gameState)
        {
            const auto &[stepCount, mouseIdx, catIdx] = gameState;
            if (stepCount >= static_cast<int>(graph.size() * 2))
            {
                return DRAW;
            }

            const auto stateOutcome = dp.find({stepCount % 2, mouseIdx, catIdx});
            if (stateOutcome == dp.end())
            {
                perror("outcome not valid");
                exit(1);
            }
            else if (stateOutcome->second != UNDEFINED)
            {
                return stateOutcome->second;
            }

            if (mouseIdx == catIdx)
            {
                stateOutcome->second = CAT_WIN;
                return CAT_WIN;
            }
            else if (mouseIdx == HOLE_IDX)
            {
                stateOutcome->second = MOUSE_WIN;
                return MOUSE_WIN;
            }

            const auto isMouseMove = stepCount % 2 == 0;
            const int nextStep = stepCount + 1;
            int nextOutcome = CAT_WIN;
            for (const auto move : (isMouseMove ? graph[mouseIdx] : graph[catIdx]))
            {
                const int mouseMove = isMouseMove ? move : mouseIdx;
                const int catMove = isMouseMove ? catIdx : move;
                const int result = dfsTraversal(graph, {nextStep, mouseMove, catMove});
                if (result == MOUSE_WIN)
                {
                    stateOutcome->second = MOUSE_WIN;
                    return MOUSE_WIN;
                }
                else if (result == DRAW)
                {
                    stateOutcome->second = DRAW;
                    nextOutcome = DRAW;
                }
#ifdef DEBUG
                else if (result == UNDEFINED)
                {
                    perror("dfsTraversal resulted in undefined sub-game state result");
                    exit(1);
                }
#endif // #ifdef DEBUG
            }
            stateOutcome->second = nextOutcome;
            return nextOutcome;
        }
    };

    int readNumTestCases(void)
    {
        int numTestCases = 0;
        std::cin >> numTestCases;
        return numTestCases;
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
            if (std::isdigit(static_cast<char>(c)))
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
