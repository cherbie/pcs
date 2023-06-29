from typing import List
from sys import stdin, stdout
from math import floor

class Solution:
        def isValidSudoku(self, board: List[List[str]]) -> bool:
            rm = [set() for _ in range(9)]
            cm = [set() for _ in range(9)]
            bm = [set() for _ in range(9)]

            for r in range(9):
                for c in range(9):
                    boxr = floor(r / 3)
                    boxc = floor(c / 3)
                    box = (boxr * 3) + boxc
                    v = board[r][c]
                    if len(v) == 0:
                        continue
                    sr = rm[r]
                    sc = cm[c]
                    sb = bm[box]
                    print(f'{r},{c},{box}')
                    print(f'{sr},{sc},{sb}')
                    if v in sr or v in sc or v in sb:
                        print(v)
                        return False
                    sr.add(v)
                    sc.add(v)
                    sb.add(v)
            return True


def parseNumCases() -> int:
    return int(stdin.readline().strip())


def parseSudokuBoard() -> List[List[str]]:
    board = []
    for _ in range(9):
        board.append([val.strip('][.\"')
                      for val in stdin.readline()
                                      .strip()
                                      .lstrip(',][')
                                      .rstrip(',][')
                                      .split(',')])
    return board


if __name__ == '__main__':
    s = Solution()
    t = parseNumCases()
    for _ in range(t):
        board = parseSudokuBoard()
        print(board)
        print(s.isValidSudoku(board))

