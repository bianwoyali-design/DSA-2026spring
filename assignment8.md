# DSA Assignment #8: 🌲（3/3）

*Updated 2026-04-21 19:09 GMT+8*
 *Compiled by <mark>张真铭 元培学院</mark> (2026 Spring)*



>**说明：**
>
>1. **解题与记录：**
>
>     对于每一个题目，请提供其解题思路（可选），并附上使用Python或C++编写的源代码（确保已在OpenJudge， Codeforces，LeetCode等平台上获得Accepted）。请将这些信息连同显示“Accepted”的截图一起填写到下方的作业模板中。（推荐使用Typora https://typoraio.cn 进行编辑，当然你也可以选择Word。）无论题目是否已通过，请标明每个题目大致花费的时间。
>
>2. **提交安排：**提交时，请首先上传PDF格式的文件，并将.md或.doc格式的文件作为附件上传至右侧的“作业评论”区。确保你的Canvas账户有一个清晰可见的本人头像，提交的文件为PDF格式，并且“作业评论”区包含上传的.md或.doc附件。
> 
>3. **延迟提交：**如果你预计无法在截止日期前提交作业，请提前告知具体原因。这有助于我们了解情况并可能为你提供适当的延期或其他帮助。  
>
>请按照上述指导认真准备和提交作业，以保证顺利完成课程要求。



## 1. 题目

### M晴问9.7: 向下调整构建大顶堆

手搓堆, https://sunnywhy.com/sfbj/9/7

思路：



代码：

```cpp
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

template <typename Type> class BinaryHeap {
private:
  std::vector<Type> heap;

  auto get_min_child(auto &&i) -> int {
    if (2 * i + 2 >= heap.size()) {
      return 2 * i + 1;
    }
    if (heap[2 * i + 1] < heap[2 * i + 2]) {
      return 2 * i + 1;
    }
    return 2 * i + 2;
  }

  auto perc_up(auto &&i) -> void {
    while (i > 0) {
      const int parent = (i - 1) / 2;
      if (heap[i] < heap[parent]) {
        std::swap(heap[i], heap[parent]);
      } else {
        break;
      }
      i = parent;
    }
  }

  auto perc_down(auto &&i) -> void {
    while (2 * i + 1 < heap.size()) {
      const int sm_child = get_min_child(i);
      if (heap[i] > heap[sm_child]) {
        std::swap(heap[i], heap[sm_child]);
      } else {
        break;
      }
      i = sm_child;
    }
  }

public:
  explicit BinaryHeap(std::vector<int> &x) : heap(std::move(x)) {}

  auto insert(auto &&item) -> void {
    heap.push_back(item);
    perc_up(static_cast<int>(heap.size() - 1));
  }

  auto pop_root() -> int {
    std::swap(heap.front(), heap.back());
    const int result = heap.back();
    heap.pop_back();
    perc_down(0);
    return result;
  }

  auto heapify() -> std::vector<Type> {
    int i = (heap.size() >> 1) - 1;
    while (i >= 0) {
      perc_down(i);
      --i;
    }
    return heap;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::vector<int> list(n);
  for (auto &&x : list) {
    std::cin >> x;
    x = -x;
  }

  BinaryHeap<int> priority_queue(list);
  auto ans = priority_queue.heapify();
  for (auto &&[i, x] : std::views::zip(std::views::iota(0), ans)) {
    std::cout << -x << " \n"[i + 1 == ans.size()];
  }
}
```

> 共用时20min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260421215206539.png"/>



### M1722.执行交换操作后的最小汉明距离

dsu, https://leetcode.cn/problems/minimize-hamming-distance-after-swap-operations/


思路：



代码：

