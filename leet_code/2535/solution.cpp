#include <bits/stdc++.h>

/// leetcode runtime trick
static auto _ = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

constexpr int sumDigits(int n)
{
    int sum = 0;
    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

inline int differenceOfSum(const std::vector<int> &nums)
{
    int element_sum = 0, digit_sum = 0;
    for (auto n : nums)
    {
        element_sum += n;
        digit_sum += sumDigits(n);
    }
    return std::abs(element_sum - digit_sum);
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    std::vector<int> caseOne = {1, 15, 6, 3};
    std::cout << differenceOfSum(caseOne) << std::endl;
#endif // #ifdef DEBUG
}