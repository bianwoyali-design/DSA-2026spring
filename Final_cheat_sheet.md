---
cssclasses:
  - pdf-two-col
---

# Final Cheat Sheet
## 前缀和
### 二维前缀和
```cpp
class PrefixSum2D {
private:
  int m{}, n{};
  std::vector<std::vector<long long>> pre_sum;

public:
  explicit PrefixSum2D(const std::vector<std::vector<int>> &matrix) {
    m = static_cast<int>(matrix.size());
    n = m == 0 ? 0 : static_cast<int>(matrix[0].size());
    pre_sum.assign(m + 1, std::vector<long long>(n + 1, 0));
    for (int i = 1; i <= m; ++i)
      for (int j = 1; j <= n; ++j)
        pre_sum[i][j] = pre_sum[i - 1][j] + pre_sum[i][j - 1] -
                        pre_sum[i - 1][j - 1] + matrix[i - 1][j - 1];
  }

  auto query(int x1, int y1, int x2, int y2) -> long long {
    return pre_sum[x2 + 1][y2 + 1] - pre_sum[x1][y2 + 1] -
           pre_sum[x2 + 1][y1] + pre_sum[x1][y1];
  }
};
```
### 动态前缀和：BIT
```cpp
class Fenwick {
private:
  int n;
  std::vector<int> tree;
public:
  explicit Fenwick(int n) : n(n), tree(n + 1, 0) {}
  auto update(int i, int v) -> void {
    while (i <= n) {
      tree[i] += v; // 单点增加 v
      i += (i & -i);
    }
  }
  auto query(int i) -> int {
    int sum = 0;
    while (i > 0) {
      sum += tree[i]; // 查询前缀和[1, i]
      i &= i - 1;
    }
    return sum;
  }
};
```
### BIT 扫描方向
离散化后 `rank(x)` 是 1-index；BIT 维护已经扫过的数的出现次数。
```cpp
std::vector<int> sorted = nums;
std::sort(sorted.begin(), sorted.end());
sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
auto get_rank = [&](int value) {
  return static_cast<int>(std::lower_bound(sorted.begin(), sorted.end(), value) - sorted.begin()) + 1;
};
```
边界：`< x = query(r - 1)`，`<= x = query(r)`，`> x = seen - query(r)`，`>= x = seen - query(r - 1)`。
```cpp
Fenwick bit(static_cast<int>(sorted.size()));
long long ans = 0;
// 左 -> 右：统计左侧信息，如逆序对左边 > nums[i]
for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
  int r = get_rank(nums[i]);
  ans += i - bit.query(r);
  bit.update(r, 1);
}
// 右 -> 左：统计右侧信息，如逆序对右边 < nums[i]
bit = Fenwick(static_cast<int>(sorted.size()));
for (int i = static_cast<int>(nums.size()) - 1; i >= 0; --i) {
  int r = get_rank(nums[i]);
  ans += bit.query(r - 1);
  bit.update(r, 1);
}
```
康托展开排名从右往左扫：
```cpp
long long rank = 1;
for (int i = n - 1; i >= 0; --i) {
  int smaller_on_right = bit.query(permutation[i] - 1);
  rank = (rank + smaller_on_right * fact[n - 1 - i]) % MOD;
  bit.update(permutation[i], 1);
}
```

## 位运算 / 状态压缩
### 位运算速记
```cpp
bool has = (mask >> i) & 1;        // 第 i 位是否为 1
mask |= 1 << i;                    // 把第 i 位设为 1
mask &= ~(1 << i);                 // 把第 i 位清 0
mask ^= 1 << i;                    // 翻转第 i 位
int lowbit = x & -x;               // 最低位的 1
int count = std::popcount(mask);   // C++20，1 的个数
```
枚举集合 `mask` 的非空子集：
```cpp
for (int sub = mask; sub; sub = (sub - 1) & mask) {
  // sub 是 mask 的一个非空子集
}
```
若要包含空集：
```cpp
for (int sub = mask;; sub = (sub - 1) & mask) {
  // use sub
  if (sub == 0)
    break;
}
```

### 状态压缩 DP
适用：`n <= 20` 左右，状态用二进制集合表示。常见转移是“从小集合扩展到大集合”。

```cpp
const long long INF = 4e18;
std::vector dp(1 << n, std::vector<long long>(n, INF));
dp[1 << start][start] = 0;

for (int mask = 0; mask < (1 << n); ++mask) {
  for (int u = 0; u < n; ++u) {
    if (((mask >> u) & 1) == 0 || dp[mask][u] == INF)
      continue;
    for (int v = 0; v < n; ++v) {
      if ((mask >> v) & 1)
        continue;
      int next_mask = mask | (1 << v);
      dp[next_mask][v] = std::min(dp[next_mask][v], dp[mask][u] + cost[u][v]);
    }
  }
}
```

## 排序 / 分治
### 归并排序 + 逆序对
```cpp
std::vector<int> tmp(nums.size());
auto merge_sort = [&](auto &&self, int l, int r) -> long long {
  if (r - l <= 1) return 0;
  int m = l + ((r - l) >> 1);
  long long inv = self(self, l, m) + self(self, m, r);
  int i = l, j = m, k = l;
  while (i < m || j < r) {
    if (j == r || (i < m && nums[i] <= nums[j])) {
      tmp[k++] = nums[i++];
    } else {
      inv += m - i; // nums[i..m) 都 > nums[j]
      tmp[k++] = nums[j++];
    }
  }
  for (int p = l; p < r; ++p) nums[p] = tmp[p];
  return inv;
};
long long inversions = merge_sort(merge_sort, 0, static_cast<int>(nums.size()));
```

### 贪心速记
适用：局部选择不会破坏全局最优，常和排序、优先队列、交换论证搭配。

常见套路：
- 区间调度：按结束时间升序选，能选就选。
- 覆盖问题：在当前位置可选范围内，选能延伸最远的方案。
- 配对问题：排序后双指针，最小配最大或相邻配对。
- 反悔贪心：先接受选择，若超限制就用堆删掉代价最大或收益最小的选择。

```cpp
std::sort(intervals.begin(), intervals.end(),
          [](auto &a, auto &b) { return a.end < b.end; });

int count = 0;
int last_end = std::numeric_limits<int>::min();
for (auto [start, end] : intervals) {
  if (start >= last_end) {
    ++count;
    last_end = end;
  }
}
```

## 动态规划
### 背包
0/1 背包：每个物品最多选一次，容量从大到小扫。
```cpp
std::vector<long long> dp(capacity + 1, 0);
for (int i = 0; i < n; ++i)
  for (int c = capacity; c >= weight[i]; --c)
    dp[c] = std::max(dp[c], dp[c - weight[i]] + value[i]);
```
完全背包：每个物品可选多次，容量从小到大扫。
```cpp
std::vector<long long> dp(capacity + 1, 0);
for (int i = 0; i < n; ++i)
  for (int c = weight[i]; c <= capacity; ++c)
    dp[c] = std::max(dp[c], dp[c - weight[i]] + value[i]);
```

### LIS
`tails[len]` 表示长度为 `len + 1` 的上升子序列的最小结尾。
```cpp
std::vector<int> tails;
for (int x : nums) {
  auto it = std::lower_bound(tails.begin(), tails.end(), x);
  if (it == tails.end())
    tails.push_back(x);
  else
    *it = x;
}
int lis = static_cast<int>(tails.size());
```
严格上升用 `lower_bound`；非下降用 `upper_bound`。

### 网格 DP
```cpp
std::vector dp(m, std::vector<long long>(n, 0));
dp[0][0] = grid[0][0];
for (int i = 0; i < m; ++i) {
  for (int j = 0; j < n; ++j) {
    if (i > 0)
      dp[i][j] = std::max(dp[i][j], dp[i - 1][j] + grid[i][j]);
    if (j > 0)
      dp[i][j] = std::max(dp[i][j], dp[i][j - 1] + grid[i][j]);
  }
}
```

### 线性 DP / 滑动窗口 DP
线性 DP 通常只依赖前面若干状态：

```cpp
std::vector<long long> dp(n, 0);
dp[0] = base;
for (int i = 1; i < n; ++i) {
  dp[i] = std::max(dp[i - 1] + take[i], skip_value);
}
```

若转移形如 `dp[i] = sum(dp[j]), i - k <= j < i`，用前缀和维护窗口和：

```cpp
std::vector<long long> dp(n + 1, 0), prefix(n + 1, 0);
dp[0] = 1;
prefix[1] = 1;

for (int i = 1; i <= n; ++i) {
  int left = std::max(0, i - k);
  dp[i] = prefix[i] - prefix[left];
  prefix[i + 1] = prefix[i] + dp[i];
}
```

