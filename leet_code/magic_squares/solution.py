from typing import List

class Solution:
    def numMagicSquaresInside(self, grid: List[List[int]]) -> int:
        rLen = len(grid)
        cLen = len(grid[0])
        if rLen < 3 or cLen < 3:
            return 0
        
        count = 0
        for r in range(rLen-2):
            for c in range(cLen-2):
                m = getMatrix3X3(grid, r, c)
                pSum, sSum, cSum, rSum = 0, 0, 0, 0
                seen = set()
                for i in range(3):
                    cSum, rSum = 0, 0
                    for j in range(3):
                        seen.add(m[i][j])
                        rSum += m[i][j]
                        cSum += m[j][i]
                        if i == j:
                            pSum += m[i][j]
                        if i + j == 2:
                            sSum += m[i][j]
                    if cSum != rSum:
                        break
                if pSum == sSum == cSum == rSum and seen == {1,2,3,4,5,6,7,8,9}:
                    count += 1
                
        return count


def getMatrix3X3(grid: List[List[int]], i: int, j: int) -> List[List[int]]:
    subGrid = []
    for r in range(3):
        subGrid.append(grid[i+r][j:j+3])
    return subGrid

if __name__ == '__main__':
    s = Solution()
    print(f'case 1: [[4,3,8,4],[9,5,1,9],[2,7,6,2]] = {s.numMagicSquaresInside([[4,3,8,4],[9,5,1,9],[2,7,6,2]])}')
