#include <cstddef>
#include <iostream>
#include <new>
#include <queue>
#include <utility>
#include <vector>

struct TreeNode {
  char data;
  TreeNode *first_child;
  TreeNode *next_sibling;
  TreeNode() : data(0), first_child(nullptr), next_sibling(nullptr) {}
  TreeNode(char x) : data(x), first_child(nullptr), next_sibling(nullptr) {}
  TreeNode(char x, TreeNode *first_child, TreeNode *next_sibling)
      : data(x), first_child(first_child), next_sibling(next_sibling) {}
};

static void destroyTree(TreeNode *root) noexcept {
  if (!root)
    return;
  destroyTree(root->first_child);
  destroyTree(root->next_sibling);
  delete root;
}

struct node {
  char id;
  int degree;
};

class TreeUtils {
public:
  [[nodiscard]] static auto buildTree(const std::vector<node> &nodes) noexcept
      -> TreeNode * {
    if (nodes.empty())
      return nullptr;

    auto root = new (std::nothrow) TreeNode(nodes[0].id);
    if (!root)
      return nullptr;

    std::queue<std::pair<TreeNode *, int>> q;
    q.emplace(root, nodes[0].degree);

    const auto n = nodes.size();
    size_t i = 1;
    while (!q.empty() && i < n) {
      auto [parent, degree] = q.front();
      q.pop();

      auto first_child = parent->first_child;
      auto prev_child = first_child;
      while (degree-- && i < n) {
        auto child = new (std::nothrow) TreeNode(nodes[i].id);
        if (!child)
          return nullptr;

        if (!first_child)
          first_child = child;
        else
          prev_child->next_sibling = child;

        prev_child = child;
        q.emplace(child, nodes[i].degree);
        ++i;
      }

      parent->first_child = first_child;
    }

    return root;
  }

  static auto postorderTraversal(TreeNode *root) noexcept -> void {
    if (!root)
      return;

    postorderTraversal(root->first_child);
    std::cout << root->data << ' ';
    postorderTraversal(root->next_sibling);
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  while (n--) {
    std::vector<node> nodes;
    char id;
    int degree;

    std::cin >> id >> degree;
    nodes.push_back({id, degree});

    int pending = degree;
    while (pending > 0) {
      std::cin >> id >> degree;
      nodes.push_back({id, degree});
      pending += degree - 1;
    }

    auto tree = TreeUtils::buildTree(nodes);

    TreeUtils::postorderTraversal(tree);

    destroyTree(tree);
  }
}