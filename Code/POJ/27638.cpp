#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

struct TreeNode {
  int val;
  TreeNode *left{};
  TreeNode *right{};
  TreeNode(int i) : val(i) {};
};

class TreeUtils {
private:
  TreeNode *root;
  int leafs = 0;

  auto _get_height(TreeNode *node) -> int {
    if (!node) {
      return -1;
    }
    return std::max(_get_height(node->left), _get_height(node->right)) + 1;
  }

public:
  TreeUtils(int n, const std::vector<std::pair<int, int>> &tree) {
    std::vector<TreeNode *> node(n, nullptr);
    std::vector<bool> has_parent(n, false);

    for (int i = 0; i < n; ++i) {
      node[i] = new TreeNode(i);
    }

    for (int i = 0; i < n; ++i) {
      auto [left, right] = tree[i];
      if (left == -1 && right == -1) {
        ++leafs;
      }

      if (left != -1) {
        node[i]->left = node[left];
        has_parent[left] = true;
      }

      if (right != -1) {
        node[i]->right = node[right];
        has_parent[right] = true;
      }
    }

    root = node[std::find(has_parent.begin(), has_parent.end(), false) -
                has_parent.begin()];
  }

  auto get_leaf() -> int { return leafs; }

  auto get_height() -> int { return _get_height(root); }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n = 0;
  std::cin >> n;
  std::vector<std::pair<int, int>> tree(n);
  for (auto &[left, right] : tree) {
    std::cin >> left >> right;
  }
  TreeUtils sol(n, tree);
  std::cout << sol.get_height() << ' ' << sol.get_leaf() << '\n';
}
