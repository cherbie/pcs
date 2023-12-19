package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
)

func main() {
	if err := part2(); err != nil {
		panic(err)
	}
}

var numbersRegex = regexp.MustCompile(`\d+`)

type Field struct {
	field []byte
	cols  int
	rows  int
}

type PosGroup struct {
	value  int64
	minIdx int
	maxIdx int
}

type PosInfo struct {
	counted bool
	element byte
	group   *PosGroup
}

type PosMap = map[int](*PosInfo)

func readField() (field *Field, err error) {
	field = nil
	scanner := bufio.NewScanner(os.Stdin)

	scanner.Split(bufio.ScanLines)

	for scanner.Scan() {
		line := scanner.Text()
		if field == nil {
			field = &Field{[]byte(line), len(line), 1}
		} else {
			field.field = append(field.field, []byte(line)...)
			field.rows++
		}
	}

	if err := scanner.Err(); err != nil {
		return nil, err
	}

	return field, nil
}

func getAdjacentIndices(pos int, rows int, cols int) []int {
	list := make([]int, 0, 8)
	maxIdx := rows*cols - 1

	for i := -1; i <= 1; i++ {
		for j := -1; j <= 1; j++ {
			idx := pos + (j * cols) + i
			if idx == pos || idx < 0 || idx > maxIdx {
				continue
			} else {
				list = append(list, idx)
			}
		}
	}
	return list
}

func initPositionsMap(field *Field) PosMap {
	positions := make(PosMap)
	for idx, element := range field.field {
		positions[idx] = &PosInfo{false, element, nil}
	}
	return positions
}

func isSymbol(e byte) bool {
	return !(('0' <= e && e <= '9') || e == '.')
}

func part2() error {
	field, err := readField()
	if err != nil {
		return err
	}

	positions := initPositionsMap(field)

	matches := numbersRegex.FindAllStringSubmatchIndex(string(field.field), -1)
	for _, matchIdxs := range matches {
		var (
			low  = matchIdxs[0]
			high = matchIdxs[1]
		)
		fmt.Printf("number: %s\n", field.field[low:high])
		num, err := strconv.ParseInt(string(field.field[low:high]), 10, 0)
		if err != nil {
			return err
		}

		group := &PosGroup{num, low, high - 1}
		for idx := low; idx < high; idx++ {
			positions[idx].group = group
		}
	}

	// map symbols to gears
	symbol2GearMap := make(map[int][](*PosInfo))
	for idx, el := range field.field {
		if !isSymbol(el) {
			continue
		}

		for _, adjacentIdx := range getAdjacentIndices(idx, field.rows, field.cols) {
			adjPos := positions[adjacentIdx]
			if adjPos.group != nil {
				// has a gear
				symbol2GearMap[idx] = append(symbol2GearMap[idx], adjPos)
				fmt.Println("symbol: ", string(el), " - ", idx, " | ", adjacentIdx, " adjacent: ", adjPos, " group: ", adjPos.group)

			}
		}
	}

	var sumOfGear int64 = 0
	for _, gearPos := range symbol2GearMap {

		// find set of "gears"
		gearSet := make(map[*PosGroup]bool)
		for _, pos := range gearPos {
			if !pos.counted {
				gearSet[pos.group] = true
			}
		}

		if len(gearSet) == 2 {
			var gearRatio int64 = 0
			for gearInfo := range gearSet {
				if gearRatio == 0 {
					gearRatio += gearInfo.value
				} else {
					gearRatio *= gearInfo.value
				}
			}
			sumOfGear += gearRatio

			// set related as counted
			for _, pos := range gearPos {
				for childIdx := pos.group.minIdx; childIdx <= pos.group.maxIdx; childIdx++ {
					positions[childIdx].counted = true
				}
			}
		}
	}

	fmt.Println("Sum of gear ratios: ", sumOfGear)

	return nil
}

func part1() error {
	field, err := readField()
	if err != nil {
		return err
	}

	positions := initPositionsMap(field)

	matches := numbersRegex.FindAllStringSubmatchIndex(string(field.field), -1)
	for _, matchIdxs := range matches {
		var (
			low  = matchIdxs[0]
			high = matchIdxs[1]
		)
		fmt.Printf("number: %s\n", field.field[low:high])
		num, err := strconv.ParseInt(string(field.field[low:high]), 10, 0)
		if err != nil {
			return err
		}

		group := &PosGroup{num, low, high - 1}
		for idx := low; idx < high; idx++ {
			positions[idx].group = group
		}
	}

	var sumOfPartNo int64 = 0
	for idx, el := range field.field {
		if !isSymbol(el) {
			continue
		}

		for _, adjacentIdx := range getAdjacentIndices(idx, field.rows, field.cols) {
			adjPos := positions[adjacentIdx]
			if !adjPos.counted && adjPos.group != nil {
				fmt.Println(adjacentIdx, " adjacent: ", adjPos, " group: ", adjPos.group)
				// add value
				sumOfPartNo += adjPos.group.value

				// set related as counted
				for childIdx := adjPos.group.minIdx; childIdx <= adjPos.group.maxIdx; childIdx++ {
					positions[childIdx].counted = true
				}
			}
		}
	}

	fmt.Println("Sum of part no.: ", sumOfPartNo)

	return nil
}
