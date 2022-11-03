#include "bits/stdc++.h"

int maxProfit(const std::vector<int> &prices)
{
        int profit = 0;
        unsigned int min = prices[0];
        for (auto e : prices)
        {
                min = std::min<int>(min, e);
                profit = std::max<int>(profit, e - min);
        }
        return profit;
}

int main(int argc, char **argv)
{
        const std::vector<int> test_case = {7, 6, 4, 3, 1};
        std::cout << maxProfit(test_case) << std::endl;
        return EXIT_SUCCESS;
}
