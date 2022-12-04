FILENAME = 'input.txt'

def read_input():
    parsedInput = []
    with open(FILENAME, 'r') as f:
        for line in f:
            pair1_str, pair2_str = line.strip().split(',')
            minMax1 = list(map(lambda r: int(r), pair1_str.split('-')))
            minMax2 = list(map(lambda r: int(r), pair2_str.split('-')))
            parsedInput.append([minMax1, minMax2])
    return parsedInput

def part1(): 
    no = 0
    schedules = read_input()
    for schedule_a, schedule_b in schedules:
        set_a = set([x for x in range(schedule_a[0], schedule_a[1]+1)])
        set_b = set([x for x in range(schedule_b[0], schedule_b[1]+1)])
        if set_a <= set_b or set_b <= set_a:
            # print(f'{schedule_a}, {schedule_b}')
            no += 1
    return no

def part2(): 
    no = 0
    schedules = read_input()
    for schedule_a, schedule_b in schedules:
        set_a = set([x for x in range(schedule_a[0], schedule_a[1]+1)])
        set_b = set([x for x in range(schedule_b[0], schedule_b[1]+1)])
        if len(set_a & set_b) > 0:
            # print(f'{schedule_a}, {schedule_b}')
            no += 1
    return no

if __name__ == '__main__':
    print(f'part 1 = {part1()}')
    print(f'part 2 = {part2()}')
