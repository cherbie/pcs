#include <bits/stdc++.h>
#include <queue>
#include <numeric>

// Complexity: O(nlog(n))
// @param ranked - the leaderboard scores (sorted max -> min)
// @param player - the player's scores
// @return - the player's rank after each score
std::vector<int> climbingTheLeaderboard(std::vector<int> ranked, std::vector<int> player)
{
    for (int &v : player) 
    {
        std::pair<int /*rank*/, int /*score*/> lastRank = std::make_pair<int, int>(0, INT_MAX);
        ranked.push_back(v);
        for (auto score : ranked)
        {
            if (lastRank.second > score)
            {
                lastRank.first += 1;
                lastRank.second = score;
            }
            if (score <= v) break;
        }
        ranked.pop_back();
        v = lastRank.first;
    }
 
    return player;
}

void readIntToVec(std::vector<int> &vec, std::size_t n)
{
    for (std::size_t i = 0; i < n; i++)
    {
        int v = 0;
        std::cin >> v;
        vec.push_back(v);
    }
}

void printVec(std::vector<int> &vec)
{
    for (auto v : vec)
        std::cout << v << " ";
}

int main(int argc, char **argv)
{
    int n = 0, m = 0;
    std::vector<int> ranked, player; 
    std::cin >> n;
    // in
    readIntToVec(ranked, n);
    std::cin >> m;
    readIntToVec(player, m);
    
    // out
    auto newRankings = climbingTheLeaderboard(ranked, player);
    printVec(newRankings);
}
