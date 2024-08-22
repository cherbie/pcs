package main

import (
	"fmt"
	"math"
)

func diagonalPrime(nums [][]int) int {
	n := len(nums)
	maxPrime := 1
	for i := 0; i < n; i++ {
		d := nums[i][i]
		if d > maxPrime && isPrime(d) {
			maxPrime = d
		}
		d = nums[n-1-i][i]
		if d > maxPrime && isPrime(d) {
			maxPrime = d
		}
	}

	if maxPrime == 1 {
		return 0
	}

	return maxPrime
}

func isPrime(number int) bool {
	if number < 2 {
		return false
	}
	if number < 4 {
		return true
	}
	if number%2 == 0 || number%3 == 0 {
		return false
	}

	sqrt := int(math.Sqrt(float64(number)))
	for i := 5; i <= sqrt; i += 6 {
		if number%i == 0 || number%(i+2) == 0 {
			return false
		}
	}

	return true
}

func main() {
	fmt.Println("i: [[1,2,3],[4,5,6],[7,8,9]] | r: ", diagonalPrime([][]int{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}))
}
