package main

import "fmt"

// Use the prefix sum technique to calculate the accumulated number of changes required for each diff
func minChanges(nums []int, k int) int {
	n := len(nums)
	changeCount := make([]int, k+2)
	// first index represents no change
	// all other indexes need to be offset hence
	changeCount[0] = n / 2 // max amount of changes to a nums

	for i := 0; i < n/2; i++ {
		l, r := nums[i], nums[n-1-i]
		diff := abs(l - r)
		// max possible diff for one change (can choose integer in range (0, k])
		maxDiff := max(l, r, k-l, k-r) // constraint: 0 <= l <= r <= k

		changeCount[diff] -= 1
		changeCount[diff+1] += 1    // diff+1 is to "cancel out" the reduction at the previous index (prefix sum)
		changeCount[maxDiff+1] += 1 // any diff greater than maxDiff will require 2 changes (one change already accounted for at index 0)
	}

	fmt.Println("frequency ", changeCount)

	// cycling through range (0, k) to determine number of changes for each X
	numChanges := 0
	ans := n / 2
	for i := 0; i <= k; i++ {
		numChanges += changeCount[i]
		ans = min(ans, numChanges)
		fmt.Println("i ", i, "numChanges ", numChanges, " ans ", ans)
	}
	return ans
}

func abs(value int) int {
	if value < 0 {
		return value * -1
	} else {
		return value
	}
}

func main() {
	// Test cases
	nums := []int{1, 0, 1, 2, 4, 3}
	k := 4
	println("expect 2, received: ", minChanges(nums, k))

	nums = []int{9, 2, 7, 7, 8, 9, 1, 5, 1, 9, 4, 9, 4, 7}
	k = 9
	println("expect 4, received: ", minChanges(nums, k))

	nums = []int{0, 1, 2, 3, 3, 6, 5, 4}
	k = 6
	println("expect 2, received: ", minChanges(nums, k))
}
