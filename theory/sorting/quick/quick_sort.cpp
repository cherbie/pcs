#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

void quick_sort(vector<int>&, const int, const int);
const int partition(vector<int>&, const int, const int);
void swap(int*, int*);

int main(int argc, char* argv[]) {
    int n;
    cin >> n;
    vector<int> a(n);

    for (vector<int>::iterator i = a.begin(); i != a.end(); i++)
        cin >> *i;
    
    quick_sort(a, 0, (int) a.size() - 1);

    for (vector<int>::iterator i = a.begin(); i != a.end(); i++)
        cout << *i << " ";
    cout << endl;

    exit(EXIT_SUCCESS);
}

void quick_sort(vector<int> &a, const int low, const int high) {
    if (low < high) {
        const int p = partition(a, low, high); // pivot index
        quick_sort(a, low, p - 1);
        quick_sort(a, p + 1, high);
    }
}

const int partition(vector<int> &a, const int low, const int high) {
    const int pivot = a.at(high);
    int p = low; // index of last element seen that is less than the pivot

    for (int i = low; i < high; i++) {
       if (a.at(i) < pivot) {       
            swap(&a.at(p), &a.at(i));
            p++;
       }
    }

    swap(&a.at(p), &a.at(high)); // place pivot in correct spot
    return p;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
