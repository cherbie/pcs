FILENAME = 'input.txt'


def parse_input():
    with open(FILENAME, 'r') as f:
        for line in f:
            for c in line.strip():
                yield c


def part1():
    tokens = parse_input()
    seen = [None] * 4
    for idx, c in enumerate(tokens):
        seen = seen[1:4] + [c]
        if idx > 3 and len(set(seen)) == 4:
            return idx + 1
        seen[3] = c
    return None

def part2():
    tokens = parse_input()
    seen = [None] * 14
    for idx, c in enumerate(tokens):
        seen = seen[1:14] + [c]
        if idx > 13 and len(set(seen)) == 14:
            return idx + 1
        seen[13] = c
    return None


if __name__ == '__main__':
    print(f'part 1 = {part1()}')
    print(f'part 2 = {part2()}')