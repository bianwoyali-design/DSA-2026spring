# DSA Assignment 520: 20260520模拟考

*Updated 2026-05-20 16:47 GMT+8*
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

### E04080: Huffman编码树

http://cs101.openjudge.cn/practice/04080/

思路：
剪绳子不说人话ver.


代码：

```cpp
#include <iostream>
#include <queue>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;
  std::priority_queue<int, std::vector<int>, std::greater<>> pq;
  while (n--) {
    int num;
    std::cin >> num;
    pq.emplace(num);
  }

  int total_wpl = 0;
  while (pq.size() > 1) {
    int first = pq.top();
    pq.pop();
    int second = pq.top();
    pq.pop();
    int sum = first + second;
    total_wpl += sum;
    pq.emplace(sum);
  }

  std::cout << total_wpl << '\n';
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260521163141900.png)



### M05443: 兔子与樱花

dijkstra, Floyd-Warshall, http://cs101.openjudge.cn/practice/05443/


思路：



代码：

```cpp
#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;
  std::vector<std::string> location(n);
  for (auto &&loc : location) {
    std::cin >> loc;
  }

  std::vector next_node(n, std::vector<int>(n, -1));
  std::vector dist(n, std::vector<int>(n, INT_MAX / 2));
  for (int i = 0; i < n; ++i) {
    dist[i][i] = 0;
  }

  int m{};
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    std::string a, b;
    int d;
    std::cin >> a >> b >> d;
    int u = std::find(location.begin(), location.end(), a) - location.begin();
    int v = std::find(location.begin(), location.end(), b) - location.begin();

    if (dist[u][v] > d) {
      dist[u][v] = dist[v][u] = d;
      next_node[u][v] = v;
      next_node[v][u] = u;
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          next_node[i][j] = next_node[i][k];
        }
      }
    }
  }

  auto print_path = [&](int u, int v) -> std::string {
    std::vector<int> path = {u};
    while (u != v) {
      u = next_node[u][v];
      path.emplace_back(u);
    }

    auto result = location[path.front()];
    for (int i = 1; i < path.size(); ++i) {
      int from = path[i - 1];
      int to = path[i];
      result += "->(" + std::to_string(dist[from][to]) + ")->" + location[to];
    }

    return result;
  };

  int k{};
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    std::string a, b;
    std::cin >> a >> b;
    int u = std::find(location.begin(), location.end(), a) - location.begin();
    int v = std::find(location.begin(), location.end(), b) - location.begin();
    std::cout << print_path(u, v) << '\n';
  }
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>


![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260521180943690.png)


### M20741: 两座孤岛最短距离

bfs, http://cs101.openjudge.cn/practice/20741/

思路：



代码：

```cpp
#include <array>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;
  std::vector matrix(n, std::string());
  for (auto &&row : matrix) {
    std::cin >> row;
  }

  bool found = false;
  std::queue<std::pair<int, int>> first_island;
  for (int i = 0; i < n && !found; ++i) {
    for (int j = 0; j < n && !found; ++j) {
      if (matrix[i][j] == '1') {
        matrix[i][j] = '2';
        first_island.emplace(i, j);
        found = true;
      }
    }
  }

  constexpr std::array<std::array<int, 2>, 4> dist = {
      {{{0, 1}}, {{1, 0}}, {{0, -1}}, {{-1, 0}}}};

  std::queue<std::pair<int, int>> q;
  while (!first_island.empty()) {
    auto [x, y] = first_island.front();
    first_island.pop();
    q.emplace(x, y);

    for (int i = 0; i < 4; ++i) {
      int newX = x + dist[i][0];
      int newY = y + dist[i][1];
      if (newX >= 0 && newX < n && newY >= 0 && newY < n &&
          matrix[newX][newY] == '1') {
        matrix[newX][newY] = '2';
        first_island.emplace(newX, newY);
      }
    }
  }

  int step = 0;
  while (!q.empty()) {
    int sz = q.size();
    while (sz--) {
      auto [x, y] = q.front();
      q.pop();

      for (int i = 0; i < 4; ++i) {
        int newX = x + dist[i][0];
        int newY = y + dist[i][1];
        if (newX >= 0 && newX < n && newY >= 0 && newY < n && matrix[newX][newY] != '2') {
          if (matrix[newX][newY] == '1') {
            std::cout << step << '\n';
            return 0;
          }

          matrix[newX][newY] = '2';
          q.emplace(newX, newY);
        }
      }
    }
    ++step;
  }
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>
![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260521183956818.png)




### M24637: 宝藏二叉树

dp, dfs http://cs101.openjudge.cn/practice/24637/

思路：



代码：

```cpp
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;
  std::vector<int> tree(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    std::cin >> tree[i];
  }

  std::vector dp(2 * n + 2, std::vector<int>(2, 0));
  auto dfs = [&](auto &&self, int i) -> void {
    if (i > n) {
      return;
    }

    int left = i << 1;
    int right = i << 1 | 1;

    self(self, left);
    self(self, right);

    dp[i][0] = std::max(dp[left][1], dp[left][0]) +
               std::max(dp[right][1], dp[right][0]);
    dp[i][1] = dp[left][0] + dp[right][0] + tree[i];
  };

  dfs(dfs, 1);

  std::cout << std::max(dp[1][0], dp[1][1]) << '\n';
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260521191947143.png)



