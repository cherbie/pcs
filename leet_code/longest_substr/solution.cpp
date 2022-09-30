#include "bits/stdc++.h"

int lengthOfLongestSubstring(const std::string &s)
{
    int max = 0;
    auto start_it = s.begin();
    // O(n)
    while (start_it != s.end())
    {
        auto max_it = start_it;
        max_it++;
        std::set<char> seen;
        // O(n)
        while (max_it != s.end())
        {
            // O(log(n))
            if (seen.find(*max_it) != seen.end())
            {
                // already seen
                max = std::max(max, (int)std::distance(start_it, max_it) - 1);
                break;
            }
            // else
            seen.insert(*max_it);
            max_it++;
        }
        start_it++;
    }
    return max;
}

int main(int argc, char** argv)
{
    std::string s;
    std::cin >> s;
    std::cout << lengthOfLongestSubstring(s) << std::endl;
}


