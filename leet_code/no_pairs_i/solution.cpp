#include <bits/stdc++.h>

class Solution
{
public:
    int numberOfPairs(std::vector<int> &nums1, std::vector<int> &nums2, int k)
    {
        int sum = 0;
        for (const auto e1 : nums1)
            for (const auto e2 : nums2)
                if (e1 % (e2 * k) == 0)
                    sum++;
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