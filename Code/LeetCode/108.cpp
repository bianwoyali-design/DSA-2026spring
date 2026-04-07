#include <iostream>
#include <ranges>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  auto sortedArrayToBST(std::vector<int> &nums) -> TreeNode * {
    auto dfs = [&](this auto &&dfs, int left, int right) -> TreeNode * {
      if (left == right)
        return nullptr;
      int mid = left + ((right - left) >> 1);
      return new TreeNode(nums[mid], dfs(left, mid), dfs(mid + 1, right));
    };
    return dfs(0, static_cast<int>(nums.size()));
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<int> nums = {-10, -3, 0, 5, 9};
  Solution sol;
  auto root = sol.sortedArrayToBST(nums);
  std::vector<int> res;

  auto PreorderTraversal = [&](this auto &&PreorderTraversal,
                               TreeNode *root) -> void {
    if (!root)
      return;
    res.emplace_back(root->val);
    PreorderTraversal(root->left);
    PreorderTraversal(root->right);
  };

  PreorderTraversal(root);

  for (int i : std::views::iota(0, static_cast<int>(res.size())))
    std::cout << res[i] << " \n"[i + 1 == res.size()];
}