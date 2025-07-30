package main

import (
	"fmt"
	"slices"
)

func findLucky(arr []int) int {
	slices.Sort(arr) // nlogn
	counts := make(map[int]int)
	for _, v := range arr {
		counts[v] += 1
	}
	maxFreq := -1
	for _, v := range arr {
		if v == counts[v] {
			maxFreq = v
		}
	}
	return maxFreq
}

func main() {
	input1 := []int{2, 2, 3, 4}
	fmt.Printf("input: %v | output: %v", input1, findLucky(input1))
}
