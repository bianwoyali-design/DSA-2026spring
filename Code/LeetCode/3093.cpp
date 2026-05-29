#include <array>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

class Trie {
  struct TrieNode {
    std::array<TrieNode *, 26> children{};
    int min_length = 5001;
    int index = 0;

    ~TrieNode() {
      for (auto *c : children) {
        delete c;
      }
    }
  };

  TrieNode *root;

public:
  explicit Trie() : root(new TrieNode()) {}

  ~Trie() { delete root; }

  auto update(TrieNode *node, int length, int index) -> void {
    if (length < node->min_length) {
      node->min_length = length;
      node->index = index;
    }
  }

  auto insert(const std::string &word, int index) -> void {
    auto *current = root;
    int length = static_cast<int>(word.length());
    update(root, length, index);

    for (char it : std::ranges::reverse_view(word)) {
      const int idx = it - 'a';
      if (!current->children[idx]) {
        current->children[idx] = new TrieNode();
      }
      current = current->children[idx];
      update(current, length, index);
    }
  }

  auto query(const std::string &word) -> int {
    auto *current = root;

    for (char it : std::ranges::reverse_view(word)) {
      const int idx = it - 'a';
      if (!current->children[idx]) {
        return current->index;
      }
      current = current->children[idx];
    }
    return current->index;
  }
};

class Solution {
public:
  auto stringIndices(std::vector<std::string> &wordsContainer,
                     std::vector<std::string> &wordsQuery) -> std::vector<int> {
    Trie trie;
    for (int i = 0; i < wordsContainer.size(); ++i) {
      trie.insert(wordsContainer[i], i);
    }

    std::vector<int> ans;
    ans.reserve(wordsQuery.size());
    for (auto &word : wordsQuery) {
      ans.emplace_back(trie.query(word));
    }

    return ans;
  }
};

auto main() -> int {
  Solution solution;
  std::vector<std::string> container{"abcd", "bcd", "xbcd"};
  std::vector<std::string> query{"cd", "bcd", "xyz"};
  auto ans = solution.stringIndices(container, query);
  for (int x : ans) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
}