```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

class Solution {
  std::vector<int> pa;
  std::vector<int> rank;

  auto Find(int x) -> int { return pa[x] == x ? x : pa[x] = Find(pa[x]); }

  auto Union(int i, int j) -> void {
    int irep = Find(i);
    int jrep = Find(j);

    if (rank[irep] > rank[jrep]) {
      pa[jrep] = irep;
    } else if (rank[irep] < rank[jrep]) {
      pa[irep] = jrep;
    } else {
      pa[irep] = jrep;
      ++rank[jrep];
    }
  }

public:
  auto minimumHammingDistance(std::vector<int> &source,
                              std::vector<int> &target,
                              std::vector<std::vector<int>> &allowedSwaps)
      -> int {
    const int n = source.size();
    rank.resize(n, 0);
    pa.resize(n);
    for (int i = 0; i < n; ++i) {
      pa[i] = i;
    }

    for (auto &&pair : allowedSwaps) {
      Union(pair[0], pair[1]);
    }

    std::vector<std::vector<int>> src(n);
    for (auto &&[i, v] : std::views::zip(std::views::iota(0), source)) {
      int root = Find(i);
      src[root].push_back(v);
    }

    std::vector<std::vector<int>> tgt(n);
    for (auto &&[i, v] : std::views::zip(std::views::iota(0), target)) {
      int root = Find(i);
      tgt[root].push_back(v);
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (src[i].empty())
        continue;

      std::ranges::sort(src[i]);
      std::ranges::sort(tgt[i]);

      std::vector<int> diff;
      std::ranges::set_symmetric_difference(src[i], tgt[i],
                                                   std::back_inserter(diff));

      res += diff.size() / 2;
    }

    return res;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<int> source = {1, 2, 3, 4}, target = {2, 1, 4, 5};
  std::vector<std::vector<int>> allowedSwaps = {{0, 1}, {2, 3}};
  Solution sol;
  std::cout << sol.minimumHammingDistance(source, target, allowedSwaps) << '\n';
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260421223236523.png"/>



### T22161: 哈夫曼编码树

greedy, http://cs101.openjudge.cn/practice/22161/

思路：

对于C++有一点需要注意，写在注释里了。

代码：

```cpp
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
    /* The priority queue uses the comparator such that if comp(a, b) is true, a
     * is placed below b, meaning a has a lower priority. */
    auto operator()(TreeNode *a, TreeNode *b) -> bool {
      if (a->freq != b->freq) {
        return a->freq > b->freq;
      }
      return a->ch > b->ch;
    }
  };

  std::unordered_map<char, std::string> codes;
  std::priority_queue<TreeNode *, std::vector<TreeNode *>, CompareNode> pq;

public:
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
      auto node = new TreeNode(std::min(left->ch, right->ch),
                               left->freq + right->freq, left, right);
      pq.emplace(node);
    }

    auto root = pq.top();
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

  auto encode_huffman(const std::string &str, TreeNode *root) -> std::string {
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
      std::cout << ht.encode_huffman(ipt, root) << '\n';
    }
  }
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260421235844140.png"/>



### M晴问9.5: 平衡二叉树的建立

手搓AVL, https://sunnywhy.com/sfbj/9/5/359

思路：



代码：

