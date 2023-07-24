#include "bits/stdc++.h"

#define MAX_ASCII_CHAR_SIZE 256

int lengthOfLongestSubstring(const std::string &s)
{
    const int n = s.length();
    int store[MAX_ASCII_CHAR_SIZE] = {0};

    int left = 0, right = 0, result = 0;
    while (right < n)
    {
        store[static_cast<std::size_t>(s[right])]++;
        while (store[static_cast<std::size_t>(s[right])] > 1)
        {
            store[static_cast<std::size_t>(s[left])]--;
            left++;
        }
        right++;
        result = std::max(result, right - left);
    }
    return result;
}

int main(int argc, char **argv)
{
    int numTestCases = 0;
    std::cin >> numTestCases;

    for (int i = 0; i < numTestCases; i++)
    {
        std::string testCase;
        std::cin >> testCase;
        std::cout << testCase << ": " << lengthOfLongestSubstring(testCase) << std::endl;
    }
}
