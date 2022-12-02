import enum

FILENAME = 'input.txt'

class Move(enum.Enum):
    Rock = 'r'
    Paper = 'p'
    Scizzor = 's'

class Outcome(enum.Enum):
    Lost = 'l'
    Draw = 'd'
    Win = 'w'

moveMapping = {
    'Z': Move.Scizzor,
    'X': Move.Rock,
    'Y': Move.Paper,
    'A': Move.Rock,
    'B': Move.Paper,
    'C': Move.Scizzor
}

outcomeMapping = {
    'Z': Outcome.Win,
    'X': Outcome.Lost,
    'Y': Outcome.Draw
}

pointsMapping = {
    Outcome.Draw: 3,
    Outcome.Lost: 0,
    Outcome.Win: 6,
    Move.Rock: 1,
    Move.Paper: 2,
    Move.Scizzor: 3
}

def calcGameMove(outcome: Outcome, opponentMove: Move) -> Move:
    if outcome == Outcome.Draw:
        return opponentMove
    elif outcome == Outcome.Win:
        if opponentMove == Move.Rock:
            return Move.Paper
        if opponentMove == Move.Paper:
            return Move.Scizzor
        if opponentMove == Move.Scizzor:
            return Move.Rock
    else:
        if opponentMove == Move.Rock:
            return Move.Scizzor
        if opponentMove == Move.Paper:
            return Move.Rock
        if opponentMove == Move.Scizzor:
            return Move.Paper

def calcGameOutcome(opponentMove: Move, ourMove: Move) -> Outcome:
    if opponentMove == ourMove:
        return Outcome.Draw
    if ((opponentMove == Move.Rock and ourMove == Move.Paper)
        or (opponentMove == Move.Paper and ourMove == Move.Scizzor)
        or (opponentMove == Move.Scizzor and ourMove == Move.Rock)):
        return Outcome.Win
    else:
        return Outcome.Lost

def getTotalGamePoints():
    total = 0
    with open(FILENAME, 'r') as f:
        for line in f:
            opponent, ours = line.split()
            oppMove = moveMapping[opponent]
            # ourMove = moveMapping[ours]
            gameOutcome = outcomeMapping[ours]
            # gameOutcome = calcGameOutcome(oppMove, ourMove)
            ourMove = calcGameMove(gameOutcome, oppMove)
            total += sum([pointsMapping[gameOutcome], pointsMapping[ourMove]])
    return total

if __name__ == '__main__':
    print(getTotalGamePoints())