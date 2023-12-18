package main

import (
	"bufio"
	"bytes"
	"errors"
	"fmt"
	"os"
	"slices"
	"strconv"
)

var (
	// []byte cannot be used in map type ... would need to covert to string
	numberWords = [][]byte{
		{'z', 'e', 'r', 'o'},
		{'o', 'n', 'e'},
		{'t', 'w', 'o'},
		{'t', 'h', 'r', 'e', 'e'},
		{'f', 'o', 'u', 'r'},
		{'f', 'i', 'v', 'e'},
		{'s', 'i', 'x'},
		{'s', 'e', 'v', 'e', 'n'},
		{'e', 'i', 'g', 'h', 't'},
		{'n', 'i', 'n', 'e'},
	}
)

// func splitFirstAndLastDigits(data []byte, atEOF bool) (advance int, token []byte, err error) {
// 	advance, token, err = bufio.ScanLines(data, atEOF)
// 	digits := make([]byte, 0, 10)
// 	for _, c := range token {
// 		if '0' <= c && c <= '9' {
// 			digits = append(digits, c)
// 		}
// 	}
// 	if len(digits) > 2 {
// 		digits = []byte{digits[0], digits[len(digits)-1]}
// 	} else if len(digits) == 1 {
// 		digits = []byte{digits[0], digits[0]}
// 	}

// 	if !atEOF {
// 		return 0, nil, nil
// 	} else if atEOF && token == nil {
// 		fmt.Println("final token -- ", token)
// 		return advance, nil, bufio.ErrFinalToken
// 	}

// 	return advance, digits, err
// }

func number2Digit(word []byte) (digit byte, err error) {
	if idx := slices.IndexFunc(numberWords, func(e []byte) bool {
		return bytes.Equal(e, word)
	}); idx == -1 {
		return '\x00', errors.New("could not identify digit")
	} else {
		return byte('0' + idx), nil
	}
}

// sliding window to find digits or words to map to digits
func findDigits(token []byte) (results []byte, err error) {
	results = make([]byte, 0, 10)
	for i := 0; i < len(token); i++ {
		for j := i + 1; j < len(token) && j-i < 6; j++ {
			window := token[i:j]
			if len(window) == 1 && '0' <= window[0] && window[0] <= '9' {
				results = append(results, window[0])
				break
			} else if digit, err := number2Digit(window); err != nil {
				fmt.Printf("not number: %s\n", window)
				continue
			} else {
				results = append(results, digit)
			}
		}
	}
	return results, nil
}

func splitFirstAndLastWords(data []byte, atEOF bool) (advance int, token []byte, err error) {
	if !atEOF {
		return 0, nil, nil
	}

	advance, token, err = bufio.ScanLines(data, atEOF)

	if atEOF && token == nil {
		fmt.Println("final token -- ", token)
		return advance, nil, bufio.ErrFinalToken
	} else if digits, err := findDigits(token); err != nil {
		panic(err)
	} else {
		if len(digits) > 2 {
			digits = []byte{digits[0], digits[len(digits)-1]}
		} else if len(digits) == 1 {
			digits = []byte{digits[0], digits[0]}
		}
		return advance, digits, err
	}
}

func main() {
	integerScanner := bufio.NewScanner(os.Stdin)

	integerScanner.Split(splitFirstAndLastWords)

	var sum int = 0
	for integerScanner.Scan() {
		token := integerScanner.Text()
		if len(token) == 0 {
			continue
		}

		if value, err := strconv.Atoi(token); err == nil {
			sum += value
		} else {
			panic("Error parsing integer token")
		}
	}

	if err := integerScanner.Err(); err != nil {
		fmt.Printf("Invalid input: %s", err)
		panic("Integer scanner error encounted")
	}

	fmt.Printf("Integer Sum: %d", sum)
}
