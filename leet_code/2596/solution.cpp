#include <bits/stdc++.h>

#define DEBUG

#define MAX_ROW_SIZE 7
#define MAX_COL_SIZE 7

using Grid = std::vector<std::vector<int>>;
using Coordinates = std::array<int, 2>;

/// entrypoint
bool checkValidGrid(Grid &grid)
{
    if (grid[0][0] != 0)
        return false;

    // collect coordinates
    std::array<Coordinates, MAX_ROW_SIZE * MAX_COL_SIZE> coordinates;
    int ridx = 0, cidx = 0;
    for (auto row : grid)
    {
        cidx = 0;
        for (auto position : row)
        {
            coordinates[position] = {ridx, cidx++};
        }
        ridx++;
    }

    // check move validity
    for (std::size_t i = 1; i < (std::size_t)(grid.size() * grid.size()); i++)
    {
        const auto row_diff = std::abs(coordinates[i][0] - coordinates[i - 1][0]) + 1;
        const auto col_diff = std::abs(coordinates[i][1] - coordinates[i - 1][1]) + 1;
        if (std::abs(row_diff - col_diff) != 1 || (row_diff + col_diff) != 5)
            return false;
    }
    return true;
}

#ifdef DEBUG
Grid parseGrid(std::istream &file)
{
    if (!file.good())
        throw std::exception();

    Grid grid;
    std::string str;
    int row = -1;

    while (std::getline(file, str))
    {
        std::stringstream ss(str);
        grid.push_back(std::vector<int>{});
        row++;
        while (ss.good())
        {
            int temp;
            ss >> temp;
            grid[row].push_back(temp);
        }
    }

    return grid;
}

void printGrid(Grid &grid)
{
    for (auto row : grid)
    {
        for (auto element : row)
        {
            std::cerr << element << " ";
        }
        std::cerr << std::endl;
    }
}
#endif // ifdef DEBUG

int main(int argc, char **argv)
{
#ifdef DEBUG
    // case 1 - pass
    std::stringstream input1("0 11 16 5 20\n17 4 19 10 15\n12 1 8 21 6\n3 18 23 14 9\n24 13 2 7 22");
    Grid grid1 = parseGrid(input1);
    std::cout << (checkValidGrid(grid1) ? "true" : "false") << std::endl;

    // case 2 - fail
    std::stringstream input2("0 3 6\n5 8 1\n2 7 4");
    Grid grid2 = parseGrid(input2);
    std::cout << (checkValidGrid(grid2) ? "true" : "false") << std::endl;
#endif // ifdef DEBUG
}