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

var numbersRegex = regexp.MustCompile(`([0-9])+|(\|)`)

type Game struct {
	winners []int
	picks   []int
}

type GameOutcome struct {
	wins int
}

func readGames() (games []Game, err error) {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Split(bufio.ScanLines)
	for scanner.Scan() {
		line := scanner.Text()
		if matches := numbersRegex.FindAllStringSubmatch(line, -1); matches == nil {
			return nil, errors.New("error: could not match regexp")
		} else {
			game := Game{}
			seenPipe := false
			for idx, submatches := range matches {
				if idx == 0 {
					// ignore game id
					continue
				}

				submatch := strings.Trim(submatches[0], " ")
				if submatch == "|" {
					seenPipe = true
					continue
				}
				if numberValue, err := strconv.Atoi(submatch); err != nil {
					return nil, err
				} else if seenPipe {
					game.picks = append(game.picks, numberValue)
				} else {
					game.winners = append(game.winners, numberValue)
				}
			}
			games = append(games, game)
		}
	}

	if err := scanner.Err(); err != nil {
		return nil, err
	}

	return games, nil
}

func calcGameOutcomes(games []Game) []GameOutcome {
	outcomes := make([]GameOutcome, 0, len(games))
	for _, game := range games {
		outcome := GameOutcome{}
		winningSet := make(map[int]bool)
		for _, draw := range game.winners {
			winningSet[draw] = true
		}

		for _, draw := range game.picks {
			if _, exists := winningSet[draw]; exists {
				outcome.wins++
			}
		}
		outcomes = append(outcomes, outcome)
	}
	return outcomes
}

func part1() error {
	games, err := readGames()
	if err != nil {
		return err
	}

	gameOutcomes := calcGameOutcomes(games)

	sumOfGamePoints := 0
	for _, outcome := range gameOutcomes {
		if outcome.wins > 0 {
			fmt.Println("shift: ", 1<<(outcome.wins-1), " wins: ", outcome.wins)
			sumOfGamePoints += 1 << (outcome.wins - 1)
		}
	}
	fmt.Println("Sum of game points: ", sumOfGamePoints)

	return nil
}

type ScratchCard struct {
	count int64
}

func calcScratchCardOutcomes(games []Game) []ScratchCard {
	scratchCards := make([]ScratchCard, len(games))
	gameOutcomes := calcGameOutcomes(games)

	for idx, outcome := range gameOutcomes {
		scratchCards[idx].count += 1

		if outcome.wins < 1 {
			continue
		}

		for j := 0; int64(j) < scratchCards[idx].count; j++ {
			for i := 1; i <= outcome.wins; i++ {
				scratchCards[idx+i].count += 1
			}
		}
	}
	return scratchCards
}

func part2() error {
	games, err := readGames()
	if err != nil {
		return err
	}

	scratchCards := calcScratchCardOutcomes(games)

	sumOfScratchCards := int64(0)
	for _, card := range scratchCards {
		sumOfScratchCards += card.count
	}

	fmt.Println("Sum of scratch cards: ", sumOfScratchCards)

	return nil
}
