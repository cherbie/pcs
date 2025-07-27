package main

import (
	"fmt"
)

func countHillValley(nums []int) int {
	diff := make([]int, len(nums)-1)
	for i := 0; i < len(nums)-1; i++ {
		diff[i] = nums[i+1] - nums[i]
	}

	count := 0
	// O(n)
	for i := 0; i < len(diff); i++ {
		for ; i < len(diff) && diff[i] == 0; i++ {
		}
		j := i + 1
		for ; j < len(diff) && diff[j] == 0; j++ {
		}
		if j < len(diff) && diff[i]*diff[j] < 0 {
			count++
		}
		i = j - 1
	}

	return count
}

func main() {
	input1 := []int { 2, 4, 1, 1, 6, 5 }
	fmt.Printf("input: %v | output: %d", input1, countHillValley(input1));
}
