#include <iostream>
#include <vector>
using namespace std;

class Solution
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

private:
    TreeNode *root;

    template <typename T>
    auto height(T &node)
    {
        if (node == nullptr)
            return 0;

        int leftheight = height(node->left);
        int rightheight = height(node->right);

        return max(leftheight, rightheight) + 1;
    }

public:
    auto build_tree(vector<pair<int, int>> nodes)
    {
        int n = nodes.size();
        vector<TreeNode *> tree_nodes(n);

        for (int i = 1; i < n; ++i)
            tree_nodes[i] = new TreeNode(i);

        for (int i = 1; i < n; ++i)
        {
            auto [left, right] = nodes[i];
            if (left != -1)
                tree_nodes[i]->left = tree_nodes[left];
            if (right != -1)
                tree_nodes[i]->right = tree_nodes[right];
        }

        root = tree_nodes[1];
    }

    auto depth()
    {
        return height(root);
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;
    vector<pair<int, int>> nodes(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        int left, right;
        cin >> left >> right;
        nodes[i] = {left, right};
    }

    Solution sol;
    sol.build_tree(nodes);
    cout << sol.depth() << '\n';
    return 0;
}