## Manacher / 马拉车
`d1[i]` 是以 `i` 为中心的奇回文半径，长度为 `2 * d1[i] - 1`；`d2[i]` 是以 `i - 1` 和 `i` 中间为中心的偶回文半径，长度为 `2 * d2[i]`。
```cpp
int n = static_cast<int>(s.size());
std::vector<int> d1(n), d2(n);
// 奇回文：中心是 i，初始半径至少为 1，即 s[i] 本身
for (int i = 0, l = 0, r = -1; i < n; ++i) {
  // [l, r] 是当前最靠右的回文区间，l + r - i 是 i 的镜像点
  int k = i > r ? 1 : std::min(d1[l + r - i], r - i + 1);
  while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) ++k;
  d1[i] = k;
  // 如果以 i 为中心的回文更靠右，就更新最右回文区间
  if (i + k - 1 > r) {
    l = i - k + 1;
    r = i + k - 1;
  }
}
// 偶回文：中心在 i - 1 和 i 中间，初始半径可以为 0
for (int i = 0, l = 0, r = -1; i < n; ++i) {
  int k = i > r ? 0 : std::min(d2[l + r - i + 1], r - i + 1);
  while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) ++k;
  d2[i] = k;
  if (i + k - 1 > r) {
    l = i - k;
    r = i + k - 1;
  }
}
int longest = 0;
for (int i = 0; i < n; ++i) {
  // 奇长度 = 2 * d1[i] - 1，偶长度 = 2 * d2[i]
  longest = std::max({longest, 2 * d1[i] - 1, 2 * d2[i]});
}
```
## KMP
### 字符串匹配
```cpp
auto compute_lps(const std::string &s) -> std::vector<int> {
  int n = static_cast<int>(s.length());
  std::vector<int> lps(n, 0);
  int length = 0;
  for (int i = 1; i < n; ++i) {
    while (length > 0 && s[i] != s[length])
      length = lps[length - 1];
    if (s[i] == s[length])
      ++length;
    lps[i] = length;
  }
  return lps;
} // 计算pattern字符串的LPS(最长前缀后缀)表
auto kmp_search(const std::string &text, const std::string &s) -> std::vector<int> {
  int n = static_cast<int>(text.length());
  int m = static_cast<int>(s.length());
  auto lps = compute_lps(s);
  std::vector<int> matches;
  int j = 0; // 模式串指针
  for (int i = 0; i < n; ++i) { // 主串指针
    while (j > 0 && text[i] != s[j])
      j = lps[j - 1];
    if (text[i] == s[j])
      ++j;
    if (j == m) {
      matches.emplace_back(i - j + 1);
      j = lps[j - 1];
    }
  } // 统计text中匹配的s的第1位指针
  return matches;
}
```

### 最小循环元引理
假设一个字符串的长度为 `L`（`1-based` 计数），其对应的 LPS 数组最后一位为 `lps[L-1]`。 若满足 $L\mod{(L - lps[L-1])} == 0$，则：
该字符串由一个长度为 ``d = L - lps[L-1]`` 的子串重复构成，该子串即为**最小循环元**，重复次数 ``K = L / d``。
## 调度场算法
中缀表达式求值：数字入 `nums`，运算符入 `ops`；遇到低优先级运算符前，先结算栈顶高/同优先级运算符。

```cpp
auto priority = [](char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
};
std::vector<long long> nums;
std::vector<char> ops;
auto apply = [&]() {
  long long b = nums.back(); nums.pop_back();
  long long a = nums.back(); nums.pop_back();
  char op = ops.back(); ops.pop_back();
  if (op == '+') nums.push_back(a + b);
  if (op == '-') nums.push_back(a - b);
  if (op == '*') nums.push_back(a * b);
  if (op == '/') nums.push_back(a / b);
};
bool need_num = true;
for (int i = 0; i < s.size();) {
  if (std::isspace(s[i])) {
    ++i;
  } else if (std::isdigit(s[i]) ||
             (need_num && (s[i] == '+' || s[i] == '-') &&
              i + 1 < s.size() && std::isdigit(s[i + 1]))) {
    int sign = 1;
    if (s[i] == '+' || s[i] == '-') sign = s[i++] == '-' ? -1 : 1;
    long long x = 0;
    while (i < s.size() && std::isdigit(s[i])) {
      x = x * 10 + s[i++] - '0';
    }
    nums.push_back(sign * x);
    need_num = false;
  } else if (s[i] == '(') {
    ops.push_back(s[i++]), need_num = true;
  } else if (s[i] == ')') {
    while (ops.back() != '(') apply();
    ops.pop_back(), ++i, need_num = false;
  } else {
    char op = s[i++];
    while (!ops.empty() && ops.back() != '(' &&
           priority(ops.back()) >= priority(op))
      apply();
    ops.push_back(op), need_num = true;
  }
}
while (!ops.empty()) apply();
long long ans = nums.back();
```
## 链表
### 反转链表
```cpp
auto reverseList(ListNode *head) -> ListNode * {
  ListNode *prev = nullptr;
  while (head) {
    auto next = head->next;
    head->next = prev;
    prev = head;
    head = next;
  }
  return prev;
}
```

### 快慢指针
找中点：循环结束后 `slow` 在中点；偶数长度时在右中点。
```cpp
auto middleNode(ListNode *head) -> ListNode * {
  auto slow = head;
  auto fast = head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}
```
判环并找入环点：
```cpp
auto detectCycle(ListNode *head) -> ListNode * {
  auto slow = head;
  auto fast = head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {
      auto ptr = head;
      while (ptr != slow) {
        ptr = ptr->next;
        slow = slow->next;
      }
      return ptr;
    }
  }
  return nullptr;
}
```
## Tree
### 树的读入和长子兄弟法
```cpp
struct TreeNode {
  char id;
  TreeNode *first_child{};
  TreeNode *next_sibling{};
  explicit TreeNode(char id) : id(id) {}
};
struct Node {
  char id;
  int degree;
};
auto buildTree(const std::vector<Node> &nodes) -> TreeNode * {
  if (nodes.empty())
    return nullptr;

  auto root = new TreeNode(nodes[0].id);
  std::queue<std::pair<TreeNode *, int>> q;
  q.emplace(root, nodes[0].degree);

  size_t i = 1;
  while (!q.empty() && i < nodes.size()) {
    auto [parent, degree] = q.front();
    q.pop();

    auto first_child = parent->first_child;
    auto prev_child = first_child;
    while (degree-- > 0 && i < nodes.size()) {
      auto child = new TreeNode(nodes[i].id);
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
```
### 嵌套括号树
```cpp
auto parseNode(const std::string &data, size_t &ptr) -> TreeNode * {
  if (ptr >= data.size())
    return nullptr;

  // 先读当前节点，如 A(B,C) 中的 A
  auto root = new TreeNode(data[ptr]);
  ++ptr;

  // 如果后面接 '('，说明当前节点有孩子列表
  if (ptr < data.size() && data[ptr] == '(') {
    ++ptr; // 跳过 '('
    TreeNode *prev = nullptr;

    // 逐个解析孩子，直到遇到 ')'；逗号只负责分隔兄弟
    while (ptr < data.size() && data[ptr] != ')') {
      auto child = parseNode(data, ptr);
      if (!root->first_child)
        root->first_child = child; // 第一个孩子挂到 first_child
      else
        prev->next_sibling = child; // 后续孩子接到上一个孩子的兄弟指针
      prev = child;
      if (ptr < data.size() && data[ptr] == ',')
        ++ptr; // 跳过 ','
    }
    if (ptr < data.size() && data[ptr] == ')')
      ++ptr; // 跳过 ')'
  }
  return root;
}
auto buildTree(const std::string &data) -> TreeNode * {
  if (data.empty())
    return nullptr;
  size_t ptr = 0;
  return parseNode(data, ptr);
}
```
如果题目给的是二叉树括号表示：`A(B,C)`，逗号左边是左子树，右边是右子树；空子树可写成 `A(,B)` 或 `A(B,)`。
```cpp
auto parseBinary(const std::string &s, size_t &pos) -> BinaryNode * {
  if (pos >= s.size() || s[pos] == ')' || s[pos] == ',')
    return nullptr;
  // 先读根节点，如 A(B,C) 中的 A
  auto root = new BinaryNode(s[pos++]);
  // 如果后面接括号，括号内最多两棵子树：left,right
  if (pos < s.size() && s[pos] == '(') {
    ++pos; // 跳过 '('
    if (pos < s.size() && s[pos] != ',')
      root->left = parseBinary(s, pos);
    if (pos < s.size() && s[pos] == ',')
      ++pos; // 跳过 ','
    if (pos < s.size() && s[pos] != ')')
      root->right = parseBinary(s, pos);
    if (pos < s.size() && s[pos] == ')')
      ++pos; // 跳过 ')'
  }
  return root;
}
```

### LCA 倍增法
预处理 `up[u][k]` 表示 `u` 的第 `2^k` 级祖先。查询时先把两个点提到同一深度，再一起向上跳。

