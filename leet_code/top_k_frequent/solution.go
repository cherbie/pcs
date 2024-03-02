package main

import (
	"container/heap"
	"fmt"
	"sort"
)

func main() {
	fmt.Println("test case: ", []int{1, 1, 1, 2, 2, 3}, " | k = ", 2)
	fmt.Println("result: ", topKFrequent([]int{1, 1, 1, 2, 2, 3}, 2))
}

func topKFrequent(nums []int, k int) []int {
	sort.Ints(nums)

	queue := &PriorityQueue{}
	heap.Init(queue)

	count, prev := 0, nums[0]
	for _, number := range nums {
		if number != prev {
			heap.Push(queue, Item{id: prev, count: count})
			count, prev = 1, number
		} else {
			count++
		}
	}
	heap.Push(queue, Item{id: prev, count: count})

	results := make([]int, 0, k)
	for i := 0; i < k && queue.Len() > 0; i++ {
		item := heap.Pop(queue).(Item)
		results = append(results, item.id)
	}

	return results
}

type Item struct {
	id    int
	count int
}

type PriorityQueue []Item

func (pq PriorityQueue) Len() int { return len(pq) }

func (pq PriorityQueue) Less(i, j int) bool {
	// max sort
	return pq[i].count > pq[j].count
}

func (pq PriorityQueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
}

func (pq *PriorityQueue) Push(x any) {
	item := x.(Item)
	*pq = append(*pq, item)
}

func (pq *PriorityQueue) Pop() any {
	old := *pq
	n := len(old)
	item := old[n-1]
	*pq = old[0 : n-1]
	return item
}
