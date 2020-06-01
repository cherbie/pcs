#include <bits/stdc++.h>
#include <stdint.h>
#include <string>

#define MAX 2500

using namespace std;

int main() {
  int t, n;
  string s;
  bitset<MAX> outside, polygon, match;
  
  //getline(cin, s);
  cin >> t;

  for(int i = 0; i < t; i++) { // each testcase
    cin >> n;
    polygon.reset();
    outside.reset();
    for(int j = 0; j < n; j++) { // each row
      cin >> s;
      for(int k = 0; k < n; k++) { // each column
        if(s[k] == '1')
          polygon.set((j*n)+k); // set the bit
        if(j == (n-1) || k == (n-1))
          outside.set((j*n)+k);
      }
    }
    match = (polygon >> n & polygon) | (polygon >> 1 & polygon) | (outside & polygon);
    if(match != polygon)
      cout << "NO" << endl;
    else
      cout << "YES" << endl;
  }
  return EXIT_SUCCESS;
}