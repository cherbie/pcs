package main

import (
	"fmt"
	"sort"
	"math"
)


func maxSum(nums []int) int {
    sort.Sort(sort.Reverse(sort.IntSlice(nums)))

    sum := 0
    prev := math.MinInt
    seen := false
    for i := 0; i < len(nums); i++ {
        if val := nums[i]; val != prev && (!seen || val >= 0) {
            sum += val;
            prev = val
            seen = true
        }
    }

    return sum;
}

func main() {
	input1 := []int { -1, 0, 2, 3, 4 };
	fmt.Printf("input: %v ; output: %d\n", input1, maxSum(input1));
}
