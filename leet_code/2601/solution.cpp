#include <bits/stdc++.h>

int smallestPrime(int a, int b)
{
    for (int i = a; i < b; i++)
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

        if (isPrime && (i == 2 || i % 2 != 0))
            return i;
    }

    return -1;
}

bool primeSubOperation(std::vector<int> nums)
{
    // pick an index i that you haven’t picked before,
    // and pick a prime p strictly less than nums[i]
    // then subtract p from nums[i].

    // sieve algorithm

    auto it = nums.rbegin();

    while (it != nums.rend())
    {
        auto currentValue = *it;
        it++;
        if (it == nums.rend())
            return true;

        auto nextValue = *it;
        if (currentValue > nextValue)
            continue;

        auto primeNumber = smallestPrime(nextValue - currentValue + 1, nextValue);
        if (primeNumber < 0)
            return false;
        else
        {
            *it = nextValue - primeNumber;
        }
    }
    return true;
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    std::cout << (primeSubOperation(std::vector<int>{4, 9, 6, 10}) ? "true" : "false") << std::endl;
    std::cout << (primeSubOperation(std::vector<int>{1, 20, 7, 12, 4}) ? "true" : "false") << std::endl;
    std::cout << (primeSubOperation(std::vector<int>{3, 4, 10, 15, 6}) ? "true" : "false") << std::endl;
    std::cout << (primeSubOperation(std::vector<int>{5, 8, 3}) ? "true" : "false") << std::endl;

    // failing
    std::cout << (primeSubOperation(std::vector<int>{998, 2}) ? "true" : "false") << std::endl;
#endif // ifdef DEBUG
}