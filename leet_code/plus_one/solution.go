package main

import "fmt"

func plusOne(digits []int) []int {
	carry := 1
	idx := len(digits) - 1
	for carry != 0 {
		if idx < 0 {
			tmp := make([]int, len(digits)+1)
			tmp[0] = carry
			copy(tmp[1:], digits)
			digits = tmp
			carry = 0
		} else {
			modulus := (digits[idx] + 1) % 10
			digits[idx] = modulus
			if modulus != 0 {
				carry = 0
			}
		}
		idx--
	}
	return digits
}

func main() {
	testCase := []int{2, 4, 9}
	fmt.Println("test case: ", testCase)
	fmt.Println("results: ", plusOne(testCase))
}
