package main

import "fmt"

type Trie struct {
	root *Node
}

type Node struct {
	children []*Node
	is_end   bool
}

func newEmptyNode() *Node {
	children := make([]*Node, 26)

	return &Node{
		children: children,
		is_end:   false,
	}
}

func getAlphabetIndex(c rune) int {
	return int(c) - int(rune('a'))
}

func Constructor() Trie {
	root := newEmptyNode()
	return Trie{root}
}

func (instance *Trie) Insert(word string) {
	var currentNode *Node = instance.root
	for _, c := range word {
		alphaIdx := getAlphabetIndex(c)
		if nextNode := currentNode.children[alphaIdx]; nextNode == nil {
			nextNode = newEmptyNode()
			currentNode.children[alphaIdx] = nextNode
			currentNode = nextNode
		} else {
			currentNode = nextNode
		}
	}
	currentNode.is_end = true
}

func (instance *Trie) Search(word string) bool {
	var currentNode *Node = instance.root
	for _, c := range word {
		alphaIdx := getAlphabetIndex(c)
		if nextNode := currentNode.children[alphaIdx]; nextNode == nil {
			return false
		} else {
			currentNode = nextNode
		}
	}
	return currentNode.is_end
}

func (instance *Trie) StartsWith(prefix string) bool {
	var currentNode *Node = instance.root
	for _, c := range prefix {
		alphaIdx := getAlphabetIndex(c)
		if nextNode := currentNode.children[alphaIdx]; nextNode == nil {
			return false
		} else {
			currentNode = nextNode
		}
	}
	return true
}

func main() {
	trie := Constructor()
	trie.Insert("apple")
	fmt.Println("Insert: {}", "apple")
	fmt.Println("Search: {} - Result: {}", "apple", trie.Search("apple"))
	fmt.Println("Search: {} - Result: {}", "app", trie.Search("app"))
	fmt.Println("StartsWith: {} - Result: {}", "app", trie.StartsWith("app"))
	fmt.Println("StartsWith: {} - Result: {}", "deadbeef", trie.StartsWith("deadbeef"))
}

/**
 * Your Trie object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Insert(word);
 * param_2 := obj.Search(word);
 * param_3 := obj.StartsWith(prefix);
 */
