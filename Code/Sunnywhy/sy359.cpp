#include <iostream>
#include <vector>

template <typename Type> class AVL {
private:
  struct TreeNode {
    Type value;
    int height = 1;
    TreeNode *left{};
    TreeNode *right{};
    TreeNode(const Type &value) : value(value) {}
  };

  TreeNode *root = nullptr;

  auto _get_height(TreeNode *node) -> int {
    if (!node) {
      return 0;
    }
    return node->height;
  }

  auto _get_balance(TreeNode *node) -> int {
    if (!node) {
      return 0;
    }
    return _get_height(node->left) - _get_height(node->right);
  }

  auto _rotate_left(TreeNode *z) -> TreeNode * {
    auto y = z->right;
    auto T2 = y->left;
    y->left = z;
    z->right = T2;
    z->height = 1 + std::max(_get_height(z->left), _get_height(z->right));
    y->height = 1 + std::max(_get_height(y->left), _get_height(y->right));
    return y;
  }

  auto _rotate_right(TreeNode *y) -> TreeNode * {
    auto x = y->left;
    auto T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + std::max(_get_height(y->left), _get_height(y->right));
    x->height = 1 + std::max(_get_height(x->left), _get_height(x->right));
    return x;
  }

  auto _insert(const Type &value, TreeNode *node) -> TreeNode * {
    if (!node) {
      return new TreeNode(value);
    }

    if (value < node->value) {
      node->left = _insert(value, node->left);
    } else {
      node->right = _insert(value, node->right);
    }

    node->height =
        1 + std::max(_get_height(node->left), _get_height(node->right));

    int balance = _get_balance(node);

    if (balance > 1) {
      if (value < node->left->value) {
        return _rotate_right(node);
      } else {
        node->left = _rotate_left(node->left);
        return _rotate_right(node);
      }
    }

    if (balance < -1) {
      if (value > node->right->value) {
        return _rotate_left(node);
      } else {
        node->right = _rotate_right(node->right);
        return _rotate_left(node);
      }
    }

    return node;
  }

  auto _preorder(TreeNode *node, std::vector<Type> &result) -> void {
    if (!node) {
      return;
    }
    result.push_back(node->value);
    _preorder(node->left, result);
    _preorder(node->right, result);
  }

  auto _clean(TreeNode *node) -> void {
    if (!node)
      return;
    _clean(node->left);
    _clean(node->right);
    delete node;
  }

public:
  AVL() = default;

  ~AVL() { _clean(root); }

  auto insert(const Type &value) -> void {
    if (!root) {
      root = new TreeNode(value);
    } else {
      root = _insert(value, root);
    }
  }

  auto preorder() -> std::vector<Type> {
    std::vector<int> result;
    if (root) {
      _preorder(root, result);
    }
    return result;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  AVL<int> avl;

  while (n--) {
    int value;
    std::cin >> value;
    avl.insert(value);
  }

  auto preorder_result = avl.preorder();

  for (int i = 0; i < preorder_result.size(); ++i) {
    std::cout << preorder_result[i] << " \n"[i + 1 == preorder_result.size()];
  }
}