```cpp
int LOG = 1;
while ((1 << LOG) <= n) ++LOG;

std::vector<int> depth(n + 1, 0);
std::vector up(n + 1, std::vector<int>(LOG, 0));

auto dfs = [&](auto &&self, int u, int parent) -> void {
  up[u][0] = parent;
  for (int k = 1; k < LOG; ++k)
    up[u][k] = up[up[u][k - 1]][k - 1];

  for (int v : tree[u]) {
    if (v == parent)
      continue;
    depth[v] = depth[u] + 1;
    self(self, v, u);
  }
};

auto lift = [&](int u, int step) {
  for (int k = 0; k < LOG; ++k)
    if ((step >> k) & 1)
      u = up[u][k];
  return u;
};

auto lca = [&](int u, int v) {
  if (depth[u] < depth[v])
    std::swap(u, v);
  u = lift(u, depth[u] - depth[v]);
  if (u == v)
    return u;

  for (int k = LOG - 1; k >= 0; --k) {
    if (up[u][k] != up[v][k]) {
      u = up[u][k];
      v = up[v][k];
    }
  }
  return up[u][0];
};

dfs(dfs, root, 0);
```

树上距离：

```cpp
int ancestor = lca(u, v);
int distance = depth[u] + depth[v] - 2 * depth[ancestor];
```

### DFS 序 / 子树区间
DFS 进入时间把树映射成数组，任意子树对应连续区间 `[tin[u], tout[u]]`。适用：子树加、子树和、统计子树内信息。

```cpp
std::vector<int> tin(n + 1), tout(n + 1);
int timer = 0;

auto dfs_order = [&](auto &&self, int u, int parent) -> void {
  tin[u] = ++timer;
  for (int v : tree[u]) {
    if (v == parent)
      continue;
    self(self, v, u);
  }
  tout[u] = timer;
};

dfs_order(dfs_order, root, 0);
// subtree(u) -> [tin[u], tout[u]]
```

映射关系：
- `tin[u]`：树上点 `u` 对应 DFS 序数组位置。
- `order[pos]`：DFS 序位置 `pos` 对应树上哪个点。
- `flat[tin[u]] = weight[u]`：把树上点权映射到数组。

```cpp
std::vector<int> order(n + 1);
std::vector<long long> flat(n + 1);

auto dfs_flatten = [&](auto &&self, int u, int parent) -> void {
  tin[u] = ++timer;
  order[timer] = u;
  flat[timer] = weight[u];

  for (int v : tree[u]) {
    if (v == parent)
      continue;
    self(self, v, u);
  }

  tout[u] = timer;
};
```

常用转换：单点 `u` 修改 -> 修改 `tin[u]`；查询或修改 `u` 的整棵子树 -> 区间 `[tin[u], tout[u]]`。

### 树上背包 DP
`dp[u][j]` 表示在 `u` 子树中选 `j` 个点的最优值。合并儿子时容量倒序，避免同一个儿子被重复用。

```cpp
const long long INF = 4e18;
std::vector dp(n + 1, std::vector<long long>(k + 1, -INF));
std::vector<int> size(n + 1, 0);

auto dfs_knapsack = [&](auto &&self, int u, int parent) -> void {
  dp[u][0] = 0;
  dp[u][1] = value[u];
  size[u] = 1;

  for (int v : tree[u]) {
    if (v == parent)
      continue;
    self(self, v, u);

    for (int i = std::min(size[u], k); i >= 0; --i) {
      for (int j = 1; j <= size[v] && i + j <= k; ++j) {
        dp[u][i + j] = std::max(dp[u][i + j], dp[u][i] + dp[v][j]);
      }
    }
    size[u] += size[v];
  }
};
```

### 卡特兰数
Catalan数 $𝐶_𝑛$ 的递推关系有着天然的递归结构：规模为 $𝑛$ 的计数问题 $𝐶_𝑛$ ，可以通过枚举分界点，分拆为两个规模分别为 $𝑖$ 和 $(𝑛−1-𝑖)$ 的子问题。这一递推关系使得Catalan数广泛出现于各类具有类似递归结构的问题中。
**路径计数问题**：有一个大小为 $n\times n$ 的方格图，左下角为 $(0,0)(0, 0)$，右上角为 $(𝑛,𝑛)(n, n)$ 。从左下角开始，每次都只能向右或者向上走一单位，不走到对角线 $y=x$ 上方（但可以触碰）的情况下，到达右上角的路径总数为 $C_n$ 。
**圆内不相交弦计数问题**：圆上有 $2n$ 个点，将这些点成对连接起来且使得所得到的 $n$ 条线段两两不交的方案数是 $C_n$。
**三角剖分计数问题**：对角线不相交的情况下，将一个凸 $(n + 2)$ 边形区域分成三角形区域的方法数为 $C_n$ 。
**二叉树计数问题**：含有 $n$ 个结点的形态不同的二叉树数目为 $C_n$ 。等价地，含有 $n$ 个非叶结点的形态不同的满二叉树数目为 $C_{n}$ 。
**括号序列计数问题**：由 $n$ 对括号构成的合法括号序列数为 $C_n$ 。
**出栈序列计数问题**：一个栈（无穷大）的进栈序列为 $1,2,3, \ldots ,n$ ，合法出栈序列的数目为 $C_n$ 。
**数列计数问题**：由 $n$ 个 $+1$ 和 $n$ 个 $-1$ 组成的数列 $a_1,a_2, \ldots ,a_{2n}$ 中，部分和满足 $a_1+a_2+ \ldots +a_k \geq 0~(k=1,2,3, \ldots ,2n)$ 的数列数目为 $C_n$ 。

$C_n = \frac{(4n - 2)}{n + 1} C_{n-1},\ n > 0,\ C_0 = 1.$
### Huffman Tree
```cpp
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
  std::priority_queue<TreeNode *, std::vector<TreeNode *>, CompareNode> pq;
  TreeNode *root{};
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
      auto node = new TreeNode('\0', left->freq + right->freq, left, right);
      pq.emplace(node);
    }
    root = pq.top();
    return root;
  }
};
```
### BST
二叉搜索树依赖于这样一个性质：小于父节点的键都在左子树中，大于父节点的键则都在右子树中。我们称这个性质为二叉搜索性。
```cpp
struct BSTNode {
  char value;
  BSTNode *left{};
  BSTNode *right{};
  explicit BSTNode(char value) : value(value) {}
};

class TreeUtils {
private:
  auto insertNode(BSTNode *root, char value) -> BSTNode * {
    if (!root)
      return new BSTNode(value);
    if (value < root->value)
      root->left = insertNode(root->left, value);
    else
      root->right = insertNode(root->right, value);
    return root;
  }
public:
  auto buildBST(const std::string &leaves) -> BSTNode * {
    if (leaves.empty())
      return nullptr;
    BSTNode *root = nullptr;
    for (int i = static_cast<int>(leaves.size()) - 1; i >= 0; --i)
      root = insertNode(root, leaves[i]);
    return root;
  }
};
```
### 字典树 (Trie)
```cpp
class Trie {
private:
  struct TrieNode {
    std::array<TrieNode *, 26> children{};
    int word_count = 0;
    uint32_t child_mask = 0;
  };

  TrieNode *root{};

  auto _erase_recursive(TrieNode *current, const std::string &word,
                        size_t index, bool &erased) -> bool {
    if (!current) {
      return false;
    }

    if (index == word.size()) {
      if (current->word_count == 0) {
        return false;
      }
      --current->word_count;
      erased = true;
      return current->word_count == 0 && !current->child_mask;
    }

    const int char_idx = word[index] - 'a';
    auto node = current->children[char_idx];

    if (!node) {
      return false;
    }

    if (_erase_recursive(node, word, index + 1, erased)) {
      delete node;
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
    bool erased = false;
    _erase_recursive(root, word, 0, erased);
    return erased;
  }
};
```
- 例：LC 421.数组中两个数的最大异或值
```cpp
class Solution {
  struct TrieNode {
    TrieNode *left{};
    TrieNode *right{};
    TrieNode() = default;
  };

  TrieNode *root = new TrieNode();
  constexpr static int HIGH_BIT = 30;

  auto add(int num) -> void {
    auto curr = root;
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
    auto curr = root;
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
```
### 并查集
#### 模板
```cpp
class DisjSet {
private:
  std::vector<int> parent;
  std::vector<int> rank;

public:
  explicit DisjSet(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  auto find(int x) -> int {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
  }

  auto unite(int x, int y) -> bool {
    int root_x = find(x);
    int root_y = find(y);

    if (root_x == root_y) {
      return false;
    }

    if (rank[root_x] > rank[root_y]) {
      parent[root_y] = root_x;
    } else if (rank[root_x] < rank[root_y]) {
      parent[root_x] = root_y;
    } else {
      parent[root_y] = root_x;
      ++rank[root_x];
    }
    return true;
  }
};
```
#### 扩展并查集
```cpp
DisjSet dsu(3 * n);
auto self = [&](int x) { return x; };
auto eat = [&](int x) { return x + n; };
auto eaten = [&](int x) { return x + 2 * n; };

// x 与 y 同类
if (dsu.find(eat(x)) == dsu.find(self(y)) ||
    dsu.find(self(x)) == dsu.find(eat(y))) {
  // 矛盾
} else {
  dsu.unite(self(x), self(y));
  dsu.unite(eat(x), eat(y));
  dsu.unite(eaten(x), eaten(y));
}

// x 吃 y
if (dsu.find(self(x)) == dsu.find(self(y)) ||
    dsu.find(eaten(x)) == dsu.find(self(y))) {
  // 矛盾
} else {
  dsu.unite(eat(x), self(y));
  dsu.unite(self(x), eaten(y));
  dsu.unite(eaten(x), eat(y));
}
```
扩展并查集应用：
- 三倍域：`x`、`x + n`、`x + 2n` 分别表示不同关系类。常用于食物链：同类、捕食、被捕食。
- 二倍域：`x` 和 `x + n` 表示相反关系。常用于敌友关系、二分图染色、奇偶约束。
- 带权并查集：维护 `dist[x] = x 到 parent[x] 的关系值`，适合关系可以用模数表示的题。

