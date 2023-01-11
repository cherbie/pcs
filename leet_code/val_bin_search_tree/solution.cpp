#include <bits/stdc++.h>

struct TreeNode
{
    long val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(long x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(long x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

constexpr bool isBSTUtil(const TreeNode *node, long min, long max);

/// entrypoint
constexpr bool isValidBST(TreeNode *node)
{
    return isBSTUtil(node, INT_MIN, INT_MAX);
}

constexpr bool isBSTUtil(const TreeNode *node, long min, long max)
{
    if (node == NULL)
        return true;

    if (node->val < min || node->val > max)
        return false;

    return isBSTUtil(node->left, min, node->val - 1) &&
           isBSTUtil(node->right, node->val + 1,
                     max);
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    isValidBST(nullptr);
#endif // ifdef DEBUG
}