package main

import (
	"fmt"
	"slices"
)

func maximumDifference(nums []int) int {
	diff := make([]int, len(nums))
	diff[len(diff)-1] = 0

	// o(n^2)
	for idx := 0; idx < len(nums)-1; idx++ {
		for j := idx + 1; j < len(nums); j++ {
			diff[idx] = max(diff[idx], nums[j]-nums[idx])
		}
	}

	slices.Sort(diff) // nlogn

	if maxDiff := diff[len(diff)-1]; maxDiff > 0 {
		return maxDiff
	}
	return -1
}

func main() {
	input1 := []int{7, 1, 5, 4}
	fmt.Printf("input: %v | output: %v\n", input1, maximumDifference(input1))
}
