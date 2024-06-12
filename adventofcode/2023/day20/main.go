package main

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"regexp"
	"slices"
	"strings"
)

func main() {
	if err := part1(); err != nil {
		panic(err)
	}
}

var (
	expressionRegex = regexp.MustCompile(`((%|&)?(\w+)) -> (.+)`)
)

const (
	UNDEFINED_TYPE   = '\000'
	FLIP_FLOP_TYPE   = '%'
	CONJUNCTION_TYPE = '&'

	BROADCASTER_SYMBOL = "broadcaster"
	FLIP_FLOP_SYMBOL   = "%"
	CONJUNCTION_SYMBOL = "&"
)

type Expression struct {
	t     rune
	left  string
	right []string
}

func parseExpressions() (expressions []Expression, err error) {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Split(bufio.ScanLines)

	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			continue
		}
		if matches := expressionRegex.FindAllStringSubmatch(line, -1); matches == nil {
			return nil, errors.New("error: could not match seeds regexp")
		} else {
			expression := Expression{}
			expression.left = strings.TrimSpace(matches[0][3])
			if len(matches[0][2]) == 1 {
				expression.t = rune(matches[0][2][0])
			} else {
				expression.t = UNDEFINED_TYPE
			}
			expression.right = append(expression.right, strings.Split(strings.Map(func(r rune) rune {
				if r == ' ' {
					return -1
				} else {
					return r
				}
			}, matches[0][4]), ",")...)
			expressions = append(expressions, expression)
		}
	}

	if err := scanner.Err(); err != nil {
		return nil, err
	}

	return expressions, nil
}

func part1() error {
	expressions, err := parseExpressions()
	if err != nil {
		return err
	}

	machine, err := initMachine(expressions)
	if err != nil {
		return err
	}

	lowCount := uint(0)
	highCount := uint(0)
	for i := 0; i < 1000; i++ {
		low, high := machine.Broadcast(func(pulse *Pulse) {})
		lowCount += low
		highCount += high
	}

	fmt.Println("low-high product: ", lowCount*highCount)

	return nil
}

// func part2() error {
// 	expressions, err := parseExpressions()
// 	if err != nil {
// 		return err
// 	}

// 	machine, err := initMachine(expressions)
// 	if err != nil {
// 		return err
// 	}

// 	count := 0
// 	seen := false
// 	for !seen {
// 		count++
// 		machine.Broadcast(func(pulse *Pulse) {
// 			if pulse.receiver.name == "rx" && !pulse.voltage {
// 				seen = true
// 			}
// 		})
// 	}

// 	fmt.Println("Cycle rx: ", count)

// 	return nil
// }

type Ref struct {
	name    string
	t       rune
	inputs  []string
	outputs []string
	store   StateStore
}

type RefMap = map[string](*Ref)

type StateMachine struct {
	lookup RefMap
}

type StateStore struct {
	state []uint64
}

func makeStateStore(n int) StateStore {
	return StateStore{
		make([]uint64, (n/64)+1),
	}
}

func initMachine(expressions []Expression) (machine StateMachine, err error) {
	idIdx := uint(0)
	lookup := make(RefMap)
	for _, expression := range expressions {
		if link, exists := lookup[expression.left]; !exists {
			lookup[expression.left] = &Ref{expression.left, expression.t, nil, expression.right, makeStateStore(1)}
			idIdx++
		} else {
			link.t = expression.t
			link.outputs = append(link.outputs, expression.right...)
		}
		for _, name := range expression.right {
			if link, exists := lookup[name]; !exists {
				lookup[name] = &Ref{name, expression.t, []string{expression.left}, nil, makeStateStore(1)}
				idIdx++
			} else {
				link.inputs = append(link.inputs, expression.left)
			}
		}
	}

	return StateMachine{lookup}, nil
}

func conjunction(input bool, receiver *Ref, sender *Ref) bool {
	idx := slices.Index(receiver.inputs, sender.name)
	if idx < 0 {
		panic("could not find index")
	} else if !input {
		receiver.store.Clear(uint(idx))
		return true
	} else {
		receiver.store.Set(uint(idx))
	}

	allHigh := true
	for idx := range receiver.inputs {
		if !receiver.store.Get(uint(idx)) {
			allHigh = false
			break
		}
	}
	return !allHigh
}

func flipFlop(input bool, receiver *Ref) bool {
	if !input {
		currentState := receiver.store.Get(0)
		if currentState {
			receiver.store.Clear(0)
		} else {
			receiver.store.Set(0)
		}
		return !currentState
	}
	panic("ignore")
}

type Pulse struct {
	id       string
	voltage  bool
	sender   *Ref
	receiver *Ref
}

func (machine *StateMachine) Broadcast(callback func(pulse *Pulse)) (low uint, high uint) {
	broadCastRef := machine.lookup[BROADCASTER_SYMBOL]

	updates := make([]Pulse, 0)

	low = 1
	high = 0

	for idx, broadcastName := range broadCastRef.outputs {
		nextRef := machine.lookup[broadcastName]
		pulse := Pulse{fmt.Sprint(idx), false, broadCastRef, nextRef}
		updates = append(updates, pulse)
	}

	for len(updates) > 0 {
		pulse := updates[0]
		updates = updates[1:]

		if pulse.receiver == nil {
			continue
		}

		callback(&pulse)

		output := pulse.voltage
		switch output {
		case false:
			low++
		case true:
			high++
		}

		switch pulse.receiver.t {
		case FLIP_FLOP_TYPE:
			if pulse.voltage {
				continue
			}
			output = flipFlop(pulse.voltage, pulse.receiver)
		case CONJUNCTION_TYPE:
			output = conjunction(pulse.voltage, pulse.receiver, pulse.sender)
		}

		for _, refName := range pulse.receiver.outputs {
			linkedPulse := pulse
			linkedPulse.voltage = output
			linkedPulse.receiver = machine.lookup[refName]
			linkedPulse.sender = pulse.receiver
			updates = append(updates, linkedPulse)
		}
	}
	return low, high
}

func (store *StateStore) Set(idx uint) {
	arrIdx := idx / 64
	bitIdx := idx % 64
	store.state[arrIdx] = store.state[arrIdx] | (1 << bitIdx)
}

func (store *StateStore) Clear(idx uint) {
	arrIdx := idx / 64
	bitIdx := idx % 64
	store.state[arrIdx] = store.state[arrIdx] & (^(1 << bitIdx))
}

func (store *StateStore) Get(idx uint) bool {
	arrIdx := idx / 64
	bitIdx := idx % 64
	return store.state[arrIdx]&(1<<bitIdx) != 0
}

func (store *StateStore) Print() {
	fmt.Printf("%b\n", store.state[0])
}
