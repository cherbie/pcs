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
    
    int t = 0, v = a.size() - 1;

    while( t < v ) {
        int k = (t + v) / 2;
        if (a.at(k) == element)
            return k;
        else if (a.at(k) > element)
            v = k - 1;
        else t = k + 1; 
    }

    return -1;
}
