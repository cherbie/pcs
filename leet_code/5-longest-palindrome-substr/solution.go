package main

import "fmt"

func longestPalindrome(s string) string {
	if len(s) == 1 {
		return s
	}

	p := mancher(s)

	start, maxLen := 0, 1
	for i := 0; i < len(p); i += 1 {
		count := p[i] >> 1
		size := (count << 1) - ((i + 1) % 2) // if '#' then accounting for even case

		if size > maxLen {
			start = (i >> 1) - count + 1
			maxLen = size
		}
	}

	return s[start : start+maxLen]
}

// string hashing technique used to convert even string to odd string
// odd string results are not impacted
func mancher(s string) []int {
	t := ""
	for i := 0; i < len(s); i++ {
		t += "#" + string(s[i])
	}
	t += "#"

	p := mancherOdd(t)
	return p[1 : len(p)-1]
}

func mancherOdd(s string) []int {
	n := len(s)
	s = "^" + s + "$"
	p := make([]int, n+2)

	l, r := 0, 1 // right-most palindrome bounds (l,r)
	for i := 1; i <= n; i++ {
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

		for s[i-p[i]] == s[i+p[i]] {
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
	fmt.Println("odd case: abcbcba -> output: ", longestPalindrome("abcbcba"))
	fmt.Println("even case: aabb -> output: ", longestPalindrome("aabb"))
	fmt.Println("even case: abccba -> output: ", longestPalindrome("abccba"))
	fmt.Println("even case: bb -> output: ", longestPalindrome("bb"))
	fmt.Println("odd case: aaa -> output: ", longestPalindrome("aaa"))
	fmt.Println("odd case: aaa -> output: ", longestPalindrome("a"))
}
