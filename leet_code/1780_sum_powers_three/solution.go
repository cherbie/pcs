package main

import (
	"fmt"
)

// stanley sequence: https://en.wikipedia.org/wiki/Power_of_three
func checkPowersOfThree(n int) bool {
	q := n
	for q > 0 {
		if q%3 == 2 {
			return false
		}
		q /= 3
	}

	return true
}

func main() {
	fmt.Printf("input: %v | output: %v\n", 91, checkPowersOfThree(91))
}
