package main

import "fmt"

// making use of reverse integer to check if palindrome
func isPalindrome(num int) bool {
	if num < 0 {
		return false
	}

	reversedNum := 0
	rem := num
	for rem != 0 {
		reversedNum = reversedNum*10 + rem%10
		rem /= 10
	}

	return reversedNum == num
}

func main() {
	testCases := []int{121, -121, 10}
	expResult := []bool{true, false, false}

	for idx, testCase := range testCases {
		result := isPalindrome(testCase)

		fmt.Printf("Test case: %d ", testCase)
		if result != expResult[idx] {
			fmt.Printf("[failed]: expected %t got %t", expResult[idx], result)
		} else {
			fmt.Printf("[success]")
		}
		fmt.Println()
	}
}
