package main

import (
	"slices"
	"sort"
)

func specialArray(nums []int) int {
	sort.Ints(nums)

	for i := 0; i <= 1000; i++ {
		idx, _ := slices.BinarySearch(nums, i)
		if len(nums)-idx == i {
			return i
		}
	}
	return -1
}

func main() {
}
