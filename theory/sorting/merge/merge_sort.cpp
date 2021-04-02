#include <cstdlib>
#include <vector>
#include <iostream>

void merge_sort(std::vector<int>&);
std::vector<int> merge(std::vector<int>&, std::vector<int>&);

int main(int argc, char* argv[]) {
	int n;
	std::cin >> n;
	std::vector<int> a(n);

	// initialize unsorted array values
	for (std::vector<int>::iterator iter = a.begin(); iter != a.end(); iter++) {
		std::cin >> *iter;
	}

	merge_sort(a); // perform merge
	
	// print sortd array
	for (std::vector<int>::iterator iter = a.begin(); iter != a.end(); iter++) {
		std::cout << *iter << " ";
	}
	std::cout << std::endl;

	std::exit(EXIT_SUCCESS);
}

void merge_sort(std::vector<int> &a) {
	const size_t size = a.size();
	if (size > 1) {
		const size_t mid_point = size / 2;
		std::vector<int> left(a.begin(), a.begin() + mid_point);
		std::vector<int> right(a.begin() + mid_point, a.end());
		// recursion
		merge_sort(left);
		merge_sort(right);
		// merge left and right
		a = merge(left, right);
	}
}

std::vector<int> merge(std::vector<int> &l, std::vector<int> &r) {
	std::vector<int> merged (l.size() + r.size());
	std::vector<int>::iterator ileft = l.begin(); // left iterator
	std::vector<int>::iterator iright = r.begin(); // right iterator
	for (std::vector<int>::iterator i = merged.begin(); i != merged.end(); i++) {
		if (*ileft < *iright && ileft != l.end()) {
			*i = *ileft;
			ileft++;
		} else if (iright != r.end()) {
			*i = *iright;
			iright++;
		} else {
			*i = *ileft;
			ileft++;
		}
	}
	return merged;
}