#### 带权并查集
`dist[x]` 表示 `x` 到根的关系值，关系在 `mod` 下运算。若要加入约束 `x - y = w (mod mod)`：
```cpp
class WeightedDSU {
private:
  int mod;
  std::vector<int> parent, dist; // dist[x]: x 到 parent[x] 的关系

public:
  explicit WeightedDSU(int n, int mod) : mod(mod), parent(n), dist(n, 0) {
    std::iota(parent.begin(), parent.end(), 0);
  }

  auto find(int x) -> int {
    if (parent[x] == x)
      return x;
    int old_parent = parent[x];
    parent[x] = find(parent[x]);
    dist[x] = (dist[x] + dist[old_parent]) % mod;
    return parent[x];
  }

  auto unite(int x, int y, int w) -> bool {
    int root_x = find(x), root_y = find(y);
    if (root_x == root_y)
      return ((dist[x] - dist[y] - w) % mod + mod) % mod == 0;

    parent[root_x] = root_y;
    dist[root_x] = ((w + dist[y] - dist[x]) % mod + mod) % mod;
    return true;
  }
};
```
应用换算：
- 奇偶/二分关系：`mod = 2`，同色 `w = 0`，异色 `w = 1`。
- 食物链：`mod = 3`，同类 `w = 0`，`x` 吃 `y` 可设 `w = 1`，`x` 被 `y` 吃可设 `w = 2`。
- 距离差约束：不用取模时，把 `% mod` 去掉，`dist` 用 `long long`。

### 线段树
#### 模板
```cpp
class SegTree {
private:
  int n;
  const int default_val = 0;
  std::vector<int> tree;

public:
  SegTree(const std::vector<int> &data)
      : n(data.size()), tree(2 * n, 0) {
    for (int i = 0; i < n; ++i) {
      tree[i + n] = data[i];
    }
    for (int i = n - 1; i > 0; --i) {
      tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }
  }

  auto update(int i, int value) -> void {
    i += n;
    tree[i] = value;

    while (i > 1) {
      tree[i >> 1] = tree[i] + tree[i ^ 1];
      i >>= 1;
    }
  }

  auto sumRange(int l, int r) -> int {
    int res = default_val;
    l += n;
    r += n + 1;

    while (l < r) {
      if (l & 1) {
        res = res + tree[l++];
      }
      if (r & 1) {
        res = res + tree[--r];
      }
      l >>= 1;
      r >>= 1;
    }
    return res;
  }
};
```
#### 区间开闭和自定义点

递归线段树：
- 对外接口：通常传 0-index 闭区间 `[l, r]`。
- 节点区间：`[start, end]`，也是闭区间。
- 分裂方式：左儿子 `[start, mid]`，右儿子 `[mid + 1, end]`。
- 判断覆盖：`l <= start && end <= r`。
- 判断进左儿子：`l <= mid`；判断进右儿子：`r > mid`。
- 如果题目输入是 1-index `[l, r]`，调用时改成 `[l - 1, r - 1]`。

zkw / 迭代线段树：
- 对外接口：也可以设计成 0-index 闭区间 `[l, r]`。
- 内部会转成半开区间 `[left, right)`：
  ```cpp
  size_t left = l + base;
  size_t right = r + base + 1;
  while (left < right) { ... }
  ```
- 如果本来就想传半开区间 `[l, r)`，则写成 `right = r + base`。

可自定义的地方：
- `Type`：节点值和懒标记类型，可能要用 `long long`。
- `func`：左右儿子的合并方式，如 `sum / max / min / gcd`。
- `query_default`：查询单位元。`sum = 0`，`max = -inf`，`min = +inf`。
- `lazy_default`：空懒标记。区间加法通常是 `0`。
- `_apply`：整段更新如何影响 `tree[p]` 和 `lazy[p]`。
- `_push`：父节点懒标记如何下传给左右儿子。
- `_pull`：子节点变化后，如何重新计算父节点。

常见 `_apply`：
```cpp
// 区间加 + 区间最大值：最大值整体加 value，不需要 len
tree[p] += value;
lazy[p] += value;

// 区间加 + 区间和：整段和增加 value * len
tree[p] += value * len;
lazy[p] += value;

// 区间赋值 + 区间和：懒标记是覆盖，不是累加
tree[p] = value * len;
lazy[p] = value;
has_lazy[p] = true;
```

#### 区间加法+最大值查询 懒标记线段树
递归版，接口是 0-index 闭区间 `[l, r]`。

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
      const auto left = node << 1;
      const auto right = node << 1 | 1;

      lazy[left] += lazy[node];
      has_lazy[left] = true;
      tree[left] += lazy[node];

      lazy[right] += lazy[node];
      has_lazy[right] = true;
      tree[right] += lazy[node];

      lazy[node] = default_val;
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
      lazy[node] += value;
      has_lazy[node] = true;
      tree[node] += value;
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

zkw 版，接口是 0-index 闭区间 `[l, r]`，内部转成半开区间 `[l + base, r + base + 1)`。

```cpp
template <typename Type, typename Func> class SegTree {
private:
  size_t size;
  size_t base;
  size_t height;
  Type query_default;
  Type lazy_default;
  Func func;
  std::vector<Type> tree;
  std::vector<Type> lazy;
  std::vector<bool> has_lazy;

  auto _apply(size_t p, const Type &value) -> void {
    tree[p] += value;
    if (p < base) {
      lazy[p] += value;
      has_lazy[p] = true;
    }
  }

  auto _push(size_t p) -> void {
    for (size_t s = height; s > 0; --s) {
      const size_t i = p >> s;
      if (!has_lazy[i]) {
        continue;
      }

      _apply(i << 1, lazy[i]);
      _apply(i << 1 | 1, lazy[i]);
      lazy[i] = lazy_default;
      has_lazy[i] = false;
    }
  }

  auto _pull(size_t p) -> void {
    for (p >>= 1; p > 0; p >>= 1) {
      tree[p] = func(tree[p << 1], tree[p << 1 | 1]);
      if (has_lazy[p]) {
        tree[p] += lazy[p];
      }
    }
  }

public:
  explicit SegTree(const std::vector<Type> &data, Func f = Func{},
                   const Type &query_de = Type(),
                   const Type &lazy_de = Type())
      : size(data.size()), query_default(query_de), lazy_default(lazy_de),
        func(f) {
    base = 1;
    height = 0;
    while (base < size) {
      base <<= 1;
      ++height;
    }

    tree.assign(base << 1, query_default);
    lazy.assign(base << 1, lazy_default);
    has_lazy.assign(base << 1, false);

    for (size_t i = 0; i < size; ++i) {
      tree[base + i] = data[i];
    }
    for (size_t i = base - 1; i > 0; --i) {
      tree[i] = func(tree[i << 1], tree[i << 1 | 1]);
    }
  }

  auto add_range(size_t l, size_t r, const Type &value) -> void {
    if (size == 0 || l > r || r >= size) {
      return;
    }

    size_t left = l + base;
    size_t right = r + base + 1;
    const size_t left_origin = left;
    const size_t right_origin = right;

    _push(left_origin);
    _push(right_origin - 1);

    while (left < right) {
      if (left & 1) {
        _apply(left++, value);
      }
      if (right & 1) {
        _apply(--right, value);
      }
      left >>= 1;
      right >>= 1;
    }

    _pull(left_origin);
    _pull(right_origin - 1);
  }

  auto query_range(size_t l, size_t r) -> Type {
    if (size == 0 || l > r || r >= size) {
      return query_default;
    }

    size_t left = l + base;
    size_t right = r + base + 1;
    _push(left);
    _push(right - 1);

    auto left_res = query_default;
    auto right_res = query_default;
    while (left < right) {
      if (left & 1) {
        left_res = func(left_res, tree[left++]);
      }
      if (right & 1) {
        right_res = func(right_res, tree[--right]);
      }
      left >>= 1;
      right >>= 1;
    }

    return func(left_res, right_res);
  }
};

```

## Graph
### 补图连通块
适用：给出一批“禁止边/权值为 1 的边”，需要在补图中找连通块。维护未访问集合；从点 `u` 扩展时，所有未访问且不是 `u` 原图邻居的点，都是补图邻居。

