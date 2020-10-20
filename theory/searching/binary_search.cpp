#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int binary_search(vector<int>&, int&);

int main(int getc, char* argv[]) {
    int len;
    cin >> len;
    vector<int> a(len);

    for(vector<int>::iterator i = a.begin(); i < a.end(); i++)
        cin >> *i;
    
    int find;
    cin >> find;

    int index = binary_search(a, find);
    if (index < 0)
        cout << "Could not find element" << endl;
    else cout << "Found element {" << find << "} at sorted index: " << index << endl;

    return EXIT_SUCCESS;
}

int binary_search(vector<int> &a, int &element) {
    sort(a.begin(), a.end()); // sort vector
    
    int k = 0; // lower index bound
    int len = a.size();

    for (int b = len/2; b >= 1; b /= 2) { // b remains upper index bound
        while (k+b < len && a.at(k+b) <= element) k += b;
    }

    if (a.at(k) == element)
        return k;
    return -1;
}
