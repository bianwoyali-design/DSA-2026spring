#include <iostream>
#include <vector>
using namespace std;

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        auto height = [&](this auto &&height, TreeNode *node)
        {
            if (node == nullptr)
                return 0;

            int leftheight = height(node->left);
            int rightheight = height(node->right);

            return max(leftheight, rightheight) + 1;
        };

        return height(root);
    }
};