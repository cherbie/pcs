from pprint import pprint

FILENAME = 'input.txt'

def parseStacks(tokens):
    stacks = [[]] * 9
    for arr in tokens[::-1]:
        if len(stacks) == 0:
            stacks = [[]] * 10

        for idx, e in enumerate(arr):
            e = e[1]
            if len(e.strip()) == 0:
                e = ''
            if len(stacks[idx]) == 0:
                stacks[idx] = []
            stacks[idx] += e
    return stacks

def read_input():
    stacks = []
    operations = []
    with open(FILENAME, 'r') as f:
        seenSpacer = False
        tokens = []
        for line in f:
            line = line.strip()
            if len(line.strip(' ')) == 0 and not seenSpacer:
                seenSpacer = True
                stacks = parseStacks(tokens[0:len(tokens)-1])
            elif not seenSpacer:
                tokens.append([line[x:x+3] for x in range(0,len(line),4)])
            else:
                operations.append(list(map(lambda x: int(x), line.strip().split(' ')[1::2])))
        pprint(stacks)
    return stacks, operations


def part1():
    stacks, operations = read_input()
    for move, fromIdx, toIdx in operations:
        fromStack = stacks[fromIdx-1]
        toStack = stacks[toIdx-1] + fromStack[len(fromStack)-move:len(fromStack)][::-1]
        stacks[fromIdx-1] = fromStack[:len(fromStack) - move]
        stacks[toIdx-1] = toStack
    pprint(stacks)
    return ''.join([x[-1] for x in stacks])


def part2():
    stacks, operations = read_input()
    for move, fromIdx, toIdx in operations:
        fromStack = stacks[fromIdx-1]
        toStack = stacks[toIdx-1] + fromStack[len(fromStack)-move:len(fromStack)]
        stacks[fromIdx-1] = fromStack[:len(fromStack) - move]
        stacks[toIdx-1] = toStack
    pprint(stacks)
    return ''.join([x[-1] for x in stacks])


if __name__ == '__main__':
    print(f'part 1 = {part1()}')
    print(f'part 2 = {part2()}')