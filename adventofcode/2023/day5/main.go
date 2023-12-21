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
	if err := part2(); err != nil {
		panic(err)
	}
}

var (
	numbersRegex    = regexp.MustCompile(`(\d+)`)
	mappingKeyRegex = regexp.MustCompile(`(seed|soil|fertilizer|water|light|temperature|humidity|location)-to-(seed|soil|fertilizer|water|light|temperature|humidity|location)`)
)

const (
	SEED        uint8 = iota
	SOIL        uint8 = iota
	FERTILIZER  uint8 = iota
	WATER       uint8 = iota
	LIGHT       uint8 = iota
	TEMPERATURE uint8 = iota
	HUMIDITY    uint8 = iota
	LOCATION    uint8 = iota
)

const MAX_INT = int64(^uint(0) >> 1)

type MapKey struct {
	src  uint8
	dest uint8
}

type MapRange struct {
	t      uint8
	src    int64
	dest   int64
	length int64
}

type Snapshot struct {
	t     uint8
	value int64
}

type RuleSetMap = map[uint8][]MapRange

type SeedContext struct {
	seeds   []int64
	ruleset RuleSetMap
}

func parseMapKey(token string) uint8 {
	switch token {
	case "soil":
		return SOIL
	case "seed":
		return SEED
	case "fertilizer":
		return FERTILIZER
	case "water":
		return WATER
	case "light":
		return LIGHT
	case "temperature":
		return TEMPERATURE
	case "humidity":
		return HUMIDITY
	case "location":
		return LOCATION
	default:
		panic("unable to parse")
	}
}

func readSeedContext() (context *SeedContext, err error) {
	context = &SeedContext{}
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Split(bufio.ScanLines)

	// find seeds
	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			break
		}
		if matches := numbersRegex.FindAllStringSubmatch(line, -1); matches == nil {
			return nil, errors.New("error: could not match seeds regexp")
		} else {
			for _, submatch := range matches {
				if numberValue, err := strconv.ParseInt(submatch[0], 10, 0); err != nil {
					return nil, err
				} else {
					context.seeds = append(context.seeds, numberValue)
				}
			}
		}
	}

	// find mapping
	var currentMapKey (*MapKey) = nil
	context.ruleset = make(RuleSetMap)
	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			currentMapKey = nil
			continue
		} else if currentMapKey != nil {
			if numberMatches := numbersRegex.FindAllStringSubmatch(line, -1); numberMatches == nil {
				return nil, errors.New("error: could not match seeds regexp")
			} else {
				src, _ := strconv.ParseInt(numberMatches[1][0], 10, 0)
				dest, _ := strconv.ParseInt(numberMatches[0][0], 10, 0)
				length, _ := strconv.ParseInt(numberMatches[2][0], 10, 0)
				context.ruleset[currentMapKey.src] = append(context.ruleset[currentMapKey.src], MapRange{currentMapKey.dest, src, dest, length})
			}
		} else if mappingKeyMatches := mappingKeyRegex.FindAllStringSubmatch(line, -1); mappingKeyMatches == nil {
			return nil, errors.New("error identifying mapping key snapshots")
		} else {
			srcKey := mappingKeyMatches[0][1]
			destKey := mappingKeyMatches[0][2]
			currentMapKey = &MapKey{parseMapKey(srcKey), parseMapKey(destKey)}
			context.ruleset[currentMapKey.src] = make([]MapRange, 0, 10)
		}
	}

	if err := scanner.Err(); err != nil {
		return nil, err
	}

	return context, nil
}

func part1() error {
	context, err := readSeedContext()
	if err != nil {
		return err
	}

	minLocation := MAX_INT
	for _, seed := range context.seeds {
		if location, err := calcSeedLocation(seed, context.ruleset); err != nil {
			return err
		} else {
			minLocation = min(minLocation, location)
		}
	}

	fmt.Println("Min location: ", minLocation)
	return nil
}

func calcSeedLocation(seed int64, ruleset RuleSetMap) (location int64, err error) {
	minLocation := MAX_INT
	snapshots := make([]Snapshot, 0, 10)
	snapshots = append(snapshots, Snapshot{SEED, seed})
	for len(snapshots) > 0 {
		current := snapshots[0]
		snapshots = snapshots[1:]

		if current.t == LOCATION {
			minLocation = min(minLocation, current.value)
			continue
		}

		newSnapshots := make([]Snapshot, 0, len(ruleset[current.t]))
		var mappedType uint8 = SEED
		for _, rule := range ruleset[current.t] {
			mappedType = rule.t
			if rule.src <= current.value && current.value < (rule.src+rule.length) {
				value := rule.dest + current.value - rule.src
				newSnapshots = append(newSnapshots, Snapshot{rule.t, value})
			}
		}
		if len(newSnapshots) == 0 {
			snapshots = append(snapshots, Snapshot{mappedType, current.value})
		} else {
			snapshots = append(snapshots, newSnapshots...)
		}
	}
	return minLocation, nil
}

func part2() error {
	context, err := readSeedContext()
	if err != nil {
		return err
	}

	minLocation := MAX_INT
	for i := 0; i < len(context.seeds); i = i + 2 {
		fmt.Print(".")
		if location, err := calcSeedRangeMinLocation(SeedRange{context.seeds[i], context.seeds[i+1]}, context.ruleset); err != nil {
			return err
		} else {
			minLocation = min(minLocation, location)
		}
	}

	fmt.Println("Min location: ", minLocation)
	return nil
}

type SeedRange struct {
	value  int64
	length int64
}

func calcSeedRangeMinLocation(seed SeedRange, ruleset RuleSetMap) (location int64, err error) {
	minLocation := MAX_INT
	snapshots := make([]Snapshot, 0, 10)
	for i := int64(0); i < seed.length; i++ {
		snapshots = append(snapshots, Snapshot{SEED, seed.value + i})
	}
	for len(snapshots) > 0 {
		current := snapshots[0]
		snapshots = snapshots[1:]

		if current.t == LOCATION {
			minLocation = min(minLocation, current.value)
			continue
		}

		newSnapshots := make([]Snapshot, 0, len(ruleset[current.t]))
		var mappedType uint8 = SEED
		for _, rule := range ruleset[current.t] {
			mappedType = rule.t
			if rule.src <= current.value && current.value < (rule.src+rule.length) {
				value := rule.dest + current.value - rule.src
				newSnapshots = append(newSnapshots, Snapshot{rule.t, value})
			}
		}
		if len(newSnapshots) == 0 {
			snapshots = append(snapshots, Snapshot{mappedType, current.value})
		} else {
			snapshots = append(snapshots, newSnapshots...)
		}
	}
	return minLocation, nil
}
