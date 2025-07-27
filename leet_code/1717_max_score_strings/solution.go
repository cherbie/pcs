package main

import (
	"fmt"
)

func maximumGain(s string, x int, y int) int {
	score := 0
	r1, r2 := 'a', 'b'
	count1, count2 := 0, 0

	if x < y {
		x, y = y, x
		r1, r2 = r2, r1
	}

	for _, r := range s {
		if r == r1 {
			count1++
		} else if r == r2 {
			if count1 > 0 {
				// pair found
				count1--
				score += x
			} else {
				count2++
			}
		} else {
			score += min(count1, count2) * y
			count1, count2 = 0, 0
		}
	}

	if count1 != 0 {
		// any additional pairings
		score += min(count1, count2) * y
	}

	return score
}

func main() {
	input1 := "cdbcbbaaabab"
	fmt.Printf("input: %v | output: %d", input1, maximumGain(input1, 4, 5))
}
