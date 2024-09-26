package main

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"regexp"
	"strconv"
)

func main() {
	if err := part1(); err != nil {
		panic(err)
	}
}

var instructionsRegex = regexp.MustCompile(`(R|D|L|U).*(\d+).*(#\w+)`)

const (
	MOVE_RIGHT uint8 = 0x1
	MOVE_DOWN  uint8 = 0x2
	MOVE_LEFT  uint8 = 0x3
	MOVE_UP    uint8 = 0x4
)

type Instruction struct {
	movement uint8
	length   int
	colour   string
}

func readInstructions() (instructions []Instruction, err error) {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Split(bufio.ScanLines)

	for scanner.Scan() {
		line := scanner.Text()
		if matches := instructionsRegex.FindAllStringSubmatch(line, -1); matches == nil {
			return nil, errors.New("error: could not match regexp")
		} else {
			instruction := Instruction{}
			switch matches[0][1] {
			case "R":
				instruction.movement = MOVE_RIGHT
			case "D":
				instruction.movement = MOVE_DOWN
			case "L":
				instruction.movement = MOVE_LEFT
			case "U":
				instruction.movement = MOVE_UP
			}
			if value, err := strconv.Atoi(matches[0][2]); err != nil {
				return nil, err
			} else {
				instruction.length = value
			}
			instruction.colour = matches[0][3]
			instructions = append(instructions, instruction)
		}
	}

	if err := scanner.Err(); err != nil {
		return nil, err
	}

	return instructions, nil
}

type Point struct {
	x    int
	y    int
	diff int
}

func calcVertices(instructions []Instruction) []Point {
	vertices := make([]Point, len(instructions))
	current := Point{}
	for idx, instruction := range instructions {
		current.diff = instruction.length
		switch instruction.movement {
		case MOVE_RIGHT:
			current.x += instruction.length
		case MOVE_DOWN:
			current.y -= instruction.length
		case MOVE_LEFT:
			current.x -= instruction.length
		case MOVE_UP:
			current.y += instruction.length
		}
		vertices[idx] = current
	}
	return vertices
}

func calcArea(vertices []Point) int64 {
	sumA := int64(0)
	sumB := int64(0)
	sumPerimeter := int64(vertices[0].diff)

	for i := 0; i < len(vertices)-1; i++ {
		sumA += int64(vertices[i].x * vertices[i+1].y)
		sumB += int64(vertices[i].y * vertices[i+1].x)
		sumPerimeter += int64(vertices[i+1].diff)
	}

	fmt.Println(sumPerimeter, sumA, sumB)

	absSum := sumA - sumB
	if absSum < 0 {
		absSum *= -1
	}

	return ((absSum + sumPerimeter) / 2) + 1
}

func part1() error {
	instructions, err := readInstructions()
	if err != nil {
		return err
	}

	fmt.Println(instructions)

	vertices := calcVertices(instructions)
	fmt.Println(vertices)

	fmt.Println("Area: ", calcArea(vertices))

	return nil
}
