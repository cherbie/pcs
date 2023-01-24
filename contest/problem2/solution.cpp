#include <bits/stdc++.h>

#define NROWS 5
#define NCOLS 5

void solve(int row, int col)
{
    int rowDiff = std::abs(row - 2);
    int colDiff = std::abs(col - 2);
    std::cout << rowDiff + colDiff << std::endl;
}

int main(int argc, char **argv)
{
    for (int i = 0; i < NROWS; i++)
        for (int j = 0; j < NCOLS; j++)
        {
            int v;
            std::cin >> v;
            if (v == 1)
            {
                solve(i, j);
                return 0;
            }
        }
    return -1;
}