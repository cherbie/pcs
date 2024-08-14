package main

import "fmt"

func findDuplicate(nums []int) int {
	slow, fast := nums[0], nums[0]

	slow = nums[slow]
	fast = nums[nums[fast]]

	// find "cycle" using tortiose and hare alg.
	for slow != fast {
		slow = nums[slow]
		fast = nums[nums[fast]]
	}

	slow = nums[0]
	for slow != fast {
		slow = nums[slow]
		fast = nums[fast]
	}

	return slow
}

func main() {
	fmt.Println("array: ", []int{2, 5, 9, 6, 9, 3, 8, 9, 7, 1}, " -> duplicate: ", findDuplicate([]int{2, 5, 9, 6, 9, 3, 8, 9, 7, 1}))
}
