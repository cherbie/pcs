#include <vector>
#include <iostream>
#include <cstdlib>

void bubble_sort(std::vector<int>&);

void print_usage()
{
	std::cout << "Usage:\n"
		  << "./bubble\n"
		  << "n\n"
		  << "e1 [e2 e3 [...e4]]"
		  << std::endl;
}

int main(int argc, char *argv[]) {
    print_usage();
    int n; // number of elements in array
    std::cin >> n;
    std::vector<int> a(n);

    // initialize unsorted array values
	for (std::vector<int>::iterator iter = a.begin(); iter != a.end(); iter++) {
		std::cin >> *iter;
	}

    bubble_sort(a);

    // print sorted array contents
    for (auto iter = a.begin(); iter != a.end(); iter++) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    
    std::exit(EXIT_SUCCESS);
}

// Sort the array in ascending order
void bubble_sort(std::vector<int>& a) {
    const std::size_t size = a.size();
    for (std::size_t i = 0; i < size; i++) {
        auto iter_end = a.end();
        for (auto iter = a.begin(); iter != iter_end-1; iter++) {
            if (*iter > iter[1]) {
                // perform swap
                int temp = iter[1];
                iter[1] = *iter;
                *iter = temp;
            }
        }
    }
}