```cpp
std::vector<std::unordered_set<int>> edge(n + 1);
for (auto [u, v] : edges) {
  edge[u].insert(v);
  edge[v].insert(u);
}

std::set<int> unvisited;
for (int i = 1; i <= n; ++i)
  unvisited.insert(i);

int component_count = 0;
std::queue<int> q;
while (!unvisited.empty()) {
  ++component_count;
  int start = *unvisited.begin();
  unvisited.erase(start);
  q.push(start);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto it = unvisited.begin(); it != unvisited.end();) {
      int v = *it;
      if (!edge[u].contains(v)) {
        it = unvisited.erase(it);
        q.push(v);
      } else {
        ++it;
      }
    }
  }
}
```

0/1 完全图 MST：输入边权为 `1`，未输入边权为 `0`。答案为 `补图连通块数 - 1`。

### BFS 通配符桶优化
适用：单词接龙 / 只改一个字符的最短路。把单词按通配符模式分桶，如 `fool` 放入 `_ool, f_ol, fo_l, foo_`，同桶单词两两只差一个字符。

```cpp
int n = static_cast<int>(words.size());
int len = static_cast<int>(words[0].size());
std::unordered_map<std::string, std::vector<int>> bucket;

for (int i = 0; i < n; ++i) {
  for (int p = 0; p < len; ++p) {
    std::string key = words[i];
    key[p] = '_';
    bucket[key].push_back(i);
  }
}

std::vector<int> dist(n, -1);
std::queue<int> q;
dist[start] = 0;
q.push(start);

while (!q.empty()) {
  int u = q.front();
  q.pop();

  for (int p = 0; p < len; ++p) {
    std::string key = words[u];
    key[p] = '_';

    for (int v : bucket[key]) {
      if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
    bucket[key].clear(); // 这个桶以后不用重复扫
  }
}
```

复杂度：建桶 `O(n * len)` 个键；BFS 时每个桶最多展开一次，比暴力枚举两两比较 `O(n^2 * len)` 快很多。

### 二分图染色 / 奇偶约束
无向图二分图判定：相邻点颜色必须不同。若遇到同色边，说明不是二分图。
```cpp
std::vector<int> color(n, -1);
bool ok = true;
for (int s = 0; s < n && ok; ++s) {
  if (color[s] != -1)
    continue;

  std::queue<int> q;
  color[s] = 0;
  q.push(s);

  while (!q.empty() && ok) {
    int u = q.front();
    q.pop();
    for (int v : adj[u]) {
      if (color[v] == -1) {
        color[v] = color[u] ^ 1;
        q.push(v);
      } else if (color[v] == color[u]) {
        ok = false;
        break;
      }
    }
  }
}
```
带奇偶关系的动态合并通常用带权并查集，维护 `dist[x]` 到根的奇偶值。

### DFS Warnsdorff 启发式
适用：骑士巡游、网格 DFS、精确覆盖类搜索。原则是：下一步优先走“后续可走选择最少”的点，尽早发现死路。

```cpp
std::vector<std::pair<int, int>> moves = {
    {1, 2}, {2, 1}, {-1, 2}, {-2, 1},
    {1, -2}, {2, -1}, {-1, -2}, {-2, -1}};

auto inside = [&](int x, int y) {
  return 0 <= x && x < n && 0 <= y && y < m;
};

auto degree = [&](int x, int y) {
  int cnt = 0;
  for (auto [dx, dy] : moves) {
    int nx = x + dx, ny = y + dy;
    if (inside(nx, ny) && !visited[nx][ny])
      ++cnt;
  }
  return cnt;
};

auto dfs = [&](auto &&self, int x, int y, int step) -> bool {
  if (step == n * m)
    return true;

  std::vector<std::tuple<int, int, int>> next;
  for (auto [dx, dy] : moves) {
    int nx = x + dx, ny = y + dy;
    if (inside(nx, ny) && !visited[nx][ny])
      next.emplace_back(degree(nx, ny), nx, ny);
  }
  std::sort(next.begin(), next.end()); // 可走出路少的先搜

  return std::any_of(next.begin(), next.end(), [&](auto item) {
    auto [deg, nx, ny] = item;
    visited[nx][ny] = true;
    path.emplace_back(nx, ny);
    if (self(self, nx, ny, step + 1))
      return true;
    path.pop_back();
    visited[nx][ny] = false;
    return false;
  });
};
```

