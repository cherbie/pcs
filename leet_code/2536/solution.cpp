#include <bits/stdc++.h>

/// leetcode runtime trick
static auto _ = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

using matrix_t = std::vector<std::vector<int>>;
using query_t = std::vector<int>;

void printMatrix(matrix_t mat);

inline matrix_t makeUnitMatrix(int n)
{
    matrix_t mat;
    mat.assign(n, std::vector<int>(n));
    return mat;
}

inline matrix_t makeUnitQueryMatrix(int n, const query_t &query)
{
    auto qMat = makeUnitMatrix(n);

    const int r1 = query[0];
    const int c1 = query[1];
    const int r2 = query[2];
    const int c2 = query[3];

    for (int r = r1; r <= r2; r++)
        for (int c = c1; c <= c2; c++)
        {
            std::cout << r << " | " << c << std::endl;
            qMat[r][c] += 1;
        }
    return qMat;
}

inline matrix_t sumMatrices(const matrix_t &a, const matrix_t &b)
{
    matrix_t mat = a;
    for (int r = 0; r < (int)a.size(); r++)
        for (int c = 0; c < (int)a[0].size(); c++)
            mat[r][c] += b[r][c];
    return mat;
}

matrix_t addQuery(int n, const matrix_t &querySum, const query_t &query)
{
    matrix_t unitQueryMatrix = makeUnitQueryMatrix(n, query);
    printMatrix(unitQueryMatrix);
    return sumMatrices(querySum, unitQueryMatrix);
}

matrix_t rangeAddQueries(int n, const std::vector<query_t> &queries)
{
    matrix_t querySumMat = makeUnitMatrix(n);
    for (query_t query : queries)
    {
        querySumMat = addQuery(n, querySumMat, query);
    }
    return querySumMat;
}

void printMatrix(matrix_t mat)
{
    for (int r = 0; r < (int)mat.size(); r++)
    {
        for (int c = 0; c < (int)mat[0].size(); c++)
            std::cout << mat[r][c] << ", ";
        std::cout << std::endl;
    }
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    matrix_t queries = {{1, 1, 2, 2}};
    printMatrix(rangeAddQueries(3, queries));
#endif // #ifdef DEBUG
}