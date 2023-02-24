#include <bits/stdc++.h>

#ifndef DEBUG
/// leetcode runtime trick
static auto _ = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
#endif // ifndef DEBUG

#define NUM_BITS 20

int minOperations(unsigned int n) {
    int count = 0;
    for (int i = 0; i < NUM_BITS; i++)
    {
        std::bitset<NUM_BITS> updated_bits = std::bitset<NUM_BITS>(n + (1 << i));
        std::bitset<NUM_BITS> bits(n);
        if (updated_bits.count() < bits.count())
        {
            n += (1 << i);
            count++;
        }
    }
    return count + (std::bitset<NUM_BITS>(n)).count();
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    std::cout << 74415 << " - " << minOperations(74415) << std::endl;
    std::cout << 39 << " - " << minOperations(39) << std::endl;
#endif // #ifdef DEBUG
}