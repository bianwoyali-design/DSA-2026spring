#include <iostream>
#include <vector>

class Solution {
  struct TrieNode {
    TrieNode *left{};
    TrieNode *right{};
    TrieNode() = default;
  };

  TrieNode *root = new TrieNode();
  constexpr static int HIGH_BIT = 30;

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
    int x = 0;
    auto *curr = root;
    for (int k = HIGH_BIT; k >= 0; --k) {
      int bit = (num >> k) & 1;
      if (!bit) {
        if (curr->right) {
          curr = curr->right;
          x = x << 1 | 1;
        } else {
          curr = curr->left;
          x <<= 1;
        }
      } else {
        if (curr->left) {
          curr = curr->left;
          x = x << 1 | 1;
        } else {
          curr = curr->right;
          x <<= 1;
        }
      }
    }
    return x;
  }

public:
  auto findMaximumXOR(std::vector<int> &nums) -> int {
    int n = nums.size();
    int maxXOR = 0;
    for (int i = 1; i < n; ++i) {
      add(nums[i - 1]);
      maxXOR = std::max(maxXOR, check(nums[i]));
    }
    return maxXOR;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<int> nums = {14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70};
  Solution sol;
  std::cout << sol.findMaximumXOR(nums) << '\n';
}