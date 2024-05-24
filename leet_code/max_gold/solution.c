#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Visited
{
    bool state[15][15]; // on the stack
} Visited;

Visited Visited_Create(int gridSize)
{
    Visited visited = {{{false}}};
    return visited;
}

bool Visited_IsSeen(Visited *visited, int r, int c)
{
    return visited->state[r][c];
}

void Visited_Set(Visited *visited, int r, int c)
{
    visited->state[r][c] = true;
}

void Visited_Clear(Visited *visited, int r, int c)
{
    visited->state[r][c] = false;
}

typedef struct Mine
{
    int **grid;
    int nRows;
    int *nCols;
} Mine;

int Mine_Get(Mine *mine, int r, int c)
{
    if (0 > r || 0 > c || r >= mine->nRows || c >= mine->nCols[r])
    {
        return -1;
    }
    return mine->grid[r][c];
}

int max(int a, int b)
{
    return a < b ? b : a;
}

int recursiveMaxGold(Mine *mine, Visited *visited, int r, int c)
{

    int gold = Mine_Get(mine, r, c);
    if (gold < 1)
    {
        return 0;
    }

    bool isSeen = Visited_IsSeen(visited, r, c);
    if (isSeen)
        return 0;

    Visited_Set(visited, r, c);

    int maxGold = 0;
    maxGold = max(recursiveMaxGold(mine, visited, r - 1, c), maxGold);
    maxGold = max(recursiveMaxGold(mine, visited, r + 1, c), maxGold);
    maxGold = max(recursiveMaxGold(mine, visited, r, c - 1), maxGold);
    maxGold = max(recursiveMaxGold(mine, visited, r, c + 1), maxGold);

    Visited_Clear(visited, r, c);
    return gold + maxGold;
}

/** Entrypoint */
int getMaximumGold(int **grid, int gridSize, int *gridColSize)
{
    // for every non-zero field, find max spanning tree and store the maximum size
    Mine mine = {
        grid,
        gridSize,
        gridColSize,
    };
    int maxGold = 0;
    Visited visited = Visited_Create(gridSize);
    for (int r = 0; r < gridSize; r++)
    {
        for (int c = 0; c < gridColSize[r]; c++)
        {
            maxGold = max(recursiveMaxGold(&mine, &visited, r, c), maxGold);
        }
    }
    return maxGold;
}

void Mine_Free(Mine *mine)
{
    for(int i = 0; i < mine->nRows; i++)
    {
        free(mine->grid[i]);
    }
    free(mine->nCols);
}

Mine Mine_CreateEmpty(int size)
{
    Mine mine = {
        (int **)calloc(size, sizeof(int *)),
        size,
        (int *)calloc(size, sizeof(int)),
    };
    for (int i = 0; i < size; i++)
    {
        mine.grid[i] = (int *)calloc(size, sizeof(int));
    }
    return mine;
}

int main(int argc, char **argv)
{
    Mine mine = Mine_CreateEmpty(3);
    mine.grid[0][1] = 6;
    mine.grid[1][0] = 5;
    mine.grid[1][1] = 8;
    mine.grid[1][2] = 7;
    mine.grid[2][1] = 9;
    int colSize[3] = {3, 3, 3};

    printf("Max Gold: %d\n", getMaximumGold(mine.grid, 3, &colSize[0]));

    Mine_Free(&mine);
}