### T02337: Catenyms

Eulerian Path, http://cs101.openjudge.cn/practice/02337/

思路：



代码

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t{};
  std::cin >> t;
  while (t--) {
    int n{};
    std::cin >> n;
    std::vector<std::string> words(n);
    for (auto &&word : words) {
      std::cin >> word;
    }

    std::sort(words.rbegin(), words.rend());

    std::vector adj(26, std::vector<std::pair<int, std::string>>());
    std::vector<int> indegree(26, 0);
    std::vector<int> outdegree(26, 0);

    for (auto &word : words) {
      int u = word.front() - 'a';
      int v = word.back() - 'a';

      adj[u].emplace_back(v, word);
      ++indegree[v];
      ++outdegree[u];
    }

    bool impossible = false;

    int start = -1;
    int start_count = 0;
    int end_count = 0;

    for (int i = 0; i < 26; ++i) {
      if (indegree[i] + 1 == outdegree[i]) {
        start = i;
        ++start_count;
      } else if (outdegree[i] + 1 == indegree[i]) {
        ++end_count;
      } else if (outdegree[i] != indegree[i]) {
        impossible = true;
        break;
      }
    }

    if (impossible || !((start_count == 0 && end_count == 0) ||
                        (start_count == 1 && end_count == 1))) {
      std::cout << "***\n";
      continue;
    }

    if (start == -1) {
      start = words.back().front() - 'a';
    }

    std::vector<std::string> res;
    auto dfs = [&](auto &&self, int u) -> void {
      while (!adj[u].empty()) {
        auto [v, word] = adj[u].back();
        adj[u].pop_back();

        self(self, v);
        res.emplace_back(word);
      }
    };

    dfs(dfs, start);

    if (res.size() != n) {
      std::cout << "***\n";
      continue;
    } else {
      std::reverse(res.begin(), res.end());
      std::cout << res.front();
      for (int i = 1; i < n; ++i) {
        std::cout << '.' << res[i];
      }
      std::cout << '\n';
    }
  }
}
```



<mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260522132123432.png)



### T30878:力场叠加模拟

segment tree, lazy propagation, http://cs101.openjudge.cn/practice/30878/

思路：



代码

```cpp
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

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
                   const Type &query_de = Type(), const Type &lazy_de = Type())
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

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N, Q;
  std::cin >> N >> Q;

  std::vector<long long> data(N, 0);

  auto max_value = [](long long a, long long b) -> long long {
    return std::max(a, b);
  };

  SegTree segtree(data, max_value, std::numeric_limits<long long>::lowest(),
                  0LL);

  while (Q--) {
    std::string operation;
    int l, r;
    std::cin >> operation;

    if (operation == "Add") {
      long long v;
      std::cin >> l >> r >> v;
      segtree.add_range(l - 1, r - 1, v);
    }
    if (operation == "Query") {
      std::cin >> l >> r;
      std::cout << segtree.query_range(l - 1, r - 1) << '\n';
    }
  }
}

