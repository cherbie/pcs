package main

import "fmt"

func twoSum(numbers []int, target int) []int {
	li, ri := 0, len(numbers)-1
	lt, rt := numbers[li], numbers[ri]
	for ri > li {
		sum := lt + rt
		if sum == target {
			break
		} else if sum < target {
			li++
			lt = numbers[li]
		} else {
			ri--
			rt = numbers[ri]
		}
	}
	return []int{li + 1, ri + 1}
}

func main() {
	fmt.Println("test case: ", []int{2, 7, 11, 15}, " | target = ", 9)
	fmt.Println("result: ", twoSum([]int{2, 7, 11, 15}, 9))
}
