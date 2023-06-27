from sys import stdin, stdout
from typing import List, Tuple

class Solution:
    def twoSum(self, nums: List[int], target: int) -> Tuple[int, int]:
        for i in range(1, len(nums)):
            v = nums[i]
            for j in range(0, i):
                if target == v + nums[j]:
                    return i, j
        assert False, 'assumption that a valid two integer sum exists'


def parse_num_test_cases() -> int:
    return int(stdin.readline().strip())

def parse_test_case_input() -> Tuple[int, List[int]]:
    target_input = int(stdin.readline().strip())
    num_terms: [int] = list(map(int, stdin.readline().strip().split(' ')))
    return target_input, num_terms


def print_output(terms: List[int]):
    stdout.write(','.join(map(str, terms)))
    stdout.write('\n')

if __name__ == '__main__':
    s = Solution()
    num_cases = parse_num_test_cases()
    for _ in range(num_cases):
        target, terms = parse_test_case_input()
        result = s.twoSum(terms, target)
        print_output(result)
    
