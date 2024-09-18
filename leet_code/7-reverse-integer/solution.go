package main

import (
	"fmt"
	"math"
	"strconv"
)

func reverse(x int) int {
	s := strconv.Itoa(x)

	if x < 0 {
		s = s[1:] // remove negative
	}

	for i := 0; i < len(s); i++ {
		s = fmt.Sprintf("%s%s%s", s[:i], string(s[len(s)-1]), s[i:len(s)-1])
	}

	reverseNum, err := strconv.Atoi(s)
	if err != nil {
		return 0
	}

	if reverseNum > math.MaxInt32 {
		return 0
	}

	if x < 0 {
		return reverseNum * -1
	}

	return reverseNum
}

func main() {
	testCases := []int{123, -123, -321, 120, 0, 1534236469}
	expResults := []int{321, -321, -123, 21, 0, 0}

	for testCaseIdx, testCase := range testCases {
		result := reverse(testCase)
		expResult := expResults[testCaseIdx]

		fmt.Printf("Test case: %d ", testCase)
		if result != expResult {
			fmt.Printf("[failed]: %d != %d\n", result, expResult)
		} else {
			fmt.Printf("[success]")
		}
		fmt.Println()
	}
}
