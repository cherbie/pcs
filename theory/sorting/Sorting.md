# Sorting

Sorting is a fundemental algorithm design problem. Many efficient algorithms usin sorting as a subroutine, because it is often easier to process data if the elements are in sorted order.

There are many algorithms for sorting. The effiecient general sorting algorithms work in `O(nlogn)` time, and many algorithms that use sorting as a subroutine also have this time complexity.

## Algorithms

- Bubble Sort
- Merge Sort
- Quick Sort
- Counting Sort

### Bubble Sort

Elements "bubble" up in the array according to their values

Bubble sort consists of _n_ rounds. On each round, the algorithm iterates through the elements of the array. Whenever two consecutive elements are found that are not in correct order, the algorithm swaps them.

See [bubble_sort.cpp](./bubble_sort.cpp) as an example implementation.

#### Complexity Analysis

_Bubble sort_ is an example of a sorting algorithm that always swaps consecutive elements in the array. The complexity of such an algorithm is always at least `O(n^2)`, because in the worst case, `O(n^2)` swaps are requied for sorting the array.

See [inversion algorithm analysis]().

### Merge Sort

This algorithm is based on recursion and is not limited by swapping consecutive elements.

See [merge_sort.cpp](./merge_sort.cpp) as an example implementation.

#### Algorithm

_Merge sort_ sorts the subarray `array[a...b]` as follows:

1. If a = b, do not do anything, because the subarray is already sorted.
2. Calculate the position of the middle element: `k = [(a+b)/2]`
3. Recursively sort the subarray: `array[a...k]`
4. Recursively sort the subarray: `array[k+1...b]`
5. _Merge_ the sorted subarrays `array[a...k]` and `array[k+1...b]` into a sorted subarray `array[a...b]`.

#### Complexity Analysis

_Merge sort_ is an efficient algorithm, because it halves the size of the subarray at each step. The recursion consists of `O(logn)` levels, and processing each level takes `O(n)` time. Merging the subarrays `array[a...k]` and `array[k+1...b]` is possible in linear time, because they are already sorted.

Total time complexity is hence: `O(logn) * O(n) = O(nlogn)`

#### Example

Various _"levels"_ of the recursion

1. `[1, 3, 6, 2, 8, 2, 5, 9]`
2. `[1, 3, 6, 2]` - `[8, 2, 5, 9]`
3. `[1, 3]` - `[6, 2]` - `[8, 2]` - `[5, 9]`

### Quick Sort

A divide and conquer algorithm that works by selecting a _'pivot'_ from the array and partitioning the other elements into two sub-arrays, according to whether they are less than or greater than the _'pivot'_. The sub-arrays are then sorted recursively which can be done _in-place_ requiring a small amount of additional memory.
