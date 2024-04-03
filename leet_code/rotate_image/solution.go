package main

import "fmt"

func rotate(matrix [][]int) {
	size := len(matrix)

	for i := 0; i < size; i++ {
		// Transpose of row
		for j := i; j < size; j++ {
			matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
		}
		// flipping the row
		for j, k := 0, size-1; j < k; j, k = j+1, k-1 {
			matrix[i][j], matrix[i][k] = matrix[i][k], matrix[i][j]
		}
	}
}

func main() {
	testCase := [][]int{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}
	fmt.Println("input matrix: ", testCase)
	rotate(testCase)
	fmt.Println("solution: ", testCase)
}
