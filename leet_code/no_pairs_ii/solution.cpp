#include <bits/stdc++.h>

using ll = long long;

class Solution
{
public:
    ll numberOfPairs(std::vector<int> &nums1, std::vector<int> &nums2, int k)
    {
        std::unordered_map<int, int> factorTable;

        // find the factors of nums1
        for (const auto e : nums1)
        {
            for (int i = 1; i * i <= e; i++)
                if (i * i == e)
                {
                    // special case that causes duplication of count
                    factorTable[i]++;
                }
                else if (e % i == 0)
                {
                    // is a factor
                    factorTable[i]++;
                    factorTable[e / i]++;
                }
        }

        ll sum = 0;
        // find the nums2 that are factors of nums1
        for (auto e2 : nums2)
        {
            e2 *= k;
            if (factorTable[e2] > 0)
            {
                sum += factorTable[e2];
            }
        }

        return sum;
    }
};

int main(int argc, char **argv)
{
    Solution s;
    std::vector<int> nums1 = {1, 3, 4};
    std::vector<int> nums2 = {1, 3, 4};
    std::cout << s.numberOfPairs(nums1, nums2, 2) << std::endl;
    return 0;
}