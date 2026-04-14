#include <cstddef>
#include <iostream>
#include <string>

struct TreeNode {
  char val;
  TreeNode *left{};
  TreeNode *right{};
  TreeNode(char x) : val(x) {}
};

class TreeUtils {
private:
  static inline auto insertNode(TreeNode *root, char val) -> TreeNode * {
    if (!root) {
      return new TreeNode(val);
    }

    if (val < root->val) {
      root->left = insertNode(root->left, val);
    } else {
      root->right = insertNode(root->right, val);
    }
    return root;
  }

  static inline auto dfs(TreeNode *root, std::string &res) -> void {
    if (!root)
      return;

    res += root->val;
    dfs(root->left, res);
    dfs(root->right, res);
  }

public:
  [[nodiscard]] static auto buildBST(const std::string &leaves) -> TreeNode * {
    if (leaves.empty()) {
      return nullptr;
    }

    TreeNode *root = nullptr;
    for (int i = leaves.size() - 1; i >= 0; --i) {
      root = insertNode(root, leaves[i]);
    }

    return root;
  }

  [[nodiscard]] static auto preorderTraversal(TreeNode *root) -> std::string {
    std::string res;
    dfs(root, res);
    return res;
  }
};

void delete_tree(TreeNode *root) {
  if (root == nullptr)
    return;
  delete_tree(root->left);
  delete_tree(root->right);
  delete root;
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string leaves;
  while (true) {
    std::string line;
    std::cin >> line;

    if (line == "*") {
      auto root = TreeUtils::buildBST(leaves);
      std::cout << TreeUtils::preorderTraversal(root) << '\n';
      delete_tree(root);
      leaves.clear();
      continue;
    } else if (line == "$") {
      auto root = TreeUtils::buildBST(leaves);
      std::cout << TreeUtils::preorderTraversal(root) << '\n';
      delete_tree(root);
      leaves.clear();
      break;
    }

    leaves += line;
  }
}