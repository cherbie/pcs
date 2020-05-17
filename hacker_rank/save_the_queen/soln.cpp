#include <bits/stdc++.h>

using namespace std;

void split(const string*, vector<long>*, const int&);

int main() {
  int n; // number of posters
  long h; // person's reach
  vector<long> wp;
  vector<long> lengths;
  string line_tmp; // temporary storage of input

  getline(cin, line_tmp);
  
  // process first line
  char* cp = (char*) line_tmp.c_str();
  if(sscanf(cp, "%i %li", &n, &h) < 0) {
    cerr << "Error" << endl;
    return EXIT_FAILURE;
  }

  // Poster Wall Points
  getline(cin, line_tmp);
  split(&line_tmp, &wp, n);

  // Poster lengths
  getline(cin, line_tmp);
  split(&line_tmp, &lengths, n);

  // Print result
  cout << "result!" << endl;

  return EXIT_SUCCESS;
}


void split(const string *str, vector<long> *wp, const int& n) {
  size_t start = 0, end = 0;

  (*wp).assign(n, 0); // initialise wall points vector

  for(int i = 0; i < n; i++) {
    end = (*str).find(" ", start);
    long val = stol((*str).substr(start, end)); // fetch string number representation and convert to number
    (*wp)[i] = val;

    if(end == string::npos) // end of input line
      break;

    start = end + 1; // move start to character following space
  }
}

