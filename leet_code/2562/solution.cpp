#include <bits/stdc++.h>

using ll = long long;

#ifndef DEBUG
/// leetcode runtime trick
static auto _ = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
#endif // ifndef DEBUG

constexpr ll findMagnitude(ll number)
{
    ll magnitude = 10;
    while ((number / 10) > 0)
    {
        magnitude *= 10;
        number /= 10;
    }
    return magnitude;
}

constexpr ll findTheArrayConcVal(const std::vector<int> &nums)
{
    ll concatenation_sum = 0;
    std::size_t n_elements = nums.size();
    for (std::size_t i = 0; i < n_elements / 2; i++)
    {
        ll first = (ll)nums[i];
        ll second = (ll)nums[n_elements - 1 - i];
        ll concatenation = (first * findMagnitude(second)) + second;
        concatenation_sum += concatenation;
    }
    if (n_elements % 2 == 1)
        concatenation_sum += nums[n_elements / 2];
    return concatenation_sum;
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    const std::vector<int> caseOne = {7, 52, 2, 4};
    std::cout << findTheArrayConcVal(caseOne) << std::endl;

    const std::vector<int> caseTwo = {5, 14, 13, 8, 12};
    std::cout << findTheArrayConcVal(caseTwo) << std::endl;
#endif // #ifdef DEBUG
}