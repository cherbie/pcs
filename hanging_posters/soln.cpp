#include <vector>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;

void split(const string*, vector<float>*, const int&);
float solve(vector<float>*, vector<float>*, int&, long&);

int main() {
  int n; // number of posters
  long h; // person's reach
  vector<float> wp;
  vector<float> lengths;
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
  printf("%.0f\n", solve(&wp, &lengths, n, h));

  return EXIT_SUCCESS;
}


void split(const string *str, vector<float> *wp, const int& n) {
  size_t start = 0, end = 0;

  (*wp) = vector<float>( (size_t) n, 0); // initialise wall points vector

  for(int i = 0; i < n; i++) {
    end = (*str).find(" ", start);
    float val = stof((*str).substr(start, end)); // fetch string number representation and convert to number
    (*wp)[i] = val;

    if(end == string::npos) // end of input line
      break;

    start = end + 1; // move start to character following space
  }
}

/**
 * Find the minimum ladder height required to hang all the posters.
 */
float solve(vector<float>* wp, vector<float>* l, int& n, long& h) {
  float mlh = 0, tmp = 0; // minimum ladder height
  for(int i = 0; i < n; i++) {
    tmp = (*wp)[i] - (0.25 * (*l)[i]) - h;
    mlh = tmp > mlh ? tmp : mlh; // largest value
  }
  return ceil(mlh);
}