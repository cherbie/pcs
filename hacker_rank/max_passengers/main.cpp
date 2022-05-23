#include <tuple>
#include <deque>
#include <bitset>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <map>

#define INT_MIN -100

namespace program
{
    std::vector<int> mat;
    int r = 0, c = 0;
    std::map<std::pair<int, std::pair<int, int>>, int> dp; // memoization

    bool isValid(int i, int j)
    {
        if (i < 0 || i >= r)
            return false;
        else if (j < 0 || j >= c)
            return false;
        else if (mat[i * r + j] < 0)
            return false;
        // else
        return true;
    }

    int solution(int i, int j, int x, int y)
    {
        if (!isValid(i, j))
            return INT_MIN;
        else if (!isValid(x, y))
            return INT_MIN;

        // recursion base condition
        if (i == r - 1 && x == r - 1 && j == c - 1 && y == c - 1)
        {
            if (mat[i * r + j] == 1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        if (dp.find({i, {j, x}}) != dp.end())
            return dp[{i, {j, x}}]; // get memoized value

        int sum = 0;
        if (i == x && j == y)
        {
            if (mat[i * r + j] == 1)
                sum = 1;
        }
        else
        {
            if (mat[i * r + j] == 1)
                sum++;
            if (mat[x * r + y] == 1)
                sum++;
        }

        // memoize possible down outcomes
        auto op1 = solution(i + 1, j, x + 1, y); // down
        auto op3 = solution(i + 1, j, x, y + 1); // out of sync

        // memoize possible right outcomess
        auto op2 = solution(i, j + 1, x, y + 1); // right
        auto op4 = solution(i, j + 1, x + 1, y); // out of sync
        int max = sum + std::max(op1, std::max(op2, std::max(op3, op4)));
        dp[{i, {j, x}}] = max;
        return max;
    }

    int program(int argc, char *argv[])
    {
        std::cin >> r >> c;

        // 1 0 0 0
        // -1 1 0 1
        // 0 1 0 -1
        // 1 -1 0 0
        //
        // 1000 0101
        //
        // O(m*n)
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                int t;
                std::cin >> t;
                mat.push_back(t);
            }
        }

        if (solution(0, 0, 0, 0) > 0)
            return solution(0, 0, 0, 0); // non-directed graph
        else
            return 0;
    }
}

int main(int argc, char *argv[])
{
    std::cout << program::program(argc, argv) << "\n";
    return 0;
}