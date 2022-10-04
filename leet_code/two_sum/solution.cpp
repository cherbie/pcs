#include <bits/stdc++.h>

std::vector<int> twoSum(std::vector<int>& nums, int target)
{
    std::sort(nums.begin(), nums.end());

    int left = 0, right = nums.size() - 1;
    while (nums[right] > target)
    {
        if (left == right)
            break;
        int test = right / 2;
        if (nums[test] >= target)
        {
            right = test;
        } else {
            left = test;
        }
    }
    // todo
}

int main(int argc, char** argv)
{
    int n, target;
    std::vector<int> nums;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        int v;
        std::cin >> v;
        nums.push_back(v);
    }
    std::cin >> target;
    
    std::vector<int> sums = twoSum(nums, target);
    
    for (const auto v : sums)
    {
        std::cout << v << " ";
    } 
}
