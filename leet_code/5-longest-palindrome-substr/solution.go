package main

import "fmt"

func longestPalindrome(s string) string {
	p := mancher_odd(s)

	fmt.Println(p)

	start, maxLen := 0, 1
	for i, count := range p {
		size := (count << 1) - 1
		if size > maxLen {
			start = i - count + 1
			maxLen = size
		}
	}

	return s[start : start+maxLen]
}

func mancher_odd(s string) []int {
	n := len(s)
	s = "^" + s + "$"
	p := make([]int, n+2)

	l, r := 0, 1 // right-most palindrome bounds (l,r)
	for i := 1; i <= n; i++ {
		fmt.Printf("%d: ", i)
		if i <= r {
			// use previously computed results for palindrome
			j := l + (r - i) // mirror point of i relative to centre of (l, r)
			if j-p[j] <= l {
				// special case: mirror point less than left bound (l)
				p[i] = r - i
			} else {
				p[i] = p[j]
			}
		}

		fmt.Println(p)

		for s[i-p[i]] == s[i+p[i]] {
			fmt.Printf("(%c,%c)|(%d,%d)\n", s[i-p[i]], s[i+p[i]], i-p[i], i+p[i])
			p[i]++
		}

		if r < (i + p[i]) {
			r = i + p[i]
			l = i - p[i]
		}
	}

	return p[1 : len(p)-1]
}

func main() {
	fmt.Println("odd case: abababc -> output: ", longestPalindrome("abababc"))
}
