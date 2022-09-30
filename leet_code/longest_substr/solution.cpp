#include "bits/stdc++.h"

int lengthOfLongestSubstring(const std::string &s)
{
    int store[sizeof(char)] = {0};
    int left = 0, right = 0;
    int result = 0;
    while(right < (int)s.length()){
        store[(int)s[right]]++;
        while(store[(int)s[right]] > 1){
            store[(int)s[left]]--;
            left++;
        }
        right++;
        result = std::max(result, right - left);
    }
    return result;
}

int main(int argc, char** argv)
{
    std::string s;
    std::cin >> s;
    std::cout << lengthOfLongestSubstring(s) << std::endl;
}


