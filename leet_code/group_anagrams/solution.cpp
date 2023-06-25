#include <bits/c++.h>

std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string> &strs)
{
    for (auto &str : strs)
    {
        // O(n)
        std::sort(str.begin(), str.end()); // O(w . log(w))
    }

    sort(strs.begin(), strs.end()); // O(n . log(n))

    std::vector<std::vector<std::string>> anagrams;
    for (int i = 0, j = 0; j < strs.size(); i++)
    {
        // O(n)
        if (i == 0)
        {
            anagrams.push_back(std::vector<std::string>{strs.at(i)});
            continue;
        }

        if (strs[i - 1] == strs[i])
        {
            anagrams[j].push_back(strs.at(i));
        }
        else
        {
            j++;
            anagrams.push_back(std::vector<std::string>{strs.at(i)});
        }
    }

    return anagrams;
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    auto anagrams = groupAnagrams(std::vector<std::string>{})
#endif // DEBUG
}
