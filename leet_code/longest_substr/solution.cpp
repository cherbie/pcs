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
        std::set<char> seen = {*start_it};
        // O(nlog(n))
        while (max_it != s.end() && seen.find(*max_it) == seen.end())
        {
            seen.insert(*max_it);
            max_it++;
        }
        max = std::max(max, (int)std::distance(start_it, max_it));
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


