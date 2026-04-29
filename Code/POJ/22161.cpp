#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

struct TreeNode {
  char ch;
  int freq;
  TreeNode *left{};
  TreeNode *right{};
  TreeNode() : ch(0), freq(0) {}
  TreeNode(char ch, int freq) : ch(ch), freq(freq) {}
  TreeNode(char ch, int freq, TreeNode *left, TreeNode *right)
      : ch(ch), freq(freq), left(left), right(right) {}
};

class HuffmanTree {
private:
  struct CompareNode {
    auto operator()(TreeNode *a, TreeNode *b) -> bool {
      if (a->freq != b->freq) {
        return a->freq > b->freq;
      }
      return a->ch > b->ch;
    }
  };

  std::unordered_map<char, std::string> codes;
  std::priority_queue<TreeNode *, std::vector<TreeNode *>, CompareNode> pq;
  TreeNode *root{};

  auto destroy(TreeNode *node) -> void {
    if (!node) {
      return;
    }

    destroy(node->left);
    destroy(node->right);
    delete node;
  }

public:
  HuffmanTree() = default;
  HuffmanTree(const HuffmanTree &) = delete;
  auto operator=(const HuffmanTree &) -> HuffmanTree & = delete;
  HuffmanTree(HuffmanTree &&) = delete;
  auto operator=(HuffmanTree &&) -> HuffmanTree & = delete;
  ~HuffmanTree() { destroy(root); }

  auto build_huffman_tree(const std::vector<std::pair<char, int>> &char_set)
      -> TreeNode * {
    for (auto &&x : char_set) {
      pq.emplace(new TreeNode(x.first, x.second));
    }

    while (pq.size() > 1) {
      auto left = pq.top();
      pq.pop();
      auto right = pq.top();
      pq.pop();
      auto node = new TreeNode('\0', left->freq + right->freq, left, right);
      pq.emplace(node);
    }

    root = pq.top();
    auto encode_huffman_tree = [&](auto &&self, TreeNode *node,
                                   const std::string &code) -> void {
      if (!node->left && !node->right) {
        codes[node->ch] = code;
        return;
      }

      self(self, node->left, code + '0');
      self(self, node->right, code + '1');
    };
    encode_huffman_tree(encode_huffman_tree, root, "");

    return root;
  }

  auto encode_huffman(const std::string &str) -> std::string {
    std::string code;

    for (auto &&c : str) {
      code += codes[c];
    }

    return code;
  }

  auto decode_huffman(const std::string &code, TreeNode *root) -> std::string {
    std::string str;

    auto node = root;
    for (auto &&c : code) {
      if (c == '0') {
        node = node->left;
      } else {
        node = node->right;
      }

      if (!node->left && !node->right) {
        str += node->ch;
        node = root;
      }
    }

    return str;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::vector<std::pair<char, int>> char_set(n);
  for (auto &&[ch, freq] : char_set) {
    std::cin >> ch >> freq;
  }

  if (char_set.size() == 1) {
    std::string ipt;
    while (std::cin >> ipt) {
      if (ipt.front() == '1' || ipt.front() == '0') {
        std::cout << char_set.front().first << '\n';
      } else {
        std::cout << char_set.front().second << '\n';
      }
    }
    return 0;
  }

  HuffmanTree ht;
  auto root = ht.build_huffman_tree(char_set);

  std::string ipt;
  while (std::cin >> ipt) {
    if (ipt.front() == '1' || ipt.front() == '0') {
      std::cout << ht.decode_huffman(ipt, root) << '\n';
    } else {
      std::cout << ht.encode_huffman(ipt) << '\n';
    }
  }
}