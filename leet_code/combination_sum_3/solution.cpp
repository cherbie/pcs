#include "bits/stdc++.h"

#define MIN_NO 1
#define MAX_NO 9
#define DEBUG

namespace
{
    using combination_t = std::vector<int>;

    /// Find all possible valid combinations for a particular sum.
    /// @param k - number of terms in combination
    /// @param n - sum of combination
    /// @return vector of integer combinations
    std::vector<combination_t> combinationSum3(int k, int n)
    {
        std::vector<combination_t> combinations;
        for (int i = MIN_NO; i <= MAX_NO; i++)
        {
            combination_t comb;
            int sum = 0;
            for (int j = i; j <= MAX_NO; j++)
            {
                if (comb.size() < (std::size_t)k)
                {
                    comb.push_back(j);
                    sum += j;
                }

                if (comb.size() == (std::size_t)k)
                {
                    if (sum == n)
                        combinations.push_back(comb);
                    // remove the last index
                    sum -= comb.back();
                    comb.pop_back();
                }
            }
        }
#ifdef DEBUG
        for (auto comb : combinations)
        {
            for (auto i : comb)
            {
                std::cerr << i << ", ";
            }
            std::cerr << std::endl;
        }
#endif // ifdef DEBUG
        return combinations;
    } // combinationSum3
} // namespace

int main(int argc, char **argv)
{
    ::combinationSum3(3, 7);
}
