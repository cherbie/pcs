package main

import (
	"fmt"
)

func countSymmetricIntegers(low int, high int) int {
	symCount := 0
	cache := make([]int, 10)
	// O(n*m)
	for ; low <= high; low++ {
		// extract digits and store in cache
		tmp := low
		pos := 0
		for ; tmp > 0; tmp /= 10 {
			cache[pos] = tmp % 10 // extract digit
			pos++
		}

		if pos&1 != 0 {
			// needs to be even no. digits
			continue
		}

		cl, cr := 0, 0
		for i := 0; i < pos/2; i++ {
			cl += cache[i]
			cr += cache[pos-i-1]
		}

		if cl == cr {
			symCount++
		}
	}

	return symCount
}

func main() {
	fmt.Printf("input: %v, %v | output: %v\n", 1200, 1230, countSymmetricIntegers(1200, 1230))
}
