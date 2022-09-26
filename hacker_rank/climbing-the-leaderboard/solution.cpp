#include <bits/stdc++.h>

// Complexity: O(nlog(n))
// @param ranked - the leaderboard scores (sorted max -> min)
// @param player - the player's scores
// @return - the player's rank after each score
std::vector<int> climbingTheLeaderboard(std::vector<int> ranked, std::vector<int> player)
{
    using LeaderboardSet = std::set<int, std::greater<int>>;
    LeaderboardSet base = LeaderboardSet(ranked.begin(), ranked.end());

    for (int &v : player) 
    {
        LeaderboardSet round = base;
        auto result = round.insert(v);
        if (result.first == round.end())
        {
            std::cerr << "something went wrong" << std::endl;
            std::exit(1);
        }
        v = std::distance(round.begin(), result.first) + 1;
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
