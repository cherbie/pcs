FILENAME = 'calories.txt'

def find_elf_with_most_calories():
    maxCalories = 0
    with open(FILENAME, 'r') as f:
        elfCalories = 0
        for line in f:
            line = line.strip('\n').strip()
            if len(line) == 0:
                maxCalories = max(elfCalories, maxCalories)
                elfCalories = 0
                continue
            elfCalories += int(line)
    return maxCalories


def find_top_three_elf_calories():
    calorieLeaderboard = [0, 0, 0]
    with open(FILENAME, 'r') as f:
        elfCalories = 0
        for line in f:
            line = line.strip('\n').strip()
            if len(line) == 0:
                for idx, count in enumerate(calorieLeaderboard):
                    if elfCalories >= count:
                        print(f'{idx}:{count}:{elfCalories}:{calorieLeaderboard}')
                        calorieLeaderboard = calorieLeaderboard[0:idx] + [elfCalories] + calorieLeaderboard[idx:2]
                        print(f'slice ({elfCalories}) | leaderboard ({calorieLeaderboard})')
                        break
                elfCalories = 0
                continue
            elfCalories += int(line)
    return sum(calorieLeaderboard)

if __name__ == "__main__":
    print(f'Max number of Elf calories: {find_elf_with_most_calories()}')
    print(f'Find top three Elf calories: {find_top_three_elf_calories()}')


