# A/B Matrix (1360G)

You are given four positive integers 𝑛, 𝑚, 𝑎, 𝑏 (1≤𝑏≤𝑛≤50; 1≤𝑎≤𝑚≤50). Find any such rectangular matrix of size 𝑛×𝑚

that satisfies all of the following conditions:

 - each row of the matrix contains exactly 𝑎 ones;
 - each column of the matrix contains exactly 𝑏 ones;
 - all other elements are zeros. 

If the desired matrix does not exist, indicate this.

For example, for 𝑛=3, 𝑚=6, 𝑎=2, 𝑏=1, there exists a matrix satisfying the conditions above:

0 1 0 0 0 1

1 0 0 1 0 0

0 0 1 0 1 0

## Input

The first line contains an integer 𝑡(1≤𝑡≤1000) — the number of test cases. Then _t_test cases follow.

Each test case is described by four positive integers 𝑛
, 𝑚, 𝑎, 𝑏 (1≤𝑏≤𝑛≤50; 1≤𝑎≤𝑚≤50), where 𝑛 and 𝑚 are the sizes of the matrix, and 𝑎 and 𝑏

are the number of ones for rows and columns, respectively.

## Output

For each test case print:
 - `YES` (without quotes) and the required matrix (if there are several answers, print any) if it exists, or
 - `NO` (without quotes) if it does not exist. 

To print the matrix 𝑛×𝑚, print 𝑛 rows, each of which consists of 𝑚 numbers 0 or 1 describing a row of the matrix. Numbers must be printed without spaces.