```



<mark>（至少包含有"Accepted"）</mark>


![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260522132254226.png)


## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2026spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

这周过的太混乱了。
还是和`数据结构与算法(B)`过520更幸福😋
### POJ 01258
```cpp
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N{};
  while (std::cin >> N) {
    std::vector matrix(N, std::vector<int>(N));
    for (auto &&row : matrix) {
      for (auto &v : row) {
        std::cin >> v;
      }
    }


    int total_weight = 0;
    std::vector<int> min_dist(N, 0x3f3f3f3f);
    std::vector<bool> visited(N, false);
    min_dist[0] = 0;

    for (int step = 0; step < N; ++step) {
      int current = -1;

      for (int i = 0; i < N; ++i) {
        if (!visited[i] && (current == -1 || min_dist[i] < min_dist[current])) {
          current = i;
        }
      }

      visited[current] = true;
      total_weight += min_dist[current];

      for (int i = 0; i < N; ++i) {
        if (!visited[i] && matrix[current][i] < min_dist[i]) {
          min_dist[i] = matrix[current][i];
        }
      }
    }

    std::cout << total_weight << '\n';
  }
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260521160142286.png)

### LC 1584
|算法|写法|时间复杂度|空间|
|---|---|---|---|
|Prim 邻接矩阵版|不用优先队列，每次找最近点|O(N^2)|O(N) 或 O(N^2)|
|Prim 优先队列版|你现在这种|O(N^2 log N)|O(N^2)|
|Kruskal|矩阵转边集再排序|O(N^2 log N)|O(N^2)|
所以最适合这个题的是：**朴素 Prim，邻接矩阵版**。

原因是图是稠密图，几乎每两个点之间都有边。Kruskal 要先把所有边拿出来排序，排序成本比较高；优先队列 Prim 也会把很多边塞进堆里。朴素 Prim 直接在矩阵上维护每个未访问点到当前生成树的最短距离，不需要排序，也不需要堆。

**邻接矩阵 + 稠密图：朴素 Prim 最好。**  
**边比较少的稀疏图：Kruskal 或堆优化 Prim 更常用。**

```cpp
#include <cstdlib>
#include <iostream>
#include <vector>

class Solution {
public:
  auto minCostConnectPoints(std::vector<std::vector<int>> &points) -> int {
    int n = points.size();
    std::vector matrix(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int xi = points[i][0], yi = points[i][1];
        int xj = points[j][0], yj = points[j][1];
        matrix[i][j] = matrix[j][i] = std::abs(xi - xj) + std::abs(yi - yj);
      }
    }

    int total_dist = 0;
    std::vector<int> min_dist(n, 0x3f3f3f3f);
    std::vector<bool> visited(n, false);
    min_dist[0] = 0;

    for (int step = 0; step < n; ++step) {
      int current = -1;

      for (int i = 0; i < n; ++i) {
        if (!visited[i] && (current == -1 || min_dist[i] < min_dist[current])) {
          current = i;
        }
      }

      visited[current] = true;
      total_dist += min_dist[current];

      for (int i = 0; i < n; ++i) {
        if (!visited[i] && matrix[current][i] < min_dist[i]) {
          min_dist[i] = matrix[current][i];
        }
      }
    }
    
    return total_dist;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<std::vector<int>> points = {{-1000000, -1000000},
                                          {1000000, 1000000}};
  Solution sol;
  std::cout << sol.minCostConnectPoints(points) << '\n';
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260521160340197.png)

### Luogu P6192

使用SPFA优化，勉强挤进最优解前十。没有恶意卡常刷成绩。
```cpp
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector adj(n + 1, std::vector<std::pair<int, int>>());
  while (m--) {
    int u, v, w;
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }

  std::vector<int> terminals(k);
  for (auto &&v : terminals) {
    std::cin >> v;
  }

  std::vector dp(1 << k, std::vector<int>(n + 1, 0x3f3f3f3f));

  for (int i = 0; i < k; ++i) {
    dp[1 << i][terminals[i]] = 0;
  }

  for (int mask = 1; mask < (1 << k); ++mask) {
    for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
      if (sub > (mask ^ sub)) {
        continue;
      }
      for (int i = 1; i <= n; ++i) {
        dp[mask][i] = std::min(dp[mask][i], dp[sub][i] + dp[mask ^ sub][i]);
      }
    }

    std::deque<int> q;
    std::vector<bool> in_queue(n + 1, false);
    for (int i = 1; i <= n; ++i) {
      if (dp[mask][i] != 0x3f3f3f3f) {
        in_queue[i] = true;
        q.emplace_back(i);
      }
    }

    while (!q.empty()) {
      int u = q.front();
      q.pop_front();
      in_queue[u] = false;

      for (auto &&[v, w] : adj[u]) {
        if (dp[mask][v] > dp[mask][u] + w) {
          dp[mask][v] = dp[mask][u] + w;

          if (!in_queue[v]) {
            in_queue[v] = true;

            if (!q.empty() && dp[mask][v] < dp[mask][q.front()]) {
              q.emplace_front(v);
            } else {
              q.emplace_back(v);
            }
          }
        }
      }
    }
  }

  std::cout << dp[(1 << k) - 1][terminals[0]] << '\n';
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260521161257949.png)

