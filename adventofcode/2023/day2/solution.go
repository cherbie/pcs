package main

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"
)

func main() {
	if err := part2(); err != nil {
		panic(err)
	}
}

type Game struct {
	id    int
	red   int
	green int
	blue  int
}

var (
	gameIdRegex    = regexp.MustCompile(`Game (\d+)`)
	gameStateRegex = regexp.MustCompile(`(\d+) (red|green|blue)+`)
)

func parseGameInputLine(line string) (games []Game, err error) {
	gameId := 0

	if match := gameIdRegex.FindStringSubmatch(line); match == nil {
		return nil, errors.New("error with regexp match for game id")
	} else if parsedId, err := strconv.Atoi(match[1]); err != nil {
		return nil, err
	} else {
		gameId = parsedId
	}

	for _, term := range strings.Split(line, ";") {
		gameStateMatches := gameStateRegex.FindAllStringSubmatch(term, -1)
		if gameStateMatches == nil {
			return nil, errors.New("no game state matches")
		}

		game := Game{gameId, 0, 0, 0}
		for _, submatch := range gameStateMatches {
			if numberFound, err := strconv.Atoi(submatch[1]); err != nil {
				return nil, err
			} else {
				switch submatch[2] {
				case "red":
					game.red += numberFound
				case "green":
					game.green += numberFound
				case "blue":
					game.blue += numberFound
				}
			}
			games = append(games, game)
		}
	}

	return games, nil
}

func part2() error {
	scanner := bufio.NewScanner(os.Stdin)

	scanner.Split(bufio.ScanLines)

	const (
		maxRed   = 12
		maxGreen = 13
		maxBlue  = 14
	)

	type GameOutcome struct {
		minRed   int
		minGreen int
		minBlue  int
	}

	savedGames := make(map[int]*GameOutcome)
	for scanner.Scan() {
		line := scanner.Text()

		if games, err := parseGameInputLine(line); err != nil {
			return err
		} else {
			for _, game := range games {
				if savedGames[game.id] == nil {
					savedGames[game.id] = &GameOutcome{}
				}
				prevOutcome := savedGames[game.id]

				prevOutcome.minRed = max(prevOutcome.minRed, game.red)
				prevOutcome.minGreen = max(prevOutcome.minGreen, game.green)
				prevOutcome.minBlue = max(prevOutcome.minBlue, game.blue)
			}
		}
	}

	if err := scanner.Err(); err != nil {
		return err
	}

	products := make([]int, len(savedGames))
	for gameId, state := range savedGames {
		products[gameId-1] = state.minRed * state.minGreen * state.minBlue
	}

	sumOfProducts := 0
	for _, product := range products {
		sumOfProducts += product
	}

	fmt.Println("Sum of products: ", sumOfProducts)
	return nil
}

func part1() error {
	scanner := bufio.NewScanner(os.Stdin)

	scanner.Split(bufio.ScanLines)

	const (
		maxRed   = 12
		maxGreen = 13
		maxBlue  = 14
	)

	type GameOutcome struct {
		seen       bool
		impossible bool
	}

	impossibleGames := make(map[int]GameOutcome)
	for scanner.Scan() {
		line := scanner.Text()

		if games, err := parseGameInputLine(line); err != nil {
			return err
		} else {
			for _, game := range games {
				if !impossibleGames[game.id].seen {
					impossibleGames[game.id] = GameOutcome{true, false}
				}
				if !impossibleGames[game.id].impossible && (game.red > maxRed || game.green > maxGreen || game.blue > maxBlue) {
					impossibleGames[game.id] = GameOutcome{true, true}
				}
			}
		}
	}

	if err := scanner.Err(); err != nil {
		return err
	}

	sumOfIds := 0
	for k := range impossibleGames {
		if !impossibleGames[k].impossible {
			sumOfIds += k
		}
	}

	fmt.Println("Sum of ids: ", sumOfIds)
	return nil
}
