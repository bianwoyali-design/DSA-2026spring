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
    /* Pay attention that in C++ std::priority_queue, the priority of the first param
     * is lower than the second. */
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

```python

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>





### M208.实现Trie（前缀树）

trie, https://leetcode.cn/problems/implement-trie-prefix-tree/

思路：



代码

```python

```



<mark>（至少包含有"Accepted"）</mark>





### M307.区域和检索 - 数组可修改

segment tree, https://leetcode.cn/problems/range-sum-query-mutable/

思路：



代码

```python

```



<mark>（至少包含有"Accepted"）</mark>





## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2026spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>





