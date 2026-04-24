#include <array>
#include <iostream>
#include <print>
#include <vector>

class Trie {
private:
  struct TrieNode {
    std::array<TrieNode *, 26> children{};
    int word_count = 0;
    uint32_t child_mask = 0;
  };

  TrieNode *root{};

  auto _erase_recursive(TrieNode *current, const std::string &word,
                        const int index) -> bool {
    if (!current) {
      return false;
    }

    if (index == word.size()) {
      if (current->word_count == 0) {
        return false;
      }
      --current->word_count;
      return !current->child_mask;
    }

    const int char_idx = word[index] - 'a';
    auto node = current->children[char_idx];

    if (!node) {
      return false;
    }

    if (_erase_recursive(node, word, index + 1)) {
      current->children[char_idx] = nullptr;
      current->child_mask &= ~(1 << char_idx);
      return current->word_count == 0 && !current->child_mask;
    }

    return false;
  }

  auto _clean(TrieNode *node) -> void {
    if (!node)
      return;

    auto mask = node->child_mask;
    while (mask) {
      _clean(node->children[__builtin_ctz(mask)]);
      mask &= (mask - 1);
    }
    delete node;
  }

public:
  Trie() : root(new TrieNode()) {}

  ~Trie() { _clean(root); }

  auto insert(const std::string &word) -> void {
    auto current = root;

    for (auto &&c : word) {
      const int index = c - 'a';
      if (!current->children[index]) {
        current->children[index] = new TrieNode();
        current->child_mask |= (1 << index);
      }
      current = current->children[index];
    }
    ++current->word_count;
  }

  auto search(const std::string &word) -> bool {
    if (!root)
      return false;

    auto current = root;

    for (auto &&c : word) {
      const int index = c - 'a';
      if (!current->children[index]) {
        return false;
      }
      current = current->children[index];
    }
    return current->word_count > 0;
  }

  auto startsWith(const std::string &prefix) -> bool {
    if (!root)
      return false;

    auto current = root;

    for (auto &&c : prefix) {
      const int index = c - 'a';
      if (!current->children[index]) {
        return false;
      }
      current = current->children[index];
    }
    return true;
  }

  auto erase(const std::string &word) -> bool {
    return _erase_recursive(root, word, 0);
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  auto trie = Trie();
  std::vector<std::string> words = {"and", "ant", "do", "geek", "dad", "ball"};
  for (auto &&w : words) {
    trie.insert(w);
  }

  std::println("搜索 'do': {}", trie.search("do"));
  std::println("搜索 'bat': {}", trie.search("bat"));
  std::println("前缀 'an': {}", trie.startsWith("an"));

  trie.erase("geek");
  std::println("删除 'geek' 后搜索: {}", trie.search("geek"));
}