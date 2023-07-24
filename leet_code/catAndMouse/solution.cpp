#include <bits/stdc++.h>
#include <algorithm>

#define MAX_GRAPH_SIZE 50

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
            int graphDegrees[MAX_GRAPH_SIZE/*mouse*/][MAX_GRAPH_SIZE/*cat*/][2/*move*/] = {0};
            int colours[MAX_GRAPH_SIZE/*mouse*/][MAX_GRAPH_SIZE/*cat*/][2/*move*/] = {0};

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
                            colours[i][j][k] = MOUSE_WIN;
                            gameStates.push_back({{k, i, j}, MOUSE_WIN});
                        }
                        else if (i == j)
                        {
                            colours[i][j][k] = CAT_WIN;
                            gameStates.push_back({{k, i, j}, CAT_WIN});
                        }
                    }
                }
            }

            for (; !gameStates.empty(); gameStates.pop_front())
            {
                const auto &[gameState, outcome] = gameStates.front();
                const auto &[turn, mouseIdx, catIdx] = gameState;

                int prevTurn = 1 - turn; // turn % 2
                for (int prevMove : graph[prevTurn == 1 ? catIdx : mouseIdx])
                {
                    int prevCatIdx = prevTurn == 1 ? prevMove : catIdx;
                    int prevMouseIdx = prevTurn == 1 ? mouseIdx : prevMove;
                    if (prevCatIdx == HOLE_IDX)
                    {
                        continue;
                    }

                    const int prevOutcome = colours[prevMouseIdx][prevCatIdx][prevTurn];
                    if (prevOutcome == DRAW)
                    {
                        if ((prevTurn == 1 && outcome == CAT_WIN) ||
                            (prevTurn == 0 && outcome == MOUSE_WIN))
                        {
                            colours[prevMouseIdx][prevCatIdx][prevTurn] = outcome;
                            gameStates.push_back({{prevTurn, prevMouseIdx, prevCatIdx}, outcome});
                        }
                        else if ((--graphDegrees[prevMouseIdx][prevCatIdx][prevTurn]) == 0)
                        {
                            const int lossOutcome = 2 - prevTurn;
                            colours[prevMouseIdx][prevCatIdx][prevTurn] = lossOutcome;
                            gameStates.push_back({{prevTurn, prevMouseIdx, prevCatIdx}, lossOutcome});
                        }
                    }
                }
            }

            return colours[MOUSE_IDX][CAT_IDX][0];
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
