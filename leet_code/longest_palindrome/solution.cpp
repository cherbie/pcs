#include "bits/stdc++.h"

#define DEBUG

bool isPalindrome(const std::string &s)
{
    if (s.size() < 2)
        return false;
    auto f_it = s.begin();
    auto r_it = s.rbegin();
    while (f_it != s.end() && r_it != s.rend())
    {
        if (*f_it != *r_it)
            return false;
        f_it++;
        r_it++;
    }
    return true;
}

std::string longestPalindrome(std::string s)
{
    int maxLength = 1;
    std::size_t startIdx = 0;
    std::size_t endIdx = startIdx + maxLength - 1;
    std::pair<int, int> palindrome = std::make_pair(startIdx, endIdx);
    while (startIdx < s.size())
    {
        while (endIdx < s.size() && !isPalindrome(s.substr(startIdx, /*length*/ endIdx + 1 - startIdx)))
        {
            endIdx++;
        }

        if (endIdx >= s.size())
        {
            // not palindrome
            startIdx++;
            endIdx = startIdx + maxLength - 1;
        }
        else
        {
            int palindromeLength = (int)(endIdx - startIdx + 1);
#ifdef DEBUG
            std::cerr << "palindrome: " << s.substr(startIdx, palindromeLength)
                      << " | palindrome length: " << palindromeLength
                      << " | index: (" << startIdx << ", " << endIdx << ")";
#endif // ifdef DEBUG
            if (maxLength < palindromeLength)
            {
#ifdef DEBUG
                std::cerr << " | set max: " << palindromeLength;
#endif // ifdef DEBUG
                maxLength = palindromeLength;
                palindrome = std::make_pair<int, int>(startIdx, endIdx);
            }
#ifdef DEBUG
            std::cerr << std::endl;
#endif // ifdef DEBUG
            endIdx++;
        }
    }
    return s.substr(palindrome.first, palindrome.second - palindrome.first + 1);
}

int main(int argc, char **arv)
{
    std::cout << longestPalindrome("babad") << std::endl;
    std::cout << longestPalindrome("cbbd") << std::endl;
    std::cout << longestPalindrome("aacabdkacaa") << std::endl;
}