# DSA Assignment #8: 🌲（3/3）

*Updated 2026-04-21 19:09 GMT+8*
 *Compiled by <mark>同学的姓名、院系</mark> (2026 Spring)*



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
/* BIT */
class NumArray {
private:
  vector<int> tree;
  vector<int> &nums;

  auto lowBit(int x) -> int { return x & -x; }

  void add(int index, int val) {
    while (index < tree.size()) {
      tree[index] += val;
      index += lowBit(index);
    }
  }

  auto prefixSum(int index) -> int {
    int sum = 0;
    while (index > 0) {
      sum += tree[index];
      index -= lowBit(index);
    }
    return sum;
  }

public:
  NumArray(vector<int> &nums) : tree(nums.size() + 1), nums(nums) {
    for (int i = 0; i < nums.size(); i++)
      add(i + 1, nums[i]);
  }

  void update(int index, int val) {
    add(index + 1, val - nums[index]);
    nums[index] = val;
  }

  auto sumRange(int left, int right) -> int {
    return prefixSum(right + 1) - prefixSum(left);
  }
};

/* SegmentTree */
template <typename Type, typename Func> class SegmentTree {
protected:
  size_t n;
  Func func;
  Type default_val;
  std::vector<Type> tree;

public:
  explicit SegmentTree(const std::vector<Type> &data, Func func = Func{},
                       const Type &de = Type())
      : n(data.size()), func(func), default_val(de) {}

  virtual auto update(size_t i, const Type &value) -> void = 0;
  virtual auto query(size_t l, size_t r) -> Type = 0;
  virtual ~SegmentTree() = default;
};

template <typename Type, typename Func>
class RecursiveSegmentTree : public SegmentTree<Type, Func> {
private:
  auto _build(const std::vector<Type> &data, size_t node, size_t start,
              size_t end) -> void {
    if (start == end) {
      this->tree[node] = data[start];
      return;
    }

    auto mid = start + ((end - start) >> 1);
    auto left = node << 1;
    auto right = node << 1 | 1;

    _build(data, left, start, mid);
    _build(data, right, mid + 1, end);

    this->tree[node] = this->func(this->tree[left], this->tree[right]);
  }

  auto _update(size_t node, size_t start, size_t end, size_t i,
               const Type &value) -> void {
    if (start == end) {
      this->tree[node] = value;
      return;
    }

    auto mid = start + ((end - start) >> 1);

    if (i <= mid) {
      _update(node << 1, start, mid, i, value);
    } else {
      _update(node << 1 | 1, mid + 1, end, i, value);
    }

    this->tree[node] =
        this->func(this->tree[node << 1], this->tree[node << 1 | 1]);
  }

  auto _query(size_t node, size_t start, size_t end, size_t l, size_t r)
      -> Type {
    if (l <= start && end <= r) {
      return this->tree[node];
    }
    auto mid = start + ((end - start) >> 1);
    if (r <= mid)
      return _query(node << 1, start, mid, l, r);
    if (l > mid)
      return _query(node << 1 | 1, mid + 1, end, l, r);

    return this->func(_query(node << 1, start, mid, l, r),
                      _query(node << 1 | 1, mid + 1, end, l, r));
  }

public:
  explicit RecursiveSegmentTree(const std::vector<Type> &data,
                                Func func = Func{}, const Type &de = Type())
      : SegmentTree<Type, Func>(data, func, de) {
    this->tree.assign(4 * this->n, this->default_val);
    _build(data, 1, 0, this->n - 1);
  }

  auto update(size_t i, const Type &value) -> void override {
    _update(1, 0, this->n - 1, i, value);
  }

  auto query(size_t l, size_t r) -> Type override {
    return _query(1, 0, this->n - 1, l, r);
  }
};

template <typename Type, typename Func>
class ZWKSegmentTree : public SegmentTree<Type, Func> {
public:
  explicit ZWKSegmentTree(const std::vector<Type> &data, Func func = Func{},
                          const Type &de = Type())
      : SegmentTree<Type, Func>(data, func, de) {
    this->tree.assign(2 * this->n, this->default_val);
    for (int i = 0; i < this->n; ++i) {
      this->tree[i + this->n] = data[i];
    }
    for (int i = this->n - 1; i > 0; --i) {
      this->tree[i] = this->func(this->tree[i << 1], this->tree[i << 1 | 1]);
    }
  }

  auto update(size_t i, const Type &value) -> void override {
    i += this->n;
    this->tree[i] = value;

    while (i > 1) {
      this->tree[i >> 1] = this->func(this->tree[i], this->tree[i ^ 1]);
      i >>= 1;
    }
  }

  auto query(size_t l, size_t r) -> Type override {
    Type res = this->default_val;
    l += this->n;
    r += this->n;

    while (l < r) {
      if (l & 1) {
        res = this->func(res, this->tree[l++]);
      }
      if (r & 1) {
        res = this->func(res, this->tree[--r]);
      }
      l >>= 1;
      r >>= 1;
    }
    return res;
  }
};
```



<mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260424132238000.png"/>



## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2026spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>





