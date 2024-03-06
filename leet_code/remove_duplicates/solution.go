package main

import "fmt"

func removeDuplicates(nums []int) int {
	idx := 0
	for _, n := range nums {
		if n > nums[idx] {
			idx++
			nums[idx] = n
		}
	}
	return idx + 1
}

func main() {
	testCase := []int{0, 0, 1, 1, 1, 2, 2, 3, 3, 4}
	fmt.Println("test case: ", testCase)
	fmt.Println("result: ", removeDuplicates(testCase))

	testCase = []int{1, 1, 2}
	fmt.Println("test case: ", testCase)
	fmt.Println("result: ", removeDuplicates(testCase))
}
