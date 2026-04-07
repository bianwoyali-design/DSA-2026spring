#include <iostream>
#include <new>
#include <optional>
#include <queue>
#include <ranges>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  explicit TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x, TreeNode *left, TreeNode *right)
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
  auto inorderTraversal(TreeNode *root) -> std::vector<int> {
    std::vector<int> res;
    auto curr = root;

    while (curr) {
      if (!curr->left) {
        res.emplace_back(curr->val);
        curr = curr->right;
      } else {
        TreeNode *pre = curr->left;
        while (pre->right && pre->right != curr)
          pre = pre->right;

        if (!pre->right) {
          pre->right = curr;
          curr = curr->left;
        } else {
          res.emplace_back(curr->val);
          pre->right = nullptr;
          curr = curr->right;
        }
      }
    }

    return res;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<std::optional<int>> root = {1, std::nullopt, 2, 3};
  auto tree = TreeUtils::buildTree(root);
  Solution sol;
  std::vector<int> res = sol.inorderTraversal(tree);
  for (int i : std::views::iota(0, static_cast<int>(res.size())))
    std::cout << res[i] << " \n"[i + 1 == res.size()];

  TreeUtils::destroyTree(tree);
}