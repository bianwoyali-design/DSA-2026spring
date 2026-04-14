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
  static inline auto dfs(TreeNode *root, std::string &res) -> void {
    if (!root)
      return;

    dfs(root->left, res);
    dfs(root->right, res);
    res += root->val;
  }

public:
  [[nodiscard]] static auto buildTree(const std::string &preorder,
                                      const std::string &inorder) noexcept
      -> TreeNode * {
    if (preorder.empty() || inorder.empty()) {
      return nullptr;
    }

    char root_val = preorder.front();
    auto root = new TreeNode(root_val);
    int index = inorder.find(root_val);
    const int n = preorder.size();

    root->left = buildTree(preorder.substr(1, index),inorder.substr(0, index));
    root->right = buildTree(preorder.substr(index + 1, n - index - 1),
                            inorder.substr(index + 1, n - index - 1));
    return root;
  }

  [[nodiscard]] static auto postorderTraversal(TreeNode *root) -> std::string {
    std::string res = "";
    dfs(root, res);
    return res;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string preorder, inorder;
  while (std::cin >> preorder >> inorder) {
    auto root = TreeUtils::buildTree(preorder, inorder);
    std::cout << TreeUtils::postorderTraversal(root) << '\n';
  }
}