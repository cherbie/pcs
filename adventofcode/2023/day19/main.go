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
	if err := part1(); err != nil {
		panic(err)
	}
}

var (
	ruleSetNameRegex = regexp.MustCompile(`(\w+){(.+)}`)
	ruleSetRegex     = regexp.MustCompile(`(\w+)(<|>)(\d+):(\w+)`)
	stateRegex       = regexp.MustCompile(`x=(\d+),m=(\d+),a=(\d+),s=(\d+)`)
)

const (
	OUTCOME_ACCEPTED = "A"
	OUTCOME_REJECTED = "R"
	START_WORKFLOW   = "in"
)

type RuleSet struct {
	result    string // use as switch on outcome
	operation string
	leftTerm  string
	rightTerm int
}
type Part struct {
	x int
	m int
	a int
	s int
}

type Workflows = map[string][]RuleSet

func readInput() (workflows Workflows, parts []Part, err error) {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Split(bufio.ScanLines)

	workflows = make(Workflows)

	// determine worflows
	for scanner.Scan() {
		line := scanner.Text()
		if len(line) == 0 {
			break
		}

		if matches := ruleSetNameRegex.FindAllStringSubmatch(line, -1); matches == nil {
			return nil, nil, errors.New("error: could not match ruleset name regexp")
		} else {
			ruleSetId := matches[0][1]
			ruleSetArrToken := matches[0][2]

			for _, ruleSetToken := range strings.Split(ruleSetArrToken, ",") {
				rule := RuleSet{}
				if ruleSetMatches := ruleSetRegex.FindAllStringSubmatch(ruleSetToken, -1); ruleSetMatches == nil {
					// "A" or "R"
					rule.result = ruleSetToken
				} else {
					rule.leftTerm = ruleSetMatches[0][1]
					rule.operation = ruleSetMatches[0][2]
					rule.result = ruleSetMatches[0][4]

					if rightTermValue, err := strconv.Atoi(ruleSetMatches[0][3]); err != nil {
						return nil, nil, err
					} else {
						rule.rightTerm = rightTermValue
					}
				}
				workflows[ruleSetId] = append(workflows[ruleSetId], rule)
			}
		}
	}

	for scanner.Scan() {
		line := scanner.Text()

		if matches := stateRegex.FindAllStringSubmatch(line, -1); matches == nil {
			return nil, nil, errors.New("error: could not match ruleset name regexp")
		} else {
			part := Part{}
			part.x, _ = strconv.Atoi(matches[0][1])
			part.m, _ = strconv.Atoi(matches[0][2])
			part.a, _ = strconv.Atoi(matches[0][3])
			part.s, _ = strconv.Atoi(matches[0][4])

			if err != nil {
				return nil, nil, err
			}

			parts = append(parts, part)
		}
	}

	if err := scanner.Err(); err != nil {
		return nil, nil, err
	}

	return workflows, parts, nil
}

func determineOutcome(part Part, workflows Workflows) string {
	start := workflows[START_WORKFLOW]

	workflow := make([]RuleSet, len(start))
	copy(workflow, start)

	for len(workflow) > 0 {
		rule := workflow[0]
		// fmt.Println("rule: ", rule, " workflow", workflow, " part: ", part)
		nextWorkflowId := ""
		if rule.operation == ">" {
			switch rule.leftTerm {
			case "x":
				if part.x > rule.rightTerm {
					nextWorkflowId = rule.result
				} else {
					workflow = workflow[1:]
					continue
				}
			case "m":
				if part.m > rule.rightTerm {
					nextWorkflowId = rule.result
				} else {
					workflow = workflow[1:]
					continue
				}
			case "a":
				if part.a > rule.rightTerm {
					nextWorkflowId = rule.result
				} else {
					workflow = workflow[1:]
					continue
				}
			case "s":
				if part.s > rule.rightTerm {
					nextWorkflowId = rule.result
				} else {
					workflow = workflow[1:]
					continue
				}
			}
		} else if rule.operation == "<" {
			switch rule.leftTerm {
			case "x":
				if part.x < rule.rightTerm {
					nextWorkflowId = rule.result
				} else {
					workflow = workflow[1:]
					continue
				}
			case "m":
				if part.m < rule.rightTerm {
					nextWorkflowId = rule.result
				} else {
					workflow = workflow[1:]
					continue
				}
			case "a":
				if part.a < rule.rightTerm {
					nextWorkflowId = rule.result
				} else {
					workflow = workflow[1:]
					continue
				}
			case "s":
				if part.s < rule.rightTerm {
					nextWorkflowId = rule.result
				} else {
					workflow = workflow[1:]
					continue
				}
			}
		} else if rule.operation == "" {
			nextWorkflowId = rule.result
		} else {
			panic("rule set operation not recognised")
		}

		if nextWorkflowId == OUTCOME_ACCEPTED || nextWorkflowId == OUTCOME_REJECTED {
			return nextWorkflowId
		} else {
			workflow = workflows[nextWorkflowId]
		}
	}
	panic("never to reach here")
}

func part1() error {
	workflows, parts, err := readInput()
	if err != nil {
		return err
	}

	sumOfRatings := int64(0)
	for _, part := range parts {
		switch determineOutcome(part, workflows) {
		case OUTCOME_ACCEPTED:
			{
				fmt.Println("ACCEPTED:", part)
				sumOfRatings += int64(part.x) + int64(part.m) + int64(part.a) + int64(part.s)
			}
		}
	}

	fmt.Println("Sum of part ratings: ", sumOfRatings)
	return nil
}
