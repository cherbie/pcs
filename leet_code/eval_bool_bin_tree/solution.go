package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func evaluateTree(root *TreeNode) bool {
	if isLeaf(root.Val) {
		return root.Val == TRUE_OP
	} else if operand := root.Val; operand == OR_OP {
		return evaluateTree(root.Left) || evaluateTree(root.Right)
	} else {
		lResult, rResult := evaluateTree(root.Left), evaluateTree(root.Right)
		return lResult && rResult
	}
}

const (
	FALSE_OP int = 00
	TRUE_OP  int = 01
	OR_OP    int = 02
)

func isLeaf(val int) bool {
	return val == FALSE_OP || val == TRUE_OP
}

func main() {
	// TODO: test case
}
