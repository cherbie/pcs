# Number Game Problem
> __Problem:__ _[1370C - Number Game](https://codeforces.com/problemset/problem/1370/C)_

## Description

Ashishgup and FastestFinger play a game.

They start with a number n and play in turns. In each turn, a player can make any one of the following moves:

 1. Divide n by any of its odd divisors greater than 1.
 2. Subtract 1 from n if n is greater than 1.

Divisors of a number include the number itself.

*The player who is unable to make a move loses the game.*

Ashishgup moves first. Determine the winner of the game if both of them play optimally.

### Input

The first line contains a single integer t `(1 ≤ t ≤ 100)` — the number of test cases. The description of the test cases follows.

The only line of each test case contains a single integer  — n `(1 ≤ n ≤ 109)`.

### Output

For each test case, print "Ashishgup" if he wins, and "FastestFinger" otherwise (without quotes).

## Example

__INPUT__

```
7
1
2
3
4
5
6
12
```

__OUTPUT__

```
FastestFinger
Ashishgup
Ashishgup
FastestFinger
Ashishgup
FastestFinger
Ashishgup
```

## Notes:
 
 - Odd input number -> Ashishgup always wins
 - Even input number -> divide such that the resulting number is always even.
   - Need to determine how many times the even number can be divided before it approaches 1  or an
     odd number.
