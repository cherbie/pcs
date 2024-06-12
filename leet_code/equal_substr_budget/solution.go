package main

func equalSubstring(s string, t string, maxCost int) int {
	diff := make([]int, len(s))
	for i := 0; i < len(s); i++ {
		d := int(s[i]) - int(t[i])
		if d < 0 {
			d *= -1
		}
		diff[i] = d
	}

	// two pointer surely
	maxLen := 0
	size := len(s)
	for i := 0; i < size && maxLen < size-i; i++ {
		sumCost := 0
		j := i
		for ; j < size; j++ {
			sumCost += diff[j]
			if sumCost > maxCost {
				break
			}
		}
		maxLen = max(maxLen, j-i)
	}
	return maxLen
}

func main() {

}
