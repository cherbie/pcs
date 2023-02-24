#include <bits/stdc++.h>

using ll = long long;

/// leetcode runtime trick
static auto _ = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

/// @brief count the number of pairs whose sum is less than the _bound_ parameter
ll countLess(const std::vector<int>& nums, int bound) {
    ll res = 0;
    for (int i = 0, j = nums.size() - 1; i < j; ++i) {
        while(i < j && nums[i] + nums[j] > bound)
            --j;
        res += j - i;
    }        
    return res;
}

ll countFairPairs(std::vector<int> &nums, int lower, int upper)
{
    std::sort(nums.begin(), nums.end());
    return countLess(nums, upper) - countLess(nums, lower - 1);
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