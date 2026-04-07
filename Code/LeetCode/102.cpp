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
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}

  ~TreeNode() {
    delete left;
    delete right;
  }
};

class Solution {
public:
  auto levelOrder(TreeNode *root) -> std::vector<std::vector<int>> {
    std::vector<std::vector<int>> res;
    if (!root)
      return res;

    std::queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
      int sz = q.size();
      std::vector<int> level;
      while (sz--) {
        auto front = q.front();
        q.pop();

        level.emplace_back(front->val);
        if (front->left)
          q.push(front->left);
        if (front->right)
          q.push(front->right);
      }
      res.emplace_back(level);
    }

    return res;
  }
};

class TreeUtils {
public:
  [[nodiscard]] static auto
  buildTree(std::vector<std::optional<int>> node) noexcept -> TreeNode * {
    if (node.empty() || node.front() == std::nullopt)
      return nullptr;

    auto root = new (std::nothrow) TreeNode(node.front().value());
    std::queue<TreeNode *> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < node.size()) {
      auto front = q.front();
      q.pop();

      if (node[i] != std::nullopt && i < node.size()) {
        front->left = new (std::nothrow) TreeNode(node[i].value());
        if (front->left)
          q.push(front->left);
      }
      ++i;

      if (node[i] != std::nullopt && i < node.size()) {
        front->right = new (std::nothrow) TreeNode(node[i].value());
        if (front->right)
          q.push(front->right);
      }
      ++i;
    }

    return root;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<std::optional<int>> node = {3,  9, 20, std::nullopt, std::nullopt,
                                          15, 7};
  auto root = TreeUtils::buildTree(node);
  Solution sol;
  std::vector<std::vector<int>> res = sol.levelOrder(root);
  for (const auto &r : res)
    for (int i : std::views::iota(0, static_cast<int>(r.size())))
      std::cout << r[i] << " \n"[i + 1 == r.size()];

  delete root;
}