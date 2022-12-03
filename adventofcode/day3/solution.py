import math

FILENAME = 'input.txt'

def part1():
    sumPriorities = 0
    with open(FILENAME, 'r') as f:
        for line in f:
            mid = math.floor(len(line) / 2)
            c1, c2 = (line[0:mid], line[mid:len(line)])
            sc1 = set([c for c in c1])
            sc2 = set([c for c in c2])
            common = sc1.intersection(sc2)
            for c in common:
                points: int
                if c <= 'z' and c >= 'a':
                    points = ord(c) - ord('a') + 1
                else:
                    points = ord(c) - ord('A') + 27
                sumPriorities += points
    return sumPriorities


def part2():
    sumPriorities = 0
    with open(FILENAME, 'r') as f:
        count = 0
        ruckSackValues = [[{}] * 3]
        for line in f:
            line = line.strip()
            idx = math.floor(count / 3)
            itemIdx = count % 3
            if itemIdx == 0:
                ruckSackValues += [[{}] * 3]
            ruckSackValues[idx][itemIdx] = [c for c in line]
            count += 1

        for s1, s2, s3 in ruckSackValues:
            c = list(set(s1).intersection(set(s2)).intersection(set(s3)))
            if len(c) == 0:
                continue # end of file bad input
            c = c[0]
            points: int
            if c <= 'z' and c >= 'a':
                points = ord(c) - ord('a') + 1
            else:
                points = ord(c) - ord('A') + 27
            sumPriorities += points
    return sumPriorities

if __name__ == '__main__':
    print(f'part 1 = {part1()}')
    print(f'part 2 = {part2()}')
