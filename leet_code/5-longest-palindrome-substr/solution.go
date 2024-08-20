package main

import "fmt"

func longestPalindrome(str string) string {
	n := len(str)

	dp := make([][]int, 2) // even-odd dp
	dp[0] = make([]int, n)
	dp[1] = make([]int, n)

	// initialize for
	for i := 0; i < n; i++ {
		dp[1][i] = 1
	}

	start, maxLen := 0, 1
	for s := 2; s <= n; s++ {
		l, r, c, polarity := 0, s-1, s/2, s%2

		for r < n {
			if str[l] == str[r] && dp[polarity][c] >= s-2 {
				dp[polarity][c] = dp[polarity][c] + 2
				if maxLen < dp[polarity][c] {
					maxLen = dp[polarity][c]
					start = l
				}
			}
			l++
			r++
			c++
		}
	}

	return str[start : start+maxLen]
}

func main() {
	fmt.Println("i: babad -> output: ", longestPalindrome("babad"))
}
