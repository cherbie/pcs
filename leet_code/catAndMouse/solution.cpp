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
            int lastResult = 0;
            for (int lastRound = 0; lastRound < numNodes; lastRound++)
            {
                lastResult = dfsTraversal(graph, {0, MOUSE_IDX, CAT_IDX});
                if (lastResult != 0)
                {
                    return lastResult;
                }
                revisitCatAndMouse(numNodes);
            }
            return lastResult;
        }

    private:
        void revisitCatAndMouse(int numNodes)
        {
            for (int i = 0; i < numNodes; i++)
            {
                for (int j = 0; j < numNodes; j++)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        const auto outcome = dp.find({k, i, j});
#ifdef DEBUG
                        if (outcome == dp.end())
                        {
                            perror("could not find expected game state");
                            exit(1);
                        }
#endif // #ifdef DEBUG
                        if (outcome->second == 0)
                        {
                            outcome->second = UNDEFINED;
                        }
                    }
                }
            }
        }

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

            const auto stateOutcome = dp.find({stepCount % 2, mouseIdx, catIdx});
#ifdef DEBUG
            if (stateOutcome == dp.end())
            {
                perror("outcome not valid");
                exit(1);
            }
#endif // #ifdef DEBUG
            if (stateOutcome->second != UNDEFINED)
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
            else
            {
                stateOutcome->second = DRAW;
            }

            const auto isMouseMove = stepCount % 2 == 0;
            int drawCount = 0;
            for (auto const &move : (isMouseMove ? graph[mouseIdx] : graph[catIdx]))
            {
                const int mouseMove = isMouseMove ? move : mouseIdx;
                const int catMove = isMouseMove ? catIdx : move;
                if (catMove == HOLE_IDX)
                {
                    continue;
                }
                const int result = dfsTraversal(graph, {stepCount + 1, mouseMove, catMove});
#ifdef DEBUG
                if (result == UNDEFINED)
                {
                    perror("dfsTraversal resulted in undefined sub-game state result");
                    exit(1);
                }
#endif // #ifdef DEBUG
                if (isMouseMove && result == MOUSE_WIN)
                {
                    stateOutcome->second = MOUSE_WIN;
                    return MOUSE_WIN;
                }
                else if (!isMouseMove && result == CAT_WIN)
                {
                    stateOutcome->second = CAT_WIN;
                    return CAT_WIN;
                }
                else if (result == DRAW)
                {
                    drawCount++;
                }
            }
            if (drawCount > 0)
            {
                stateOutcome->second = DRAW;
                return DRAW;
            }
            else
            {
                const int outcome = isMouseMove ? CAT_WIN : MOUSE_WIN;
                stateOutcome->second = outcome;
                return outcome;
            }
        }
    };

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
