package main

import (
	"fmt"
)

// two-pointer approach
func pivotArray(nums []int, pivot int) []int {
	n := len(nums)
	l, r := 0, n-1
	res := make([]int, n)
	for i := 0; i < n; i++ {
		if v := nums[i]; v < pivot {
			res[l] = v
			l++
		}
		if v := nums[n-i-1]; v > pivot {
			// note: reading in reverse order
			res[r] = v
			r--
		}
	}

	for l <= r {
		res[l] = pivot
		l++
	}

	return res
}

func main() {
	input1 := []int{9, 12, 5, 10, 14, 3, 10}
	fmt.Printf("input: %v, %v | output: %v\n", input1, 10, pivotArray(input1, 10))
}