```cpp
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
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260423211624341.png"/>



### M208.实现Trie（前缀树）

trie, https://leetcode.cn/problems/implement-trie-prefix-tree/

思路：

课件中的写法存在性能问题：每次检查`children`是否全空都要扫描整个数组。

这里使用了一个`child_mask`来记录`children`中的状态，1代表存在，0代表不存在，这样在检查的时候只要判断`child_mask`是否等于零就可以判断是否全空。

不用`bool isLeaf`的原因是在析构的时候可以通过`__builtin_ctz_`遍历每一个非空的`children`进行高效内存管理。

代码

```cpp
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
```



<mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260423221431055.png"/>



### M307.区域和检索 - 数组可修改

segment tree, https://leetcode.cn/problems/range-sum-query-mutable/

思路：

三种写法：BIT，线段树，zkw线段树

代码

```cpp
template <typename Type, typename Func> class LazySegTree {
private:
  size_t n;
  Type default_val;
  Func func;
  std::vector<Type> tree;
  std::vector<Type> lazy;
  std::vector<bool> has_lazy;

  auto _perc_down(size_t node, size_t start, size_t end) -> void {
    if (start == end || !has_lazy[node]) {
      return;
    }

    if (has_lazy[node]) {
      const auto mid = start + ((end - start) >> 1);
      const auto left = node << 1;
      const auto right = node << 1 | 1;

      lazy[left] = lazy[node];
      has_lazy[left] = true;
      tree[left] = lazy[node] * (mid + 1 - start);

      lazy[right] = lazy[node];
      has_lazy[right] = true;
      tree[right] = lazy[node] * (end - mid);

      lazy[node] = 0;
      has_lazy[node] = false;
    }
  }

  auto _build(const std::vector<Type> &data, size_t node, size_t start,
              size_t end) -> void {
    if (start == end) {
      tree[node] = data[start];
      return;
    }

    const auto mid = start + ((end - start) >> 1);
    _build(data, node << 1, start, mid);
    _build(data, node << 1 | 1, mid + 1, end);

    tree[node] = func(tree[node << 1], tree[node << 1 | 1]);
  }

  auto _update_range(size_t node, size_t start, size_t end, size_t l, size_t r,
                     Type value) -> void {
    if (l <= start && end <= r) {
      lazy[node] = value;
      has_lazy[node] = true;
      tree[node] = (end - start + 1) * value;
      return;
    }

    _perc_down(node, start, end);

    const auto mid = start + ((end - start) >> 1);
    if (l <= mid) {
      _update_range(node << 1, start, mid, l, r, value);
    }
    if (r > mid) {
      _update_range(node << 1 | 1, mid + 1, end, l, r, value);
    }

    tree[node] = func(tree[node << 1], tree[node << 1 | 1]);
  }

  auto _query_range(size_t node, size_t start, size_t end, size_t l, size_t r)
      -> Type {
    if (l <= start && end <= r) {
      return tree[node];
    }

    _perc_down(node, start, end);
    const auto mid = start + ((end - start) >> 1);
    if (r <= mid) {
      return _query_range(node << 1, start, mid, l, r);
    }
    if (l > mid) {
      return _query_range(node << 1 | 1, mid + 1, end, l, r);
    }

    return func(_query_range(node << 1, start, mid, l, r),
                _query_range(node << 1 | 1, mid + 1, end, l, r));
  }

public:
  explicit LazySegTree(const std::vector<Type> &data, Func func = Func{},
                       const Type &de = Type())
      : n(data.size()), default_val(de), func(func) {
    tree.assign(4 * n, default_val);
    lazy.assign(4 * n, default_val);
    has_lazy.assign(4 * n, false);
    if (n > 0) {
      _build(data, 1, 0, n - 1);
    }
  }

  auto update_range(size_t l, size_t r, Type value) -> void {
    if (n == 0 || l > r) {
      return;
    }
    _update_range(1, 0, n - 1, l, r, value);
  }

  auto query_range(size_t l, size_t r) -> Type {
    if (n == 0 || l > r) {
      return default_val;
    }
    return _query_range(1, 0, n - 1, l, r);
  }
};
```



<mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260424132238000.png"/>



## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2026spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

### 懒标记

普通的线段树可以处理单点修改，区间查询，但是若要修改某个区间，传统的做法是遍历每个点去修改，复杂度会退化成$O(nlogn)$，因此需要懒标记去处理。

#### 原理

使用一个数组`lazy`存储每个节点需要修改的值，将需要修改的区间内每个需要修改的节点都打上标记，并只在执行查询操作时修改结点的值同时向下（子节点）传递修改操作，这样只需要处理要访问部分的修改从而提高性能

#### 核心操作

1. **打标记**：当修改的区间完全覆盖了当前节点表示的范围，就不再递归，直接在当前节点记下修改值，并更新当前节点的总和。
2. **存标记**：每个节点多一个变量 lazy，记录“我有多少增量还没传给儿子”。
3. **下传标记 (push_down)**：当你不得不去访问当前节点的子节点时（因为要查询或修改更小的区间），顺便把身上的标记传给左右儿子，然后清空自己的标记。

#### 具体实现

这里实现了一个区间修改+线性运算的线段树，包括了递归形式和zkw线段树形式

```cpp
template <typename Type, typename Func> class LazySegTree {
private:
  size_t n;
  Type default_val;
  Func func;
  std::vector<Type> tree;
  std::vector<Type> lazy;
  std::vector<bool> has_lazy;

  auto _perc_down(size_t node, size_t start, size_t end) -> void {
    if (has_lazy[node]) {
      const auto mid = start + ((end - start) >> 1);
      const auto left = node << 1;
      const auto right = node << 1 | 1;

      lazy[left] = lazy[node];
      has_lazy[left] = true;
      tree[left] = lazy[node] * (mid + 1 - start);

      lazy[right] = lazy[node];
      has_lazy[right] = true;
      tree[right] = lazy[node] * (end - mid);

      lazy[node] = 0;
      has_lazy[node] = false;
    }
  }

  auto _build(const std::vector<Type> &data, size_t node, size_t start,
              size_t end) -> void {
    if (start == end) {
      tree[node] = data[start];
      return;
    }

    const auto mid = start + ((end - start) >> 1);
    _build(data, node << 1, start, mid);
    _build(data, node << 1 | 1, mid + 1, end);

    tree[node] = func(tree[node << 1], tree[node << 1 | 1]);
  }

  auto _update_range(size_t node, size_t start, size_t end, size_t l, size_t r,
                     Type value) -> void {
    if (l <= start && end <= r) {
      lazy[node] = value;
      has_lazy[node] = true;
      tree[node] = (end - start + 1) * value;
      return;
    }

    _perc_down(node, start, end);

    const auto mid = start + ((end - start) >> 1);
    if (l <= mid) {
      _update_range(node << 1, start, mid, l, r, value);
    }
    if (r > mid) {
      _update_range(node << 1 | 1, mid + 1, end, l, r, value);
    }

    tree[node] = func(tree[node << 1], tree[node << 1 | 1]);
  }

  auto _query_range(size_t node, size_t start, size_t end, size_t l, size_t r)
      -> Type {
    if (l <= start && end <= r) {
      return tree[node];
    }

    _perc_down(node, start, end);
    const auto mid = start + ((end - start) >> 1);
    if (r <= mid) {
      return _query_range(node << 1, start, mid, l, r);
    }
    if (l > mid) {
      return _query_range(node << 1 | 1, mid + 1, end, l, r);
    }

    return func(_query_range(node << 1, start, end, l, r),
                _query_range(node << 1 | 1, start, end, l, r));
  }

public:
  explicit LazySegTree(const std::vector<Type> &data, Func func = Func{},
                       const Type &de = Type())
      : n(data.size()), default_val(de) {
    tree.assign(4 * n, default_val);
    lazy.assign(4 * n, default_val);
    has_lazy.assign(4 * n, false);
    _build(data, 1, 0, n - 1);
  }

  auto update_range(size_t l, size_t r, Type value) -> void {
    _update_range(1, 0, n - 1, l, r, value);
  }

  auto query_range(size_t l, size_t r) -> Type {
    return _query_range(1, 0, n - 1, l, r);
  }
};
```

```cpp
template <typename Type, typename Func> class ZWKLazySegmentTree {
private:
  size_t size;
  size_t base;
  size_t height;
  Type default_val;
  Func func;
  std::vector<Type> tree;
  std::vector<Type> lazy;
  std::vector<bool> has_lazy;

  auto _apply(size_t p, const Type &value, size_t len) -> void {
    tree[p] = value * static_cast<Type>(len);
    if (p < base) {
      lazy[p] = value;
      has_lazy[p] = true;
    }
  }

  auto _push(size_t p) -> void {
    for (size_t s = height; s > 0; --s) {
      const size_t i = p >> s;
      if (!has_lazy[i]) {
        continue;
      }

      const size_t len = static_cast<size_t>(1) << (s - 1);
      _apply(i << 1, lazy[i], len);
      _apply(i << 1 | 1, lazy[i], len);
      has_lazy[i] = false;
    }
  }

  auto _pull(size_t p) -> void {
    size_t len = 2;
    for (p >>= 1; p > 0; p >>= 1, len <<= 1) {
      if (has_lazy[p]) {
        tree[p] = lazy[p] * static_cast<Type>(len);
      } else {
        tree[p] = func(tree[p << 1], tree[p << 1 | 1]);
      }
    }
  }

public:
  explicit ZWKLazySegmentTree(const std::vector<Type> &data,
                                  Func f = Func{}, const Type &de = Type())
      : size(data.size()), default_val(de), func(f) {
    base = 1;
    height = 0;
    while (base < size) {
      base <<= 1;
      ++height;
    }

    tree.assign(base << 1, default_val);
    lazy.assign(base << 1, default_val);
    has_lazy.assign(base << 1, false);

    for (size_t i = 0; i < size; ++i) {
      tree[base + i] = data[i];
    }
    for (size_t i = base - 1; i > 0; --i) {
      tree[i] = func(tree[i << 1], tree[i << 1 | 1]);
    }
  }

  auto update_range(size_t l, size_t r, const Type &value) -> void {
    if (size == 0 || l > r || r >= size) {
      return;
    }

    size_t left = l + base;
    size_t right = r + base + 1;
    const size_t left_origin = left;
    const size_t right_origin = right;

    _push(left_origin);
    _push(right_origin - 1);

    size_t len = 1;
    while (left < right) {
      if (left & 1) {
        _apply(left++, value, len);
      }
      if (right & 1) {
        _apply(--right, value, len);
      }
      left >>= 1;
      right >>= 1;
      len <<= 1;
    }

    _pull(left_origin);
    _pull(right_origin - 1);
  }

  auto query_range(size_t l, size_t r) -> Type {
    if (size == 0 || l > r || r >= size) {
      return default_val;
    }

    size_t left = l + base;
    size_t right = r + base + 1;
    _push(left);
    _push(right - 1);

    Type left_res = default_val;
    Type right_res = default_val;
    while (left < right) {
      if (left & 1) {
        left_res = func(left_res, tree[left++]);
      }
      if (right & 1) {
        right_res = func(tree[--right], right_res);
      }
      left >>= 1;
      right >>= 1;
    }

    return func(left_res, right_res);
  }
};
```



#### 注意事项

1. **恒等元与累加**：如果是区间加法，懒标记累加；如果是区间修改（全部改成某个数），懒标记直接覆盖。
2. **标记对结果的影响**：对于区间求和，当前节点的 tree[node] 需要增加 lazy_val * (区间长度)。如果是区间求最大值，只需增加 lazy_val 即可。
3. **标记的顺序**：如果一个线段树同时有“区间加法”和“区间乘法”两种标记，下传的顺序非常重要（通常需要维护两个标记，并定义好先加后乘还是先乘后加的逻辑）
