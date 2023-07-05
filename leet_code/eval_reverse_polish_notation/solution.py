from sys import stdin, stdout
from typing import List
import math

def evaluateOperation(left: int, right: int, operation: str) -> int:
    if operation == '+':
        return left + right
    elif operation == '-':
        return left - right
    elif operation == '*':
        return left * right
    elif operation == '/':
        return int(left / right)
    assert False, 'Unrecognised operator'


class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        terms = []
        # everytime you encounter an operator evaluate the last two terms in that expression.
        for token in tokens:
            if token in ['+','-','*','/']:
                right = terms.pop()
                left = terms.pop()
                evalTerm = evaluateOperation(left, right, token)
                terms.append(evalTerm)
            else:
                terms.append(int(token))
        return terms[0]


def parseNumTests() -> int:
    return int(stdin.readline().strip())


def parseTestTokens() -> List[str]:
    return [x.strip('"')
            for x in
            stdin.readline().strip().strip('[]').split(',')]

if __name__ == '__main__':
    s = Solution()
    numTests = parseNumTests()
    for _ in range(numTests):
        tokens = parseTestTokens()
        print(s.evalRPN(tokens))

