import sys
from typing import List

class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        anagrams = dict()
        for word in strs:
            sorted_word = str(sorted(word))
            grouping = anagrams.setdefault(sorted_word, list())
            grouping += [word]
        
        return anagrams.values()


if __name__ == '__main__':
    s = Solution()
    groupings = s.groupAnagrams([line.strip() for line in sys.stdin])
    print(groupings)

