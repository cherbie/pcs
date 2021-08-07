# Palindromic Number

> [Problem](https://www.codechef.com/problems/PALNUM)

## Description

You are given a string S consisting of N digits from 0 to 9. You want to obtain a palindrome from S using some operations.

There are M different types of operations you can make on S. Each operation is described by three integers X, Y and W. In this operation, if there is a digit equal to X in S, you can replace X with Y using W coins. For example, if X=4,Y=5,W=10 and S=1448, you make S equal to either 1458 or 1548 using 10 coins.

You can do the operations in any order. One type of operation can be done multiple times. You can use at most K
coins total in all operations. Among all the palindromes that can be obtained from S, output the lexicographically maximum palindrome.

If two strings A and B have the same length, we say that A is lexicographically larger than B if there exists an index `i` so that `A1=B1,A2=B2,…,Ai−1=Bi−1,Ai>Bi`.

Print −1 if it is impossible to obtain a palindrome from S using at most K coins.

## Input

- The first line contains an integer T, the number of test cases. Then the test cases follow.
- The first line of each test case contains three integers N, M, and K
  - The length of the string, the number of operation types, and the maximum number of coins to spend, respectively.
- The second line contains a string S of length N.
- Each of the next M lines contains three integers Xi, Yi and Wi - the parameters of the i-th type of operation.

## Output

For each test case, output the lexicographically maximum palindrome which can be obtained from the given string S using at most K coins. Print -1 if it is impossible to obtain a palindrome.

## Constraints

```
1≤T≤103
1≤N≤105
0≤M≤90
0≤K,Wi≤109
0≤Xi,Yi≤9, Xi≠Yi
The sum of N over all test cases does not exceed 106.
```

## Example

### Input

```
3
5 10 10
75643
0 1 1
1 2 1
2 3 1
3 4 1
4 5 1
5 6 1
6 7 1
7 8 1
8 9 1
9 0 1
4 5 1000000
1895
2 3 10
3 1 9
1 2 5
5 6 99
8 9 45
6 4 12
141746
1 5 3
5 7 2
7 9 10
6 1 5
```

### Ouput

```
95759
-1
147741
```
