#include <bits/stdc++.h>
#include <stdint.h>

using namespace std;

bitset<50>* do_something(int&, int&, int&, int&);
void print(bitset<50>*, int&, int&);


int main() {
  int num_cases, n, m, a, b;

  cin >> num_cases; // fetch number of test cases

  for (int i = 0; i < num_cases; i++) {
    cin >> n >> m >> a >> b;
    bitset<50>* rows;
    if ((rows = do_something(n, m, a, b)) != NULL) {
      cout << "YES" << endl;
      print(rows, n, m);
      free(rows);
    } else {
      cout << "NO" << endl;
    }
  }

  return EXIT_SUCCESS;
}

bitset<50>* do_something(int& n, int& m, int& a, int& b) {
  if((a*n) != (b*m)) // not possible
    return NULL;
  
  bitset<50>* rows = (bitset<50>*) calloc(n, sizeof(bitset<50>));
  if (rows == NULL) return NULL;

  int d = 0; // magic number
  for(int i = 1; i < m; i++) {
    if((i*n)%m == 0) {
      d = i;
      break;
    }
  }

  for(int row = 0; row < n; row++) {
    rows[row] = bitset<50>(0);
    for(int col = 0; col < m; col++) {
      //previous shifted column
      int pcol = (col + (m - d))%m; // previous bit index to look at
      if(row == 0 && col < a)
        rows[row].set(col);
      else if(row != 0 && rows[row-1][pcol] == 1)
        rows[row].set(col);
    }
  }
  return rows;
}

void print(bitset<50>* rows, int& n, int& m) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++)
      cout << rows[i][j]; // print 0 or 1;
    cout << endl;
  } 
}