#include "bits/stdc++.h"

int lengthOfLongestSubstring(const string &s)
{
    int max = 0;
    auto start_it = s.begin();
    std::map<const std::string, int> mem; 
    while (start_it != s.end())
    {
        auto max_it = start_it;
        while (max_it != s.end() && *max_it != *start_it
    }
}

int main(int argc, char** argv)
{
    std::string s;
    std::cin >> s;
    std::cout << lengthOfLongestSubstring(s) << std::endl;
}


