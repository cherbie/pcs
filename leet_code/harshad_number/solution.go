package main

import "fmt"

func sumOfTheDigitsOfHarshadNumber(x int) int {
	if x == 100 {
		return 1
	}

	sum := (x % 10) + (x / 10)
	if x%sum == 0 {
		return sum
	}

	return -1
}

func main() {
	fmt.Println("number: ", 18, " -> sum: ", sumOfTheDigitsOfHarshadNumber(18))
}
