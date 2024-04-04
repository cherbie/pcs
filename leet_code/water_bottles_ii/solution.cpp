#include <iostream>

class Solution
{
public:
    int maxBottlesDrunk(int numBottles, int numExchange)
    {
        int bottlesDrunk = 0;
        for (; numBottles >= numExchange; numExchange++)
        {
            bottlesDrunk += numExchange;
            numBottles -= numExchange - 1;
        }
        return bottlesDrunk + numBottles;
    }
};

#ifdef DEBUG
int main(int argc, char **argv)
{
    auto solution = Solution();
    std::cout << "no. bottles: " << 13 << std::endl
              << "no. exchange: " << 6 << std::endl
              << "result: " << solution.maxBottlesDrunk(13, 6) << std::endl;
    return EXIT_SUCCESS;
}
#endif