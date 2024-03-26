package main

import "fmt"

func strStr(haystack string, needle string) int {
	for li := 0; li <= len(haystack)-len(needle); li++ {
		ri := 0
		for ri < len(needle) && haystack[li+ri] == needle[ri] {
			if ri == len(needle)-1 {
				return li
			}
			ri++
		}
	}
	return -1
}

func main() {
	fmt.Println("test case: ", "tsadbutsad", "sad")
	fmt.Println("result: ", strStr("tsadbutsad", "sad"))
}
