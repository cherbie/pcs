package main

import (
	"bufio"
	"container/heap"
	"fmt"
	"os"
)

func main() {
	if err := part2(); err != nil {
		panic(err)
	}
}

type HeatMap struct {
	field []int
	rows  int
	cols  int
}

func readCostMap() (heatMap *HeatMap, err error) {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Split(bufio.ScanLines)

	heatMap = &HeatMap{}

	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			break
		}
		cols := make([]int, len(line))
		for i, c := range line {
			cols[i] = int(c - '0')
		}
		heatMap.field = append(heatMap.field, cols...)
		heatMap.cols = len(line)
		heatMap.rows++
	}

	if err := scanner.Err(); err != nil {
		return nil, err
	}

	return heatMap, nil
}

func part1() error {
	heatMap, err := readCostMap()
	if err != nil {
		return err
	}

	minCost := minValuePath(*heatMap, 1, 3)

	fmt.Println("Min cost: ", minCost)

	return nil
}

func part2() error {
	heatMap, err := readCostMap()
	if err != nil {
		return err
	}

	minCost := minValuePath(*heatMap, 4, 10)

	fmt.Println("Min cost: ", minCost)

	return nil
}

var (
	UNDEFINED = [2]int{0, 0}
	RIGHT     = [2]int{1, 0}
	DOWN      = [2]int{0, 1}
	LEFT      = [2]int{-1, 0}
	UP        = [2]int{0, -1}
)

type Location struct {
	position  Position
	direction Direction
	heat      int
}

type Direction = [2]int // (dx, dy)
type Position = [2]int  // (x, y)

type HeatQueue []*Location

func (hq HeatQueue) Len() int { return len(hq) }

func (hq HeatQueue) Less(i, j int) bool {
	return hq[i].heat < hq[j].heat
}

func (hq *HeatQueue) Pop() interface{} {
	tmp := *hq
	if size := len(tmp); size == 0 {
		return nil
	} else {
		item := tmp[size-1]
		tmp[size-1] = nil
		*hq = tmp[0 : size-1]
		return item
	}
}

func (hq *HeatQueue) Push(x interface{}) {
	item := x.(*Location)
	*hq = append(*hq, item)
}

func (hq HeatQueue) Swap(i, j int) {
	hq[i], hq[j] = hq[j], hq[i]
}

func (loc Location) GetIndex(cols int) int {
	return loc.position[1]*cols + loc.position[0]
}

type Vector struct {
	idx       int
	direction Direction
}

func minValuePath(heatMap HeatMap, minMovement, maxMovement int) int {
	hq := make(HeatQueue, 0)
	heap.Init(&hq)

	heap.Push(&hq, &Location{Position{0, 0}, UNDEFINED, 0})
	seenSet := make(map[Vector]bool, len(heatMap.field))
	finalIdx := heatMap.cols*heatMap.rows - 1

	for hq.Len() != 0 {
		location := heap.Pop(&hq).(*Location)
		idx := location.GetIndex(heatMap.cols)

		if _, exists := seenSet[Vector{idx, location.direction}]; exists {
			continue
		} else if idx == finalIdx {
			return location.heat
		} else {
			seenSet[Vector{idx, location.direction}] = true
		}

		directions := [2]Direction{UNDEFINED, UNDEFINED}
		switch location.direction {
		case RIGHT, LEFT:
			directions[0] = UP
			directions[1] = DOWN
		case DOWN, UP:
			directions[0] = RIGHT
			directions[1] = LEFT
		case UNDEFINED:
			directions[0] = RIGHT
			directions[1] = DOWN
		}

		for _, direction := range directions {
			prevHeat := location.heat
			for k := 1; k <= maxMovement; k++ {
				pos := Position{location.position[0] + (k * direction[0]), location.position[1] + (k * direction[1])}

				if pos[0] < 0 || pos[1] < 0 || pos[0] >= heatMap.cols || pos[1] >= heatMap.rows {
					continue
				}

				newLoc := Location{pos, direction, -1}
				prevHeat += heatMap.field[newLoc.GetIndex(heatMap.cols)]
				newLoc.heat = prevHeat
				if k >= minMovement {
					heap.Push(&hq, &newLoc)
				}
			}
		}
	}
	panic("could not determine final index")
}
