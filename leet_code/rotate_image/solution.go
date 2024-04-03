package main

import "fmt"

func rotate(matrix [][]int) {
	size := len(matrix)

	// swap along row
	for i := 0; i < size; i++ {
		for j := 0; j < size/2; j++ {
			k := size - j - 1
			tmp := int(matrix[i][j])
			matrix[i][j] = matrix[i][k]
			matrix[i][k] = tmp
		}
	}

	// swap non-transposed diagonal
	for i := 0; i < size; i++ {
		for j := 0; i+j < size-1; j++ {
			ki, kj := size-1-i, size-1-j
			tmp := int(matrix[kj][ki])
			matrix[kj][ki] = matrix[i][j]
			matrix[i][j] = tmp
		}
	}
}

func main() {
	testCase := [][]int{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}
	fmt.Println("input matrix: ", testCase)
	rotate(testCase)
	fmt.Println("solution: ", testCase)
}
