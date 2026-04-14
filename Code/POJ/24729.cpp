#include <cstddef>
#include <iostream>
#include <string>

struct TreeNode {
  char val;
  TreeNode *first_child{};
  TreeNode *next_sibling{};
  TreeNode(char x) : val(x) {}
};

class TreeUtils {
private:
  static auto parseNode(const std::string &data, size_t &ptr) -> TreeNode * {
    if (ptr >= data.size())
      return nullptr;

    auto root = new TreeNode(data[ptr]);
    ++ptr;

    if (ptr < data.size() && data[ptr] == '(') {
      ++ptr;

      TreeNode *prev = nullptr;
      while (ptr < data.size() && data[ptr] != ')') {
        auto child = parseNode(data, ptr);
        if (!root->first_child)
          root->first_child = child;
        else
          prev->next_sibling = child;
        prev = child;

        if (ptr < data.size() && data[ptr] == ',')
          ++ptr;
      }

      if (ptr < data.size() && data[ptr] == ')')
        ++ptr;
    }

    return root;
  }

  static auto preorder(std::string &res, TreeNode *root) -> void {
    if (!root)
      return;

    res += root->val;
    preorder(res, root->first_child);
    preorder(res, root->next_sibling);
  }

  static auto postorder(std::string &res, TreeNode *root) -> void {
    if (!root)
      return;

    postorder(res, root->first_child);
    res += root->val;
    postorder(res, root->next_sibling);
  }

public:
  static auto buildTree(const std::string &data) -> TreeNode * {
    if (data.empty())
      return nullptr;

    size_t ptr = 0;
    return parseNode(data, ptr);
  }

  static auto preorderTraversal(TreeNode *root) -> std::string {
    std::string res = "";
    preorder(res, root);
    return res;
  }

  static auto postorderTraversal(TreeNode *root) -> std::string {
    std::string res = "";
    postorder(res, root);
    return res;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string data;
  std::cin >> data;
  auto root = TreeUtils::buildTree(data);
  std::cout << TreeUtils::preorderTraversal(root) << '\n';
  std::cout << TreeUtils::postorderTraversal(root) << '\n';
}