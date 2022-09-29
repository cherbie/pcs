#include <bits/stdc++.h>

// Complexity: O(M + N), where M = ranked.size() & N = player.size();
// @param ranked - the leaderboard scores (sorted max -> min) (descending order)
// @param player - the player's scores (ascending order)
// @return - the player's rank after each score
std::vector<int> climbingTheLeaderboard(std::vector<int> ranked, std::vector<int> player)
{
    auto ranked_it = ranked.begin();
    auto player_it = player.rbegin(); // iterate in reverse
    int rank = 1;
    while (player_it != player.rend())
    {
        int score = *player_it; // default score = current evaluated player
        while (ranked_it != ranked.end() && *ranked_it > *player_it)
        {
            if (score > *ranked_it) rank++;  // previous ranked_it greater

            score = *ranked_it;  // update greatest score
            ranked_it++;
        }
        if (score > *player_it) rank++; // one more rank difference from ranked list

        *player_it = rank;
        player_it++;
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