### sy406
```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{}, m{};
  std::cin >> n >> m;
  std::vector g(n, std::vector<std::pair<int, int>>());
  std::vector<int> indegree(n, 0);
  for (int i = 0; i < m; ++i) {
    int u{}, v{}, w{};
    std::cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    ++indegree[v];
  }

  std::vector<int> ve(n, 0);
  std::vector<int> topo_order;
  auto topo_sort = [&]() -> bool {
    std::queue<int> q;
    for (int u = 0; u < n; ++u) {
      if (!indegree[u]) {
        q.emplace(u);
      }
    }

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      topo_order.emplace_back(u);

      for (auto &&[v, w] : g[u]) {
        if (ve[u] + w > ve[v]) {
          ve[v] = ve[u] + w;
        }

        --indegree[v];
        if (!indegree[v]) {
          q.emplace(v);
        }
      }
    }

    return topo_order.size() == n;
  };

  auto get_critical_activity = [&]() -> std::vector<std::vector<int>> {
    int max_length = *std::max_element(ve.begin(), ve.end());
    std::vector<int> vl(n, max_length);
    std::vector activity(n, std::vector<int>());

    std::reverse(topo_order.begin(), topo_order.end());

    for (auto u : topo_order) {
      for (auto &&[v, w] : g[u]) {
        if (vl[v] - w < vl[u]) {
          vl[u] = vl[v] - w;
        }
      }
    }

    for (int u = 0; u < n; ++u) {
      for (auto &&[v, w] : g[u]) {
        int e = ve[u];
        int l = vl[v] - w;
        if (e == l) {
          activity[u].emplace_back(v);
        }
      }
    }

    return activity;
  };

  auto indegree_copy = indegree;
  std::vector activity(n, std::vector<int>());

  auto print_critical_path = [&](auto &&self, int u,
                                 std::vector<int> &path) -> void {
    path.emplace_back(u);

    if (activity[u].empty()) {
      for (int i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i < path.size() - 1) {
          std::cout << "->";
        } else {
          std::cout << '\n';
        }
      }
    } else {
      std::sort(activity[u].begin(), activity[u].end());
      for (auto v : activity[u]) {
        self(self, v, path);
      }
    }

    path.pop_back();
  };

  if (!topo_sort()) {
    std::cout << "No\n";
  } else {
    std::cout << "Yes\n";
    activity = get_critical_activity();
    for (int u = 0; u < n; ++u) {
      if (!indegree_copy[u] && !activity[u].empty()) {
        std::vector<int> path;
        print_critical_path(print_critical_path, u, path);
      }
    }
  }
}

```


![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260521161559692.png)