### 拓扑排序
#### Kahn 算法
数据以邻接表储存，输出为拓扑序。
```cpp
auto topo_sort_kahn(int n, const std::vector<std::vector<int>> &adj)
    -> std::vector<int> {
  std::vector<int> indegree(n, 0);
  for (int u = 0; u < n; ++u)
    for (auto v : adj[u])
      ++indegree[v];
  std::queue<int> q;
  for (int i = 0; i < n; ++i)
    if (!indegree[i])
      q.emplace(i);
  std::vector<int> topo_order;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    topo_order.emplace_back(u);
    for (auto v : adj[u]) {
      --indegree[v];
      if (!indegree[v])
        q.emplace(v);
    }
  }
  return topo_order; // 若 topo_order.size() != n 说明有环
}
```
#### DFS 拓扑排序
原始输出为逆拓扑序，需要`reverse`。
```cpp
auto dfs_topo_sort(const std::vector<std::vector<int>> &adj) {
  int n = static_cast<int>(adj.size());
  std::vector<int> visited(n, false);
  std::vector<int> finish_order;
  auto dfs_visit = [&](this auto &&self, int u) -> bool {
    visited[u] = 1;
    for (auto v : adj[u]) {
      if (visited[v] == 0) {
        if (!self(v))
          return false;
      } else if (visited[v] == 1) {
        return false;
      }
    }
    visited[u] = 2;
    finish_order.emplace_back(u);
    return true;
  };
  for (int u = 0; u < n; ++u) {
    if (visited[u] == 0) {
      if (!dfs_visit(u))
        return {};
    }
  }
  std::ranges::reverse(finish_order);
  return finish_order;
}
```
### 环检测
#### 无向图判环
##### 并查集
在函数`unite()`中判断：
```cpp
auto unite(int x, int y) -> bool {
  int root_x = find(x);
  int root_y = find(y);
  if (root_x == root_y)
    return false; // 有环
  if (rank[root_x] < rank[root_y])
    parent[root_x] = root_y;
  else if (rank[root_x] > rank[root_y])
    parent[root_y] = root_x;
  else {
    parent[root_y] = root_x;
    ++rank[root_x];
  }
  return true;
}
```
存图时用边表示无向图：
```cpp
DisjSet dsu(n);
for (auto [u, v] : edges)
  if (!dsu.unite(u, v))
    return false;
```
##### DFS (parent 指针)
```cpp
auto has_cycle(int n, const std::vector<std::vector<int>> &adj) {
  std::vector<bool> visited(n, false);
  auto dfs = [&](this auto &&self, int node, int parent) {
    visited[node] = true;
    for (auto v : adj[node]) {
      if (!visited[v]) {
        if (self(v, node))
          return true; // 有环
      } else if (v != parent) {
        return true;
      }
    }
    return false;
  };
  for (int u = 0; u < n; ++u)
    if (!visited[u] && dfs(u, -1))
      return true;
  return false;
}
```
#### 有向图判环
见[拓扑排序](#拓扑排序).
### 无向图 Tarjan
Tarjan 可用于无向图求桥、割点、边双连通分量、点双连通分量。核心仍是 `dfn/low`，但判定条件和 SCC 不同。

- 桥：`low[v] > dfn[u]`，是边双连通分量分界线
- 割点：非根节点满足 `low[v] >= dfn[u]`；根节点有至少两个 DFS 儿子，是点双连通分量分界线
- 有重边时必须用边编号跳过父边，不能只判断 `v == parent`

```cpp
struct Edge {
  int to;
  int id;
};

std::vector<std::vector<Edge>> adj(n);
for (int id = 0; id < m; ++id) {
  int u, v;
  std::cin >> u >> v;
  adj[u].push_back({v, id});
  adj[v].push_back({u, id});
}

std::vector<int> dfn(n, -1), low(n), is_cut(n, false);
std::vector<std::pair<int, int>> bridges;
int timer = 0;

auto dfs = [&](auto &&self, int u, int parent_edge) -> void {
  dfn[u] = low[u] = timer++;
  int child_count = 0;
  for (auto [v, edge_id] : adj[u]) {
    if (edge_id == parent_edge)
      continue;
    if (dfn[v] == -1) {
      ++child_count;
      self(self, v, edge_id);
      low[u] = std::min(low[u], low[v]);
      if (low[v] > dfn[u])
        bridges.push_back({u, v});
      if (parent_edge != -1 && low[v] >= dfn[u])
        is_cut[u] = true;
    } else {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
  if (parent_edge == -1 && child_count >= 2)
    is_cut[u] = true;
};

for (int u = 0; u < n; ++u)
  if (dfn[u] == -1)
    dfs(dfs, u, -1);
```
### 强连通分量（SCC）
#### Tarjan 算法
```cpp
auto tarjan(const std::vector<std::vector<int>> &adj) {
  int n = adj.size();
  int timer = 0;
  std::vector<int> dfn(n, -1);
  std::vector<int> low(n, -1);
  std::vector<int> stack{};
  std::vector<bool> on_stack(n, false);
  std::vector<std::vector<int>> sccs;
  auto dfs = [&](auto &&self, int u) -> void {
    dfn[u] = low[u] = timer++;
    stack.emplace_back(u);
    on_stack[u] = true;
    for (auto v : adj[u]) {
      if (dfn[v] == -1) {
        self(self, v);
        low[u] = std::min(low[u], low[v]);
      } else if (on_stack[v]) {
        low[u] = std::min(low[u], dfn[v]);
      }
    }
    if (low[u] == dfn[u]) {
      std::vector<int> component;
      while (true) {
        int node = stack.back();
        stack.pop_back();
        component.emplace_back(node);
        on_stack[node] = false;
        if (node == u) break;
      }
      sccs.emplace_back(component);
    }
  };
  for (int i = 0; i < n; ++i)
    if (dfn[i] == -1) dfs(dfs, i);
  return sccs;
}
```
#### 缩点算法
`comp[u]` 表示点 `u` 属于哪个强连通分量。每个 SCC 缩成一个点后，原图变成 DAG。

```cpp
std::vector<int> dfn(n, -1), low(n), stk, comp(n, -1);
std::vector<bool> in_stack(n, false);
int timer = 0, comp_count = 0;
auto dfs = [&](auto &&self, int u) -> void {
  dfn[u] = low[u] = timer++;
  stk.push_back(u);
  in_stack[u] = true;
  for (int v : g[u]) {
    if (dfn[v] == -1) {
      self(self, v);
      low[u] = std::min(low[u], low[v]);
    } else if (in_stack[v]) {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    while (true) {
      int x = stk.back();
      stk.pop_back();
      in_stack[x] = false;
      comp[x] = comp_count;
      if (x == u)
        break;
    }
    ++comp_count;
  }
};
for (int i = 0; i < n; ++i)
  if (dfn[i] == -1)
    dfs(dfs, i);
```
建缩点图：
```cpp
std::vector<std::vector<int>> dag(comp_count);
std::vector<int> indegree(comp_count, 0);

for (int u = 0; u < n; ++u) {
  for (int v : g[u]) {
    int cu = comp[u], cv = comp[v];
    if (cu == cv)
      continue;
    dag[cu].push_back(cv);
  }
}

// 去重，否则入度、DP 可能被重边影响
for (int u = 0; u < comp_count; ++u) {
  std::sort(dag[u].begin(), dag[u].end());
  dag[u].erase(std::unique(dag[u].begin(), dag[u].end()), dag[u].end());
  for (int v : dag[u])
    ++indegree[v];
}
```
如果点有权值，缩点时汇总 SCC 权值：
```cpp
std::vector<long long> comp_weight(comp_count, 0);
for (int u = 0; u < n; ++u) {
  comp_weight[comp[u]] += weight[u];
}
```

缩点 DAG DP：有边 `u -> v` 时，`u` 的答案可由 `v` 更新。先求拓扑序，再反向转移。

```cpp
std::queue<int> q;
std::vector<int> topo;
for (int i = 0; i < comp_count; ++i)
  if (indegree[i] == 0)
    q.push(i);

while (!q.empty()) {
  int u = q.front();
  q.pop();
  topo.push_back(u);
  for (int v : dag[u])
    if (--indegree[v] == 0)
      q.push(v);
}

std::vector<int> dp(comp_count);
for (int c = 0; c < comp_count; ++c)
  dp[c] = comp_min_id[c]; // 或 comp_weight[c] 等 SCC 自身信息

for (int i = static_cast<int>(topo.size()) - 1; i >= 0; --i) {
  int u = topo[i];
  for (int v : dag[u])
    dp[u] = std::min(dp[u], dp[v]);
}
```

### 欧拉路径 Hierholzer
适用：每条边恰好走一次。无向图要求奇度点为 `0` 或 `2` 个；有向图要求出入度差符合起终点条件，并且相关点连通。

有向图模板，`adj[u]` 存边的终点，边会被弹出：
```cpp
std::vector<std::vector<int>> adj(n);
std::vector<int> path;

auto dfs = [&](this auto &&self, int u) -> void {
  while (!adj[u].empty()) {
    int v = adj[u].back();
    adj[u].pop_back();
    self(v);
  }
  path.push_back(u);
};

dfs(start);
std::ranges::reverse(path); // path.size() == edge_count + 1 才用完所有边
```
字符串接龙 / Catenyms 类题常把单词看成边，首字母到尾字母建有向边；输出边时需要同时保存边编号或单词。

### 最短路问题
#### Dijkstra （非负权单源最短路）
```cpp
auto dijkstra(int n, const std::vector<std::vector<std::pair<int, int>>> &adj,
              int start) {
  const long long INF = 4e18;
  std::vector<long long> dist(n, INF);
  dist[start] = 0;
  std::priority_queue<std::pair<long long, int>,
                      std::vector<std::pair<long long, int>>,
                      std::greater<>> pq;
  pq.emplace(0, start);
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (d > dist[u]) continue;
    for (auto [v, weight] : adj[u])
      if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.emplace(dist[v], v);
      }
  }
  return dist;
}
```
#### Dijkstra 变形差异
只改状态、初值、转移和堆方向；其余框架沿用 Dijkstra。

```cpp
// 同余最短路：dist[r] 是能达到余数 r 的最小值
int mod = static_cast<int>(*std::min_element(step.begin(), step.end()));
std::vector<long long> dist(mod, INF);
dist[0] = 0; // 若从 base 开始：dist[base % mod] = base
for (long long w : step) {
  int v = static_cast<int>((u + w) % mod);
  relax_min(v, du + w);
}
bool ok = dist[target % mod] <= target;

// 统计 [0, limit] 内可达数
if (dist[r] <= limit)
  ans += (limit - dist[r]) / mod + 1;
```

```cpp
// 最小瓶颈路：最小化路径最大边权，海拔差/最小体力
long long next = std::max(dist[u], w);
if (next < dist[v])
  relax_min(v, next);

// 最大瓶颈路：最大化路径最小边权，货车限重/最大带宽
dist[start] = INF;              // 其他点初值 -1
long long next = std::min(dist[u], w);
if (next > dist[v])
  relax_max(v, next);           // 用大根堆
```

```cpp
// 最大概率路：最大化边概率乘积
prob[start] = 1;                // 其他点初值 0
double next = prob[u] * p;
if (next > prob[v])
  relax_max(v, next);           // 用大根堆

// 状态/分层图：最多用一次道具、剩余次数、钥匙状态等
std::vector dist(n, std::array<long long, 2>{INF, INF});
// 状态为 (du, u, used)
if (!special)
  relax_min({v, used}, du + w);
else if (used == 0)
  relax_min({v, 1}, du + w);
```

最小瓶颈路也可二分答案 + BFS，或 Kruskal 按边权从小到大加边；最大瓶颈路也可用最大生成树 + LCA 查询路径最小边。

#### Bellman-Ford （有负权单源最短路）
适用：有负权边、判断负环、差分约束、限制边数的最短路。复杂度 `O(nm)`。

```cpp
struct Edge {
  int from, to;
  long long weight;
};

const long long INF = 4e18;
std::vector<long long> dist(n + 1, INF);
dist[start] = 0;

for (int i = 1; i <= n - 1; ++i) {
  bool relaxed = false;
  for (auto [u, v, w] : edges) {
    if (dist[u] != INF && dist[v] > dist[u] + w) {
      dist[v] = dist[u] + w;
      relaxed = true;
    }
  }
  if (!relaxed)
    break;
}
```

判断从 `start` 可达的负环：

```cpp
bool has_negative_cycle = false;
for (auto [u, v, w] : edges) {
  if (dist[u] != INF && dist[v] > dist[u] + w) {
    has_negative_cycle = true;
    break;
  }
}
```

最多经过 `k` 条边的最短路：每一轮必须用上一轮的备份，避免同一轮连续松弛多条边。

```cpp
std::vector<long long> dist(n + 1, INF);
dist[start] = 0;

for (int step = 1; step <= k; ++step) {
  auto prev = dist;
  for (auto [u, v, w] : edges) {
    if (prev[u] != INF)
      dist[v] = std::min(dist[v], prev[u] + w);
  }
}
```

差分约束：
- `x_v <= x_u + w` 建边 `u -> v, w`
- 求一组可行解：加超级源 `0`，向所有点连 `0` 权边，再跑 Bellman-Ford
- 若存在负环，则约束无解

```cpp
for (int i = 1; i <= n; ++i)
  edges.push_back({0, i, 0});
dist.assign(n + 1, INF);
dist[0] = 0;
// 跑 Bellman-Ford；若还能松弛，说明差分约束无解
```

#### SPFA
Bellman-Ford 的队列优化版。只把被更新的点入队，再用它继续松弛出边。最坏仍是 `O(nm)`，但稀疏图/差分约束中常用。SLF 优化：如果新点距离比队首更小，就放到队首。

```cpp
const long long INF = 4e18;
std::vector<long long> dist(n + 1, INF);
std::vector<bool> in_queue(n + 1, false);
std::vector<int> count(n + 1, 0);
std::deque<int> q;

dist[start] = 0;
q.push(start);
in_queue[start] = true;
count[start] = 1;

bool has_negative_cycle = false;
while (!q.empty() && !has_negative_cycle) {
  int u = q.front();
  q.pop();
  in_queue[u] = false;

  for (auto [v, w] : adj[u]) {
    if (dist[u] != INF && dist[v] > dist[u] + w) {
      dist[v] = dist[u] + w;
      if (!in_queue[v]) {
        if (!q.empty() && dist[v] < dist[q.front()])
          q.push_front(v);
        else
          q.push_back(v);
        in_queue[v] = true;
        if (++count[v] > n) {
          has_negative_cycle = true;
          break;
        }
      }
    }
  }
}
```

差分约束要检查全图负环时，加超级源后从 `0` 开始跑；或者一开始把所有点都入队：

```cpp
for (int i = 1; i <= n; ++i) {
  dist[i] = 0;
  q.push_back(i);
  in_queue[i] = true;
}
```

#### Floyd-Warshall（全源最短路）
适用：点数较小的全源最短路，复杂度 `O(n^3)`。通常用 0-based 或 1-based 都可以，下面是 1-based。

```cpp
const long long INF = 4e18;
std::vector dist(n + 1, std::vector<long long>(n + 1, INF));

for (int i = 1; i <= n; ++i)
  dist[i][i] = 0;
for (auto [u, v, w] : edges)
  dist[u][v] = std::min(dist[u][v], w); // 无向图再加 dist[v][u]

for (int k = 1; k <= n; ++k)
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (dist[i][k] != INF && dist[k][j] != INF)
        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
```

路径恢复：

```cpp
std::vector next(n + 1, std::vector<int>(n + 1, -1));
for (int i = 1; i <= n; ++i)
  next[i][i] = i;
for (auto [u, v, w] : edges) {
  if (w < dist[u][v]) {
    dist[u][v] = w;
    next[u][v] = v;
  }
}

for (int k = 1; k <= n; ++k)
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (dist[i][k] != INF && dist[k][j] != INF &&
          dist[i][j] > dist[i][k] + dist[k][j]) {
        dist[i][j] = dist[i][k] + dist[k][j];
        next[i][j] = next[i][k];
      }

std::vector<int> path;
for (int u = start; u != target; u = next[u][target])
  path.push_back(u);
path.push_back(target);
```

传递闭包：判断任意两点是否可达。

```cpp
std::vector reachable(n + 1, std::vector<bool>(n + 1, false));
for (int i = 1; i <= n; ++i)
  reachable[i][i] = true;
for (auto [u, v] : edges)
  reachable[u][v] = true;

for (int k = 1; k <= n; ++k)
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      reachable[i][j] = reachable[i][j] || (reachable[i][k] && reachable[k][j]);
```

### 最小生成树（MST）
选型：
- 边集输入、稀疏图：Kruskal，`O(m log m)`，最好写。
- 邻接矩阵、完全图、稠密图：朴素 Prim，`O(n^2)`。
- 邻接表且边较多但不稠密：堆优化 Prim，`O(m log m)`。

应用：
- 城市/网络/道路最小连接成本。
- 完全图坐标点 MST：通常用朴素 Prim，距离边用到时再算。
- “已存在免费边”：先把免费边权设为 `0`，或先用并查集合并。
- 最大生成树：把排序改成从大到小，或 Prim 选最大边。

#### Kruskal
```cpp
struct Edge {
  int u, v;
  long long w;
  bool operator<(const Edge &other) const {
    return w < other.w;
  }
};

class DSU {
private:
  std::vector<int> parent, size;

public:
  explicit DSU(int n) : parent(n + 1), size(n + 1, 1) {
    std::iota(parent.begin(), parent.end(), 0);
  }

  auto find(int x) -> int {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
  }

  auto unite(int x, int y) -> bool {
    int rx = find(x), ry = find(y);
    if (rx == ry)
      return false;
    if (size[rx] < size[ry])
      std::swap(rx, ry);
    parent[ry] = rx;
    size[rx] += size[ry];
    return true;
  }
};

std::sort(edges.begin(), edges.end());
DSU dsu(n);
long long mst = 0;
int count = 0;

for (auto [u, v, w] : edges) {
  if (dsu.unite(u, v)) {
    mst += w;
    if (++count == n - 1)
      break;
  }
}

if (count != n - 1) {
  // 图不连通，不存在生成树
}
```

#### Prim 邻接矩阵版
适合稠密图。`matrix[u][v]` 是边权，不连通边设为 `INF`。

```cpp
const long long INF = 4e18;
std::vector<long long> min_dist(n, INF);
std::vector<bool> visited(n, false);

min_dist[0] = 0;
long long mst = 0;

for (int step = 0; step < n; ++step) {
  int u = -1;
  for (int i = 0; i < n; ++i)
    if (!visited[i] && (u == -1 || min_dist[i] < min_dist[u]))
      u = i;

  if (u == -1 || min_dist[u] == INF) {
    // 图不连通
    break;
  }

  visited[u] = true;
  mst += min_dist[u];

  for (int v = 0; v < n; ++v)
    if (!visited[v] && matrix[u][v] < min_dist[v])
      min_dist[v] = matrix[u][v];
}
```

#### Prim 优先队列版
适合邻接表。

```cpp
std::vector<bool> visited(n + 1, false);
std::priority_queue<std::pair<long long, int>,
                    std::vector<std::pair<long long, int>>,
                    std::greater<>> pq;

pq.emplace(0, 1);
long long mst = 0;
int count = 0;

while (!pq.empty() && count < n) {
  auto [w, u] = pq.top();
  pq.pop();
  if (visited[u])
    continue;

  visited[u] = true;
  mst += w;
  ++count;

  for (auto [v, weight] : adj[u])
    if (!visited[v])
      pq.emplace(weight, v);
}

if (count != n) {
  // 图不连通
}
```

### 关键路径（Critical Path / AOE 网）
适用：有向无环图 DAG，边表示活动，边权表示活动耗时。求项目最短完成时间、关键活动、哪些任务不能延误。

记号：
- `ve[u]`：事件 `u` 的最早发生时间
- `vl[u]`：事件 `u` 的最晚发生时间
- 边 `u -> v, w` 的活动最早开始 `e = ve[u]`
- 边 `u -> v, w` 的活动最晚开始 `l = vl[v] - w`
- 若 `e == l`，该活动是关键活动

```cpp
struct Edge {
  int from, to, weight;
};

std::vector<std::vector<std::pair<int, int>>> adj(n);
std::vector<int> indegree(n, 0);
std::vector<Edge> edges;

for (auto [u, v, w] : edges) {
  adj[u].emplace_back(v, w);
  ++indegree[v];
}

std::queue<int> q;
std::vector<int> topo;
std::vector<long long> ve(n, 0);

for (int i = 0; i < n; ++i)
  if (indegree[i] == 0)
    q.push(i);

while (!q.empty()) {
  int u = q.front();
  q.pop();
  topo.push_back(u);

  for (auto [v, w] : adj[u]) {
    ve[v] = std::max(ve[v], ve[u] + w);
    if (--indegree[v] == 0)
      q.push(v);
  }
}

if (topo.size() != n) {
  // 有环，不是 AOE 网
}
```

反向求最晚发生时间：

```cpp
long long project_time = *std::ranges::max_element(ve);

std::vector<long long> vl(n, project_time);
for (int i = n - 1; i >= 0; --i) {
  int u = topo[i];
  for (auto [v, w] : adj[u]) {
    vl[u] = std::min(vl[u], vl[v] - w);
  }
}
```

输出关键活动：

```cpp
for (auto [u, v, w] : edges) {
  long long earliest = ve[u];
  long long latest = vl[v] - w;
  if (earliest == latest) {
    // u -> v 是关键活动
  }
}
```

应用：
- 项目最短完成时间：`project_time`
- 关键路径长度：`project_time`
- 活动可延误时间：`latest - earliest`
- 多条关键路径：所有 `earliest == latest` 的边组成的关键子图中可能有多条路径

## 常用技巧
### 哈希表 / set
判重、计数、记录最早或最晚位置。`std::set` 有序，查找和插入 `O(log n)`；`std::unordered_set` 均摊 `O(1)`，但不能有序遍历。

```cpp
std::unordered_map<int, int> count;
for (int x : a)
  ++count[x];

std::unordered_set<int> seen;
for (int x : a) {
  if (seen.contains(target - x)) {
    // 找到一组和为 target 的数
  }
  seen.insert(x);
}
```

值到下标列表，配合二分找最小合法下标：

```cpp
std::vector<std::vector<int>> pos(max_value + 1);
for (int i = 0; i < n; ++i)
  pos[a[i]].push_back(i);

auto it = std::upper_bound(pos[value].begin(), pos[value].end(), i);
if (it != pos[value].end()) {
  int j = *it; // 最小的 j > i
}
```

### 双指针 / 滑动窗口
双指针适用：数组有序、窗口性质随左右端点单调变化、每个元素最多进出窗口一次。

有序数组二数和：

```cpp
int l = 0, r = n - 1;
while (l < r) {
  int sum = a[l] + a[r];
  if (sum < target)
    ++l;
  else if (sum > target)
    --r;
  else
    break;
}
```

滑动窗口：

```cpp
int l = 0;
long long sum = 0;
for (int r = 0; r < n; ++r) {
  sum += a[r];
  while (l <= r && !check_window(l, r, sum)) {
    sum -= a[l];
    ++l;
  }
  // [l, r] 是当前合法窗口
}
```

### 队列 / deque
普通 BFS 用 `queue`；需要两端进出、维护窗口或 0-1 BFS 时用 `deque`。

```cpp
std::queue<int> q;
dist[start] = 0;
q.push(start);

while (!q.empty()) {
  int u = q.front();
  q.pop();
  for (int v : g[u]) {
    if (dist[v] != -1)
      continue;
    dist[v] = dist[u] + 1;
    q.push(v);
  }
}
```

0-1 BFS：

```cpp
std::deque<int> q;
dist[start] = 0;
q.push_front(start);

while (!q.empty()) {
  int u = q.front();
  q.pop_front();
  for (auto [v, w] : g[u]) {
    if (dist[u] + w < dist[v]) {
      dist[v] = dist[u] + w;
      if (w == 0)
        q.push_front(v);
      else
        q.push_back(v);
    }
  }
}
```

### 撤销栈 / 状态历史
适用：编辑器撤销、版本回退、搜索中恢复状态。把每次修改前的旧值压栈，撤销时反向恢复。

```cpp
struct Change {
  int index;
  int old_value;
};

std::vector<int> a(n);
std::vector<Change> history;

auto assign_value = [&](int index, int value) {
  history.push_back({index, a[index]});
  a[index] = value;
};

auto snapshot = [&]() {
  return static_cast<int>(history.size());
};

auto rollback = [&](int checkpoint) {
  while (static_cast<int>(history.size()) > checkpoint) {
    auto [index, old_value] = history.back();
    history.pop_back();
    a[index] = old_value;
  }
};
```

### 堆 / 优先队列
默认是大根堆；小根堆用 `std::greater<>`。
```cpp
std::priority_queue<int> max_heap;
std::priority_queue<int, std::vector<int>, std::greater<>> min_heap;
```
自定义排序：比较器返回 `true` 表示优先级更低，会排到后面。
```cpp
struct Node {
  int value;
  int id;
};

struct Compare {
  auto operator()(const Node &a, const Node &b) const -> bool {
    if (a.value != b.value)
      return a.value > b.value; // 小 value 优先
    return a.id > b.id;
  }
};

std::priority_queue<Node, std::vector<Node>, Compare> pq;
```
Dijkstra / Prim 里常用懒删除：弹出时如果状态已经过期，直接 `continue`。

### 单调栈
适用：找每个元素左/右第一个更大或更小的元素、柱状图最大矩形、字典序删除字符。

右侧第一个更大元素：

```cpp
std::vector<int> next_greater(n, -1);
std::vector<int> st; // 栈内下标对应值单调递减

for (int i = 0; i < n; ++i) {
  while (!st.empty() && a[st.back()] < a[i]) {
    next_greater[st.back()] = i;
    st.pop_back();
  }
  st.push_back(i);
}
```

柱状图最大矩形：

```cpp
a.push_back(0); // 哨兵，清空栈
std::vector<int> st;
long long ans = 0;

for (int i = 0; i < a.size(); ++i) {
  while (!st.empty() && a[st.back()] > a[i]) {
    int h = a[st.back()];
    st.pop_back();
    int left = st.empty() ? -1 : st.back();
    ans = std::max(ans, 1LL * h * (i - left - 1));
  }
  st.push_back(i);
}
```

### 单调队列
适用：滑动窗口最大/最小值、窗口内 DP 最值优化。队列里存下标，队首永远是当前窗口最优。

滑动窗口最大值：

```cpp
std::deque<int> q;
std::vector<int> ans;

for (int i = 0; i < n; ++i) {
  while (!q.empty() && q.front() <= i - k)
    q.pop_front(); // 过期
  while (!q.empty() && a[q.back()] <= a[i])
    q.pop_back(); // 保持递减
  q.push_back(i);
  if (i >= k - 1)
    ans.push_back(a[q.front()]);
}
```

DP 窗口最大值：

```cpp
// dp[i] = value[i] + max(dp[j]), i - k <= j < i
std::deque<int> q;
for (int i = 0; i < n; ++i) {
  while (!q.empty() && q.front() < i - k)
    q.pop_front();
  if (!q.empty())
    dp[i] = value[i] + dp[q.front()];
  while (!q.empty() && dp[q.back()] <= dp[i])
    q.pop_back();
  q.push_back(i);
}
```

### 答案二分
把“求最优值”改成“判断答案 `x` 是否可行”。关键是判定函数 `check(x)` 必须单调。

最大值最小化：找最小可行值，形如 `false false true true`。

```cpp
auto check = [&](long long x) {
  // 是否能让最大代价 <= x
  return true;
};

long long l = low, r = high;
while (l < r) {
  long long mid = l + ((r - l) >> 1);
  if (check(mid))
    r = mid;
  else
    l = mid + 1;
}
// l 是最小可行值
```

应用：分割数组最小化最大段和、运货最小容量、最小化最大距离。

最小值最大化：找最大可行值，形如 `true true false false`。

```cpp
auto check = [&](long long x) {
  // 是否能让最小收益/间距 >= x
  return true;
};

long long l = low, r = high;
while (l < r) {
  long long mid = l + ((r - l + 1) >> 1);
  if (check(mid))
    l = mid;
  else
    r = mid - 1;
}
// l 是最大可行值
```

应用：最大化最小间距、最大化最小分数、选点/放置类问题。

### 约数分解 / 最小质因数
质数筛法：

埃氏筛，简单好写，复杂度 `O(n log log n)`。

```cpp
std::vector<bool> is_prime(limit + 1, true);
is_prime[0] = is_prime[1] = false;

for (int i = 2; i * i <= limit; ++i) {
  if (!is_prime[i])
    continue;
  for (long long j = 1LL * i * i; j <= limit; j += i)
    is_prime[j] = false;
}

std::vector<int> primes;
for (int i = 2; i <= limit; ++i)
  if (is_prime[i])
    primes.push_back(i);
```

线性筛，每个合数只被最小质因数筛一次，复杂度 `O(n)`。

```cpp
std::vector<int> primes;
std::vector<bool> is_composite(limit + 1, false);

for (int i = 2; i <= limit; ++i) {
  if (!is_composite[i])
    primes.push_back(i);
  for (int p : primes) {
    if (1LL * i * p > limit)
      break;
    is_composite[i * p] = true;
    if (i % p == 0)
      break;
  }
}
```

多次分解整数时先筛 `spf[x]`，`spf[x]` 表示 `x` 的最小质因数。复杂度 `O(M log log M)` 预处理，单次分解约 `O(质因数个数)`。

```cpp
std::vector<int> spf(limit + 1, 0);
for (int i = 2; i <= limit; ++i) {
  if (spf[i] != 0)
    continue;
  for (long long j = i; j <= limit; j += i)
    if (spf[j] == 0)
      spf[j] = i;
}

auto factorize = [&](int x) {
  std::vector<std::pair<int, int>> factors;
  while (x > 1) {
    int p = spf[x], cnt = 0;
    while (x % p == 0) {
      x /= p;
      ++cnt;
    }
    factors.push_back({p, cnt});
  }
  return factors;
};
```

生成所有约数：

```cpp
std::vector<int> divisors{1};
for (auto [p, cnt] : factors) {
  int size = static_cast<int>(divisors.size());
  int power = 1;
  for (int e = 1; e <= cnt; ++e) {
    power *= p;
    for (int i = 0; i < size; ++i)
      divisors.push_back(divisors[i] * power);
  }
}
```

若图的转移和质因数/约数有关，先预处理每个数的因子表，再 BFS，避免每次现场分解。

### 剪枝搜索
适用：组合枚举、分组、因子拆分。核心是先排序，再用上下界、重复跳过、不可行提前返回。

```cpp
std::sort(a.rbegin(), a.rend()); // 大元素优先，剪枝更强

auto dfs = [&](auto &&self, int index, int current) -> void {
  if (current >= best)
    return; // 最优性剪枝
  if (index == n) {
    best = std::min(best, current);
    return;
  }

  for (int choice = 0; choice < limit; ++choice) {
    if (!can_place(index, choice))
      continue; // 可行性剪枝
    place(index, choice);
    self(self, index + 1, current + cost(index, choice));
    undo(index, choice);
  }
};
```
