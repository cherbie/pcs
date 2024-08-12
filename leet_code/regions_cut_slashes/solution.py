from typing import List

class Solution:
    parent: List[int]
    rank: List[int] # tree depth optimization
    count: int # number of regions

    def regionsBySlashes(self, grid: List[str]) -> int:
        n = len(grid)
        sides = n+1
        self.parent = [x for x in range(sides * sides)]
        self.rank = [0] * (sides * sides)
        self.count = 0

        # connect all edges to cell 0
        for i in range(sides):
            for j in range(sides):
                if i == 0 or j == 0 or i == n or j == n:
                    cell = i * sides + j
                    self.union(0, cell)

        # link all connected components
        for i in range(n):
            s = grid[i]
            j = 0
            for c in s:
                if c == '\\':
                    cell1 = i * sides + j
                    cell2 = cell1 + sides + 1
                    self.union(cell1, cell2)
                elif c == '/':
                    cell1 = i * sides + j + 1
                    cell2 = cell1 + n
                    self.union(cell1, cell2)
                j += 1
        
        return self.count

    def find(self, v: int):
        if v == self.parent[v]:
            return v
        self.parent[v] = self.find(self.parent[v]) # optimization
        return self.parent[v]
    
    def union(self, a: int, b: int):
        aParent = self.find(a)
        bParent = self.find(b)

        if aParent == bParent:
            # they belong in the same disjoint set
            self.count += 1
        else:
            if self.rank[aParent] < self.rank[bParent]:
                self.parent[aParent] = bParent
            elif self.rank[aParent] > self.rank[bParent]:
                self.parent[bParent] = aParent
            else:
                self.parent[bParent] = aParent
                self.rank[aParent] += 1


if __name__ == '__main__':
    s = Solution()
    print(f'Number of regions for {['/\\',"\\/"]}: {s.regionsBySlashes(['/\\',"\\/"])}')
    print(f'Number of regions for {[" /","/ "]}: {s.regionsBySlashes([" /","/ "])}')