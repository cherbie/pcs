package main

import "fmt"

const (
	ROTTEN int = 2
	FRESH  int = 1
	EMPTY  int = 0
)

type Point struct {
	x int
	y int
}

// BFS across entire graph
// look at minimum depth achieved in saved DP
// if orange without connecting orange found, return -1

func orangesRotting(grid [][]int) int {
	points := make([]Point, 0, len(grid)*len(grid)/2)

	// list of components
	for rowIdx, row := range grid {
		for colIdx, orange := range row {
			if orange != EMPTY {
				points = append(points, Point{colIdx, rowIdx})
			}
		}
	}

	if len(points) == 0 {
		return 0
	}

	// BFS from rotten components
	visited := make(map[Point]int)
	for _, point := range points {
		if grid[point.y][point.x] != ROTTEN {
			continue
		}
		visited[point] = 0
		bfsUtil(grid, &visited, point)
	}

	// find max depth of the minimum tree distance
	maxDepth := 0
	for _, component := range points {
		if depth, isSeen := visited[component]; !isSeen {
			return -1
		} else {
			// TODO: check if all components have been seen
			maxDepth = max(maxDepth, depth+1)
		}
	}

	return maxDepth - 1
}

func bfsUtil(grid [][]int, dp *map[Point]int, component Point) {
	queue := make([]Point, 0, 16)
	queue = append(queue, component)
	visited := make(map[Point]bool)
	visited[component] = true

	for len(queue) != 0 {
		point := queue[0]
		queue = queue[1:]
		depth := (*dp)[point]

		for _, transform := range []Point{{0, 1}, {1, 0}, {-1, 0}, {0, -1}} {
			if x := point.x + transform.x; x >= 0 && x < len(grid[0]) {
				if y := point.y + transform.y; y >= 0 && y < len(grid) {
					transformPoint := Point{x, y}
					if _, isSeen := visited[transformPoint]; isSeen {
						continue
					}

					if orange := grid[transformPoint.y][transformPoint.x]; orange != EMPTY {
						if prevDepth, isSeen := (*dp)[transformPoint]; !isSeen {
							(*dp)[transformPoint] = depth + 1
						} else {
							(*dp)[transformPoint] = min(depth+1, prevDepth)
						}
						queue = append(queue, transformPoint)
						visited[transformPoint] = true
					}
				}
			}
		}
	}
}

func main() {
	testCase := [][]int{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}
	fmt.Println("test case 1: ", testCase, " | expected: ", 4)
	fmt.Println("result: ", orangesRotting(testCase))

	testCase = [][]int{{2, 1, 1}, {0, 1, 1}, {1, 0, 1}}
	fmt.Println("test case 2: ", testCase, " | expected: ", -1)
	fmt.Println("result: ", orangesRotting(testCase))
}
