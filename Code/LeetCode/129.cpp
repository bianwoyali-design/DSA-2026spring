#include <iostream>
#include <new>
#include <optional>
#include <queue>
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

class TreeUtils {
public:
  [[nodiscard]] static auto
  buildTree(const std::vector<std::optional<int>> &node) noexcept
      -> TreeNode * {
    if (node.empty() || node.front() == std::nullopt)
      return nullptr;

    auto root = new (std::nothrow) TreeNode(node.front().value());
    if (!root)
      return nullptr;

    std::queue<TreeNode *> q;
    q.push(root);

    const auto n = node.size();
    std::size_t i = 1;
    while (!q.empty() && i < n) {
      auto front = q.front();
      q.pop();

      if (i < n && node[i] != std::nullopt) {
        front->left = new (std::nothrow) TreeNode(node[i].value());
        if (front->left)
          q.push(front->left);
      }
      ++i;

      if (i < n && node[i] != std::nullopt) {
        front->right = new (std::nothrow) TreeNode(node[i].value());
        if (front->right)
          q.push(front->right);
      }
      ++i;
    }
    return root;
  }

  static auto destroyTree(TreeNode *root) noexcept -> void {
    if (!root)
      return;

    std::queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
      auto cur = q.front();
      q.pop();
      if (cur->left)
        q.push(cur->left);
      if (cur->right)
        q.push(cur->right);
      delete cur;
    }
  }
};

class Solution {
public:
  auto sumNumbers(TreeNode *root, int res = 0) -> int {
    if (!root) {
      return 0;
    }
    res = res * 10 + root->val;
    if (!root->left && !root->right) {
      return res;
    }
    return sumNumbers(root->left, res) + sumNumbers(root->right, res);
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<std::optional<int>> data = {0, 1};
  auto root = TreeUtils::buildTree(data);
  Solution sol;
  std::cout << sol.sumNumbers(root) << '\n';
}