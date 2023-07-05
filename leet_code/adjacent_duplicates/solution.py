from sys import stdin, stdout

class Solution:
    def removeDuplicates(self, s: str) -> str:
        stack = []
        for c in s:
            if stack and stack[-1] == c:
                stack.pop()
            else:
                stack.append(c)

        return ''.join(stack)


def parseNumberTestCases() -> int:
    return int(stdin.readline().strip())


def parseTestString() -> str:
    return stdin.readline().strip()


if __name__ == '__main__':
    s = Solution()
    nTests = parseNumberTestCases()
    for _ in range(nTests):
        testCase = parseTestString()
        result = s.removeDuplicates(testCase)
        print(result)

