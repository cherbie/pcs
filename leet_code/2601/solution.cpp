#include <bits/stdc++.h>

int largestPrime(int a, int b)
{
    for (int i = b - 1; i >= a; i--)
    {
        if (i < 2)
            continue;

        bool isPrime = true;

        for (int j = 2; j < i / 2; j++)
        {
            if (i % j == 0)
            {
                isPrime = false;
                break;
            }
        }

        if (isPrime)
            return i;
    }

    return -1;
}

bool primeSubOperation(std::vector<int> nums)
{
    // pick an index i that you haven’t picked before,
    // and pick a prime p strictly less than nums[i]
    // then subtract p from nums[i].

    if (largestPrime(0, nums[0]) > 0)
        nums[0] = nums[0] - largestPrime(0, nums[0]);

    for (std::size_t i = 0; i < nums.size() - 1; i++)
    {
        int maxPrime = largestPrime(nums[i], nums[i+1] - nums[i]);
        std::cerr << "(" << nums[i] << ", " << nums[i+1] << ", " << maxPrime << ") ";
        if (maxPrime < 0)
            return false;
        else nums[i+1] = nums[i+1] - maxPrime;
    }
    return true;
}

int main(int argc, char **argv)
{
    std::cout << (primeSubOperation(std::vector<int> {4, 9, 6, 10}) ? "true" : "false") << std::endl;
    std::cout << (primeSubOperation(std::vector<int> {6, 8, 11, 12}) ? "true" : "false") << std::endl;
    std::cout << (primeSubOperation(std::vector<int> {5, 8, 3}) ? "true" : "false") << std::endl;

    // failing
    std::cout << (primeSubOperation(std::vector<int> {998, 2}) ? "true" : "false") << std::endl;
}