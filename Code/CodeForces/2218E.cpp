#include <iostream>
#include <vector>

class Trie {
  struct TrieNode {
    TrieNode *left{};
    TrieNode *right{};
    TrieNode() = default;
  };

  TrieNode *root = new TrieNode();
  constexpr static int HIGH_BIT = 30;

  auto _delete(TrieNode *root) -> void {
    if (!root) {
      return;
    }
    _delete(root->left);
    _delete(root->right);
    delete root;
  }

public:
  auto add(int num) -> void {
    auto *curr = root;
    for (int k = HIGH_BIT; k >= 0; --k) {
      int bit = (num >> k) & 1;
      if (!bit) {
        if (!curr->left) {
          curr->left = new TrieNode();
        }
        curr = curr->left;
      } else {
        if (!curr->right) {
          curr->right = new TrieNode();
        }
        curr = curr->right;
      }
    }
  }

  auto check(int num) -> int {
    auto *curr = root;
    int x = 0;
    for (int k = HIGH_BIT; k >= 0; --k) {
      int bit = (num >> k) & 1;
      if (!bit) {
        if (curr->right) {
          x = x << 1 | 1;
          curr = curr->right;
        } else {
          x <<= 1;
          curr = curr->left;
        }
      } else {
        if (curr->left) {
          x = x << 1 | 1;
          curr = curr->left;
        } else {
          x <<= 1;
          curr = curr->right;
        }
      }
    }
    return x;
  }

  auto clean() -> void {
    _delete(root);
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int T{};
  std::cin >> T;
  while (T--) {
    int n{};
    std::cin >> n;
    std::vector<int> nums(n);
    for (auto &&v : nums) {
      std::cin >> v;
    }

    Trie trie;
    int XOR = 0;
    for (int i = 1; i < n; ++i) {
      trie.add(nums[i - 1]);
      XOR = std::max(XOR, trie.check(nums[i]));
    }

    std::cout << XOR << '\n';
    trie.clean();
  }
}