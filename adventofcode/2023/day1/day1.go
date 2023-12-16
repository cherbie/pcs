package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
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

func splitFirstAndLastWords(data []byte, atEOF bool) (advance int, token []byte, err error) {
	advance, token, err = bufio.ScanLines(data, atEOF)
	if r, err := regexp.Compile("(one|two|three|four|five|six|seven|eight|nine|ten|[0-9])"); err != nil {
		return 0, nil, err
	} else {
		submatch := r.FindAllSubmatch(token, -1)
		fmt.Println(submatch)
	}

	digits := make([]byte, 0, 10)
	for _, c := range token {
		if '0' <= c && c <= '9' {
			digits = append(digits, c)
		}

	}
	if len(digits) > 2 {
		digits = []byte{digits[0], digits[len(digits)-1]}
	} else if len(digits) == 1 {
		digits = []byte{digits[0], digits[0]}
	}

	if !atEOF {
		return 0, nil, nil
	} else if atEOF && token == nil {
		fmt.Println("final token -- ", token)
		return advance, nil, bufio.ErrFinalToken
	}

	return advance, digits, err
}

func main() {
	integerScanner := bufio.NewScanner(os.Stdin)

	integerScanner.Split(splitFirstAndLastWords)

	var sum int = 0
	var count int = 0
	for integerScanner.Scan() {
		count++
		if count > 10 {
			break
		}
		fmt.Println("-", integerScanner.Text())

		token := integerScanner.Text()
		if len(token) == 0 {
			continue
		}

		if value, err := strconv.Atoi(token); err == nil {
			fmt.Println("value: ", value)
			sum += value
		} else {
			panic("Error parsing integer token")
		}

		fmt.Println("count: ", count)
		fmt.Println("sum: ", sum)
	}

	if err := integerScanner.Err(); err != nil {
		fmt.Printf("Invalid input: %s", err)
		panic("Integer scanner error encounted")
	}

	fmt.Printf("Integer Sum: %d", sum)
}
