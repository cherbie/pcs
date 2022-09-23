#include "bits/stdc++.h"

int solve(std::vector<int> &arr, int size)
{
    int moves = 0;
    for (int i = 0; i < size - 1; i++) 
    {
        int diff = arr[i] - arr[i+1];
        if (diff <= 0)
            continue;
        moves += diff;
    }
    return moves;
}

int main(int argc, char **argv)
{
    int n = 0;
    std::cin >> n;
    std::vector<int> arr;
    for (int i = 0; i < n; i++) {
        int v;
        std::cin >> v;
        arr.push_back(v);
    }
    std::cout << solve(arr, n);
}
