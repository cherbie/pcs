#include "bits/stdc++.h"

namespace
{
    int maxProfit(const std::vector<int> &prices)
    {
        unsigned int profit = 0;
        unsigned int min = prices[0];
        for (auto e : prices)
        {
            min = std::min<int>(min, e);
            profit = std::max<int>(profit, e - min);
        }
        return profit;
    }

    std::vector<int> readline(void)
    {
        for (auto c = '\n'; (c = std::cin.peek()) != EOF && !std::isdigit(static_cast<unsigned char>(c)); std::cin.get())
        {
        }

        std::vector<int> terms;
        std::deque<int> digits;
        while (std::cin.peek() != EOF)
        {
            const char c = std::cin.get();
            if (std::isdigit(static_cast<unsigned char>(c)))
            {
                digits.push_back(std::atoi(&c));
            }
            else
            {
                int term = 0;
                for (int magnitude = 0; !digits.empty(); magnitude++, digits.pop_front())
                {
                    term += magnitude == 0 ? digits.front() : digits.front() * magnitude;
                }
                terms.push_back(term);

                if (c == '\n')
                {
                    break;
                }
            }
        }
        return terms;
    }
} // namespace

int main(int argc, char **argv)
{
    int numTestCases = 0;
    std::cin >> numTestCases;

    for (int i = 0; i < numTestCases; i++)
    {
        const auto testCase = ::readline();
        std::cout << ::maxProfit(testCase) << std::endl;
    }

    return EXIT_SUCCESS;
}
