from typing import List
from pprint import pprint
from copy import deepcopy

FILENAME = 'input.txt'

def parse_tree_grid():
    row_tree_grid = []
    with open(FILENAME, 'r') as f:
        for line in f:
            line = line.strip()
            row_tree_grid.append([int(c) for c in line])
    return row_tree_grid

def transpose_tree_grid(grid: List[List[int]]):
    num_rows = len(grid)
    num_cols = len(grid[0])
    t_grid = deepcopy(grid[:][:])
    for r in range(0, num_rows):
        for c in range(0, num_cols):
            t_grid[c][r] = grid[r][c]
    return t_grid

def calc_row_wise_idx(r: int, c: int, num_cols: int):
    return r * num_cols + c

def part1():
    row_grid = parse_tree_grid()
    col_grid = transpose_tree_grid(row_grid)

    num_cols = len(col_grid)
    num_rows = len(row_grid)
    seen_grid = [False] * num_cols * num_rows  # row wise
    
    for r in range(1, num_rows-1):
        for c in range(1, num_cols-1):
            idx = calc_row_wise_idx(r, c, num_cols)
            height = row_grid[r][c]

            # top
            top = (r-1, c) if r-1 >= 0 else None
            if top is not None and not seen_grid[idx]:
                trees_above = col_grid[c][:r]
                # print(f'a={trees_above}')
                if len(list(filter(lambda x: x < height, trees_above))) == len(trees_above):
                    seen_grid[idx] = True

            # bottom
            bottom = (r+1, c) if r+1 < num_rows else None
            if bottom is not None and not seen_grid[idx]:
                trees_below = col_grid[c][:r:-1]
                if len(list(filter(lambda x: x < height, trees_below))) == len(trees_below):
                    seen_grid[idx] = True
            
            # left
            left = (r, c-1) if c-1 >= 0 else None
            if left is not None and not seen_grid[idx]:
                trees_left = row_grid[r][:c]
                if len(list(filter(lambda x: x < height, trees_left))) == len(trees_left):
                    seen_grid[idx] = True

            # right
            right = (r, c+1) if c+1 < num_cols else None
            if right is not None and not seen_grid[idx]:
                trees_right = row_grid[r][:c:-1]
                if len(list(filter(lambda x: x < height, trees_right))) == len(trees_right):
                    seen_grid[idx] = True

    return len(list(filter(lambda x: x, seen_grid)))


def part2():
    row_grid = parse_tree_grid()
    col_grid = transpose_tree_grid(row_grid)

    num_cols = len(col_grid)
    num_rows = len(row_grid)
    
    max_scenic_score = 0
    for r in range(1, num_rows-1):
        for c in range(1, num_cols-1):
            height = row_grid[r][c]

            # top
            ts, bs, rs, ls = (0, 0, 0, 0)
            trees_above = col_grid[c][:r]
            for s in trees_above[::-1]:
                ts += 1
                if s >= height:
                    break

            # bottom
            trees_below = col_grid[c][:r:-1]
            for s in trees_below[::-1]:
                bs += 1
                if s >= height:
                    break

            # left
            trees_left = row_grid[r][:c]
            for s in trees_left[::-1]:
                ls += 1
                if s >= height:
                    break

            # right
            trees_right = row_grid[r][:c:-1]
            for s in trees_right[::-1]:
                rs += 1
                if s >= height:
                    break

            scenic_score = ts * bs * rs * ls
            max_scenic_score = max(max_scenic_score, scenic_score)

    return max_scenic_score

if __name__ == '__main__':
    print(f'part 1 = {part1()}')
    print(f'part 2 = {part2()}')