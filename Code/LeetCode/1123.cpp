#include <iostream>
#include <new>
#include <optional>
#include <queue>
#include <utility>
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
  auto lcaDeepestLeaves(TreeNode *root) -> TreeNode * {
    return dfs(root).second;
  }

private:
  static auto dfs(TreeNode *root) -> std::pair<int, TreeNode *> {
    if (!root)
      return {0, nullptr};

    auto [left_height, left_lca] = dfs(root->left);
    auto [right_height, right_lca] = dfs(root->right);

    if (left_height < right_height)
      return {right_height + 1, right_lca};
    if (left_height > right_height)
      return {left_height + 1, left_lca};
    return {left_height + 1, root};
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<std::optional<int>> root = {
      3, 5, 1, 6, 2, 0, 8, std::nullopt, std::nullopt, 7, 4};
  auto tree = TreeUtils::buildTree(root);
  Solution sol;
  TreeNode *res = sol.lcaDeepestLeaves(tree);
  if (res)
    std::cout << res->val << '\n';

  TreeUtils::destroyTree(tree);
}