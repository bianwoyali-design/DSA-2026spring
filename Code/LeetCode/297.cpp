#include <cstddef>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left{};
  TreeNode *right{};
  TreeNode(int x) : val(x) {}
};

class Codec {
public:
  // Encodes a tree to a single string.
  auto serialize(TreeNode *root) -> std::string {
    if (!root)
      return "";

    std::string data;
    std::deque<TreeNode *> q;
    q.emplace_back(root);

    while (!q.empty()) {
      auto front = q.front();
      q.pop_front();

      if (!front) {
        data += "null,";
      } else {
        data += std::to_string(front->val) + ',';
        q.emplace_back(front->left);
        q.emplace_back(front->right);
      }
    }
    data.pop_back();
    return data;
  }

  // Decodes your encoded data to tree.
  auto deserialize(const std::string &data) -> TreeNode * {
    if (data.empty())
      return nullptr;

    std::stringstream ss(data);
    std::string str;
    getline(ss, str, ',');

    auto root = new TreeNode(std::stoi(str));
    std::deque<TreeNode *> q;
    q.emplace_back(root);

    while (!q.empty()) {
      auto front = q.front();
      q.pop_front();

      if (getline(ss, str, ',')) {
        if (str != "null") {
          front->left = new TreeNode(std::stoi(str));
          q.push_back(front->left);
        }
      }

      if (getline(ss, str, ',')) {
        if (str != "null") {
          front->right = new TreeNode(std::stoi(str));
          q.push_back(front->right);
        }
      }
    }

    return root;
  }
};

auto same_tree(TreeNode *a, TreeNode *b) -> bool {
  if (!a || !b)
    return a == b;
  return a->val == b->val && same_tree(a->left, b->left) &&
         same_tree(a->right, b->right);
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  Codec ser, deser;
  std::string data = "1,2,3,null,null,4,5";
  auto root = deser.deserialize(data);

  TreeNode *ans = deser.deserialize(ser.serialize(root));
  std::cout << same_tree(root, ans) << '\n';
}