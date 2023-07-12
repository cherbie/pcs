#include <bits/stdc++.h>

namespace
{
    constexpr bool isPalindrome(std::string seq)
    {
        seq.erase(std::remove_if(seq.begin(), seq.end(),
                                  [](unsigned char c)
                                  { return !std::isalnum(c); }),
                   seq.end());
        std::transform(seq.begin(), seq.end(), seq.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });

        auto r_it = seq.rbegin();
        for (auto it = seq.begin(); it != seq.end(); it++, r_it++)
        {
            if (*r_it != *it)
            {
                return false;
            }
        }
        return true;
    }
} // end namespace

int main(int argc, char **argv)
{
#ifdef DEBUG
    const std::string palindromeTestCase1 = "A man, a plan, a canal: Panama";

    std::cout << palindromeTestCase1
              << ": "
              << (::isPalindrome(palindromeTestCase1) ? "true" : "false")
              << std::endl;

    const std::string palindromeTestCase2 = "racecar";

    std::cout << palindromeTestCase2
              << ": "
              << (::isPalindrome(palindromeTestCase2) ? "true" : "false")
              << std::endl;
#endif // ifdef DEBUG

    return 0;
}
