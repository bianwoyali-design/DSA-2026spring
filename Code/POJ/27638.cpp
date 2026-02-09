#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
private:
    TreeNode *root;
    int cnt_leafs = 0;

    template <typename T>
    auto height(T &node)
    {
        if (node == nullptr)
            return -1;
        return max(height(node->left), height(node->right)) + 1;
    }

public:
    auto build_tree(vector<pair<int, int>> nodes)
    {
        int n = nodes.size();
        vector<TreeNode *> tree_nodes(n);
        vector<bool> has_parents(n, false);

        for (int i = 0; i < n; ++i)
            tree_nodes[i] = new TreeNode(i);

        for (int i = 0; i < n; ++i)
        {
            auto [left, right] = nodes[i];
            if (left != -1)
            {
                tree_nodes[i]->left = tree_nodes[left];
                has_parents[left] = true;
            }
            if (right != -1)
            {
                tree_nodes[i]->right = tree_nodes[right];
                has_parents[right] = true;
            }
            if (left == -1 && right == -1)
                ++cnt_leafs;
        }

        root = tree_nodes[find(has_parents.begin(), has_parents.end(), false) - has_parents.begin()];
    }

    auto depth()
    {
        return height(root);
    }

    auto leaf()
    {
        return cnt_leafs;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;
    vector<pair<int, int>> nodes(n);
    for (auto &n : nodes)
        cin >> n.first >> n.second;

    Solution sol;
    sol.build_tree(nodes);
    cout << sol.depth() << ' ' << sol.leaf() << '\n';
    return 0;
}