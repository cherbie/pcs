#include <bits/stdc++.h>

using ll = long long;

/// leetcode runtime trick
static auto _ = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

constexpr ll n_choose_k(ll n, ll k)
{
    if (k > n)
        return 0;
    if (k * 2 > n)
        k = n - k;
    if (k == 0)
        return 1;

    ll result = n;
    for (ll i = 2; i <= k; ++i)
    {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}

constexpr ll countFairPairs(std::vector<int> &nums, int lower, int upper)
{
    std::sort(nums.begin(), nums.end());
    auto low_it = std::find(nums.begin(), nums.end(), [lower, upper](int v)
                            { return v >= lower && v <= upper; });
    if (low_it == nums.end())
        return 0;
    auto upper_it = std::find(nums.begin(), nums.end(), [lower, upper](int v)
                              { return v >= lower && v <= upper; });
    auto number_el = std::distance(low_it, upper_it);
    std::cerr << number_el << std::endl;
    return n_choose_k(number_el, 2);
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    std::vector<int> caseOne = {0, 1, 7, 4, 4, 5};
    std::cout << countFairPairs(caseOne, 3, 6) << std::endl;

    std::vector<int> caseTwo = {1, 7, 9, 2, 5};
    std::cout << countFairPairs(caseTwo, 11, 11) << std::endl;
#endif // #ifdef DEBUG
}