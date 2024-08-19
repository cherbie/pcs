package main

import "fmt"

func longestCommonSubsequence(text1 string, text2 string) int {
	m, n := len(text1)+1, len(text2)+1
	dp := make([][]int, m)

	// initialize either case where length of string considered is zero
	for i := 0; i < m; i++ {
		dp[i] = make([]int, n)
	}

	// recursive DFS traversal of DP "tree"
	var f func(i, j int) int
	f = func(i, j int) int {
		if i == len(text1) || j == len(text2) {
			return 0
		}
		result := 0
		if text1[i] == text2[j] {
			result = 1 + f(i+1, j+1)
		} else {
			result = max(f(i+1, j), f(i, j+1))
		}
		dp[i][j] = result

		return result
	}

	return f(0, 0)
}

// this technique is faster than recursion
func memoizedLongestCommonSubsequence(text1, text2 string) int {
	m, n := len(text1)+1, len(text2)+1
	dp := make([][]int, m)

	// initialize memoized values
	for i := 0; i < m; i++ {
		dp[i] = make([]int, n)
	}

	for i := len(text1) - 1; i >= 0; i-- {
		for j := len(text2) - 1; j >= 0; j-- {
			if text1[i] == text2[j] {
				dp[i][j] = 1 + dp[i+1][j+1]
			} else {
				dp[i][j] = max(dp[i+1][j], dp[i][j+1])
			}
		}
	}

	return dp[0][0]
}

func main() {
	fmt.Printf("recursive: %s vs %s -> %d\n", "abcde", "bce", longestCommonSubsequence("abcde", "bce"))
	fmt.Printf("memoized: %s vs %s -> %d\n", "abcde", "bce", memoizedLongestCommonSubsequence("abcde", "bce"))
}
