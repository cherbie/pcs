package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func postorderTraversal(root *TreeNode) []int {
	if root == nil {
		return []int{}
	}

	stack := make([](*TreeNode), 0, 100)
	nodeMap := make(map[*TreeNode]bool)
	result := make([]int, 0, 100)

	stack = append(stack, root)
	for len(stack) > 0 {
		node := stack[len(stack)-1]
		if _, seen := nodeMap[node]; !seen {
			nodeMap[node] = true
			if node.Left != nil {
				stack = append(stack, node.Left)
			}
			if node.Right != nil {
				stack = append(stack, node.Right)
			}
			continue
		} else {
			result = append(result, node.Val)
		}
		stack = stack[0 : len(stack)-1]
	}

	return result
}

func main() {
	postorderTraversal(nil)
}
