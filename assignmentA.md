# DSA Assignment #A: 5月份月考

*Updated 2026-05-06 15:43 GMT+8*
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

### E04137: 最小新整数 

monotonic stack, http://cs101.openjudge.cn/practice/04137/

思路：



代码：

```cpp
#include <iostream>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;

  while (t--) {
    std::string n;
    int k;
    std::cin >> n >> k;

    for (int i = 0; i < k; ++i) {
      bool flag = false;
      for (int j = 0; j < n.length() - 1; ++j) {
        if (n[j] > n[j + 1]) {
          n.erase(n.begin() + j);
          flag = true;
          break;
        }
      }
      if (!flag) {
        n.pop_back();
      }
    }

    std::cout << n << '\n';
  }
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>


<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260508103115899.png"/>


### E04143: 和为给定数 

two pointers, http://cs101.openjudge.cn/dsapre/04143/


思路：



代码：

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n = 0;
  std::cin >> n;
  std::vector<int> arr(n, 0);
  for (auto &&a : arr) {
    std::cin >> a;
  }
  int sum = 0;
  std::cin >> sum;

  std::sort(arr.begin(), arr.end());

  for (int l = 0, r = arr.size() - 1; l < r;) {
    int curr_sum = arr[l] + arr[r];
    if (curr_sum > sum) {
      --r;
    } else if (curr_sum < sum) {
      ++l;
    } else {
      std::cout << arr[l] << ' ' << arr[r] << '\n';
      return 0;
    }
  }

  std::cout << "No\n";
  return 0;
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>
<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260508105934229.png"/>




### M27638: 求二叉树的高度和叶子数目

http://cs101.openjudge.cn/practice/27638/

思路：



代码：

```cpp
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

struct TreeNode {
  int val;
  TreeNode *left{};
  TreeNode *right{};
  TreeNode(int i) : val(i) {};
};

class TreeUtils {
private:
  TreeNode *root;
  int leafs = 0;

  auto _get_height(TreeNode *node) -> int {
    if (!node) {
      return -1;
    }
    return std::max(_get_height(node->left), _get_height(node->right)) + 1;
  }

public:
  TreeUtils(int n, const std::vector<std::pair<int, int>> &tree) {
    std::vector<TreeNode *> node(n, nullptr);
    std::vector<bool> has_parent(n, false);

    for (int i = 0; i < n; ++i) {
      node[i] = new TreeNode(i);
    }

    for (int i = 0; i < n; ++i) {
      auto [left, right] = tree[i];
      if (left == -1 && right == -1) {
        ++leafs;
      }

      if (left != -1) {
        node[i]->left = node[left];
        has_parent[left] = true;
      }

      if (right != -1) {
        node[i]->right = node[right];
        has_parent[right] = true;
      }
    }

    root = node[std::find(has_parent.begin(), has_parent.end(), false) -
                has_parent.begin()];
  }

  auto get_leaf() -> int { return leafs; }

  auto get_height() -> int { return _get_height(root); }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n = 0;
  std::cin >> n;
  std::vector<std::pair<int, int>> tree(n);
  for (auto &[left, right] : tree) {
    std::cin >> left >> right;
  }
  TreeUtils sol(n, tree);
  std::cout << sol.get_height() << ' ' << sol.get_leaf() << '\n';
}

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260508113717766.png"/>



### M30720: 败方树的构建与维护

http://cs101.openjudge.cn/practice/30720/

思路：



代码：

```cpp
#include <iostream>
#include <vector>

class SegTree {
  int n = 0;
  std::vector<int> tree{};
  std::vector<int> node{};

public:
  explicit SegTree(const std::vector<int> &data) : n(data.size()) {
    tree.assign(2 * n, 0);
    node.assign(n, 0);
    for (int i = 0; i < n; ++i) {
      tree[i + n] = data[i];
    }
    for (int i = n - 1; i >= 0; --i) {
      tree[i] = std::min(tree[i << 1], tree[i << 1 | 1]);
      node[i] = std::max(tree[i << 1], tree[i << 1 | 1]);
    }
  }

  auto update(int i, const int value) -> void {
    i += n;
    tree[i] = value;

    while (i > 1) {
      tree[i >> 1] = std::min(tree[i], tree[i ^ 1]);
      node[i >> 1] = std::max(tree[i], tree[i ^ 1]);
      i >>= 1;
    }

    node[0] = tree[1];
  }

  auto query() -> std::vector<int> { return node; }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> data(n);
  for (auto &d : data) {
    std::cin >> d;
  }

  SegTree sol(data);
  auto res = sol.query();
  for (const auto &r : res) {
    std::cout << r << ' ';
  }
  std::cout << '\n';

  while (m--) {
    int i, value;
    std::cin >> i >> value;
    sol.update(i, value);
    auto res = sol.query();
    for (const auto &r : res) {
      std::cout << r << ' ';
    }
    std::cout << '\n';
  }
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>


<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260508155301917.png"/>


### 27093: 排队又来了

Segment Tree, Discretization（离散化）, binary search, http://cs101.openjudge.cn/practice/27093/

思路：



代码

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

template <typename Type> class Fenwick {
private:
  int n;
  std::vector<Type> tree;

public:
  explicit Fenwick(int n) : n(n), tree(n + 1, -1) {}

  auto update(int i, Type layer) -> void {
    while (i <= n) {
      tree[i] = std::max(tree[i], layer);
      i += (i & -i);
    }
  };

  [[nodiscard]] auto getMax(int i) const -> int {
    int res = -1;
    while (i > 0) {
      res = std::max(res, tree[i]);
      i &= i - 1;
    }
    return res;
  };
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N, D;
  std::cin >> N >> D;

  std::vector<int> v(N), val(N);
  for (int i = 0; i < N; ++i) {
    std::cin >> v[i];
    val[i] = v[i];
  }

  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());
  int l = (int)v.size();

  std::vector<std::vector<int>> res(N + 1);

  Fenwick<int> bit_l(l), bit_r(l);

  for (const int x : val) {
    int index = std::lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
    int left = std::upper_bound(v.begin(), v.end(), x - D - 1) - v.begin();
    int right =
        l - (std::lower_bound(v.begin(), v.end(), x + D + 1) - v.begin());

    int layer = 1 + std::max(bit_l.getMax(left), bit_r.getMax(right));

    bit_l.update(index, layer);
    bit_r.update(l + 1 - index, layer);

    res[layer].push_back(x);
  }

  for (auto &r : res) {
    if (r.empty())
      continue;
    std::sort(r.begin(), r.end());
    for (const int x : r)
      std::cout << x << ' ';
  }
}
```



<mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260508155106852.png"/>



### T30669: 地铁换乘

LCA, binary lifting, http://cs101.openjudge.cn/practice/30669/

思路：



代码

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n = 0, t = 0;
  std::cin >> n >> t;
  std::vector g(n + 1, std::vector<int>());
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  int p, q;
  long long v1, v2;
  std::cin >> p >> q >> v1 >> v2;

  int log = 1;
  while ((1 << log) <= n) {
    ++log;
  }

  std::vector<int> depth(n + 1, 0);
  std::vector up(n + 1, std::vector<int>(log, -1));

  auto dfs = [&](auto &&self, int u, int parent) -> void {
    up[u][0] = parent;
    for (int j = 1; j < log; ++j) {
      if (up[u][j - 1] != -1) {
        up[u][j] = up[up[u][j - 1]][j - 1];
      }
    }

    for (int v : g[u]) {
      if (v == parent) {
        continue;
      }
      depth[v] = depth[u] + 1;
      self(self, v, u);
    }
  };

  dfs(dfs, t, -1);

  auto lca = [&](int u, int v) -> int {
    if (depth[v] > depth[u]) {
      std::swap(u, v);
    }

    for (int j = log - 1; j >= 0; --j) {
      if (up[u][j] != -1 && depth[up[u][j]] >= depth[v]) {
        u = up[u][j];
      }
    }

    if (u == v) {
      return u;
    }

    for (int j = log - 1; j >= 0; --j) {
      if (up[u][j] != -1 && up[u][j] != up[v][j]) {
        u = up[u][j];
        v = up[v][j];
      }
    }

    return up[u][0];
  };

  auto jump = [&](int u, long long steps) -> int {
    for (int j = 0; steps > 0; ++j) {
      if (steps & 1) {
        u = up[u][j];
      }
      steps >>= 1;
    }
    return u;
  };

  const int root = lca(p, q);
  const long long distance = depth[p] + depth[q] - 2LL * depth[root];
  const long long days = distance / (v1 + v2);
  const long long from_p = days * v1;

  int station = 0;
  if (from_p <= depth[p] - depth[root]) {
    station = jump(p, from_p);
  } else {
    station = jump(q, distance - from_p);
  }

  std::cout << days << ' ' << depth[station] << '\n';
}

```



<mark>（至少包含有"Accepted"）</mark>


<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260508170949835.png"/>


## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2026spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

### sy299
```cpp
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
  int num;
  char op;
  bool is_op;
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string expr;
  std::getline(std::cin, expr);

  std::unordered_map<char, int> priority = {
      {'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}};

  std::vector<Node> post_prefix;
  std::vector<char> op_stack;
  for (char c : expr) {
    if (c == ' ') {
      continue;
    } else if (std::isdigit(c)) {
      post_prefix.emplace_back(Node{c - '0', 0, false});
    } else {
      while (!op_stack.empty() && priority[c] <= priority[op_stack.back()]) {
        post_prefix.emplace_back(Node{0, op_stack.back(), true});
        op_stack.pop_back();
      }
      op_stack.emplace_back(c);
    }
  }
  while (!op_stack.empty()) {
    post_prefix.emplace_back(Node{0, op_stack.back(), true});
    op_stack.pop_back();
  }

  std::vector<double> num_stack;
  for (auto e : post_prefix) {
    if (!e.is_op) {
      num_stack.emplace_back(e.num);
    } else {
      double num2 = num_stack.back();
      num_stack.pop_back();
      double num1 = num_stack.back();
      num_stack.pop_back();

      switch (e.op) {
      case '+':
        num_stack.emplace_back(num1 + num2);
        break;
      case '-':
        num_stack.emplace_back(num1 - num2);
        break;
      case '*':
        num_stack.emplace_back(num1 * num2);
        break;
      case '/':
        num_stack.emplace_back(num1 / num2);
        break;
      default:
        break;
      }
    }
  }

  std::printf("%.2lf\n", num_stack.back());
}
```

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260509175427466.png"/>
