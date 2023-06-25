import sys

class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        return sorted(s) == sorted(t)


def getTwoWordsFromStdin():
    words = []
    for _ in range(2):
        words += [sys.stdin.readline()]
    return words

if __name__ == '__main__':
    s = Solution()
    word1, word2 = getTwoWordsFromStdin()
    print(s.isAnagram(word1, word2))

