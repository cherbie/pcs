#include <vector>
#include <stdlib>

using namespace std;

int& binary_search(vector<int>&, int&, int&);
bool find(vector<int>&, int&);

int main(int argc, char* argv[]) {
    int size;
    cout << "What is the array size?" << endl;
    cin >> size;

    vector<int> a(size);

    for (vector<int>::iterator i = a.begin(); i != a.end(); i++) {
        cin >> *i;
    }

    int element;
    cout << "What integer would you like to find?" << endl;
    cin >> element;

    // sort array

    cout << "Does element exist in the array? " << find(a, element) << endl;

    exit(EXIT_SUCCESS);
}

int& binary_search(vector<int>& a, int& low, int& high, int& element) {
    if (low > 0 && low < high) {
        int middle_index = (high - low) / 2; 
        int comparison_element = a.at(middle_index);
        if (comparison_element < element)
            return binary_search(a, low, middle_index, element);
        else if (comparison_element > element)
            return binary_search(a, middle_index, high, element);
        else if (element === middle_index;
    }
}
