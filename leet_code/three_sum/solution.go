package main

import (
	"fmt"
	"slices"
)

func main() {
	fmt.Println("test case: ", []int{-1, 0, 1, 2, -1, -4})
	fmt.Println("result: ", threeSum([]int{-1, 0, 1, 2, -1, -4}))
}

func threeSum(nums []int) [][]int {
	slices.Sort(nums)

	results := make([][]int, 0)

	for i := 0; i < len(nums)-2; i++ {
		if nums[i] > 0 {
			break
		}

		if i > 0 && nums[i-1] == nums[i] {
			continue
		}

		j, k := i+1, len(nums)-1
		target := -1 * nums[i]
		for j < k {
			twoSum := nums[j] + nums[k]
			if twoSum == target {
				results = append(results, []int{nums[i], nums[j], nums[k]})
				j++

				for j < k && nums[j-1] == nums[j] {
					j++
				}

				for k > j && nums[k-1] == nums[k] {
					k--
				}
			} else if twoSum < target {
				j++
			} else {
				k--
			}
		}
	}
	return results
}
