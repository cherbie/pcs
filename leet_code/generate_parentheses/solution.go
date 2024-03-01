package main

import (
	"fmt"
)

func generateParenthesis(n int) []string {
	results := make([]string, 0, n*n)
	solve(0, 0, n, "", &results)
	return results
}

func solve(i int, j int, n int, s string, results *[]string) {
	if i == j && i == n {
		*results = append(*results, s)
		return
	}

	if i < n {
		solve(i+1, j, n, s+string('('), results)
	}
	if j < i {
		solve(i, j+1, n, s+string(')'), results)
	}
}

func main() {
	fmt.Println("test case: ", 3)
	fmt.Println("result: ", generateParenthesis((3)))
}
