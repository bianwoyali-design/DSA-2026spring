# DSA Assignment #B: 20260513模拟考

*Updated 2026-05-13 13:35 GMT+8*
 *
Compiled by <mark>张真铭 元培学院</mark> (2026 Spring)
*



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

### E02724: 生日相同

sortings, http://cs101.openjudge.cn/pctbook/E02724/

思路：



代码：

```cpp
#include <iostream>
#include <string>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;

  std::vector data(13, std::vector(32, std::vector<std::string>()));
  while (n--) {
    std::string id;
    int month, day;
    std::cin >> id >> month >> day;
    data[month][day].emplace_back(id);
  }

  for (int i = 1; i <= 12; ++i) {
    for (int j = 1; j <= 31; ++j) {
      if (data[i][j].size() > 1) {
        std::cout << i << ' ' << j;
        for (const auto& id : data[i][j]) {
          std::cout << ' ' << id;
        }
        std::cout << '\n';
      }
    }
  }
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260513171903601.png"/>




### E19963: 买学区房

math, http://cs101.openjudge.cn/practice/19963


思路：



代码：

```cpp
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;
  std::vector<int> distance(n, 0);
  std::vector<int> price(n, 0);
  std::vector<double> rating(n, 0);
  std::vector<std::pair<int, double>> house(n);

  for (int i = 0; i < n; ++i) {
    char left, comma, right;
    int x, y;
    std::cin >> left >> x >> comma >> y >> right;
    distance[i] = x + y;
  }

  for (int i = 0; i < n; ++i) {
    std::cin >> price[i];
    rating[i] = static_cast<double>(distance[i]) / static_cast<double>(price[i]);
    house[i].first = price[i];
    house[i].second = rating[i];
  }

  std::sort(rating.begin(), rating.end());
  std::sort(price.begin(), price.end());
  double mid_rating =
      n % 2 == 0 ? (rating[n / 2] + rating[n / 2 - 1]) / 2.0 : rating[n / 2];
  double mid_price =
      n % 2 == 0 ? (price[n / 2] + price[n / 2 - 1]) / 2.0 : price[n / 2];

  int count = 0;
  for (int i = 0; i < n; ++i) {
    if (house[i].first < mid_price && house[i].second > mid_rating) {
      ++count;
    }
  }
  std::cout << count << '\n';
}

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>


![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260513172207330.png)


### M20746: 满足合法工时的最少人数

binary search, http://cs101.openjudge.cn/practice/20746/

思路：



代码：

```cpp
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string line;
  std::getline(std::cin, line);

  std::vector<int> nums;
  std::stringstream ss(line);
  std::string part;

  while (std::getline(ss, part, ',')) {
    nums.emplace_back(std::stoi(part));
  }

  int t;
  std::cin >> t;

  auto can_finish = [&](int k) -> bool {
    int total = 0;
    for (auto work : nums) {
      total += (work + k - 1) / k;
      if (total > t) {
        return false;
      }
    }
    return true;
  };

  int left = 1;
  int right = *std::max_element(nums.begin(), nums.end());
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (can_finish(mid)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  std::cout << left << '\n';
}

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>


![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260513173606646.png)


### M07734: 虫子的生活

DSU, http://cs101.openjudge.cn/practice/07734/

思路：



代码：

```cpp
#include <iostream>
#include <vector>

class DSU {
  std::vector<int> parent;
  std::vector<int> rank;

public:
  explicit DSU(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  auto find(int x) -> int {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  auto unite(int a, int b) -> void {
    int root_a = find(a);
    int root_b = find(b);
    if (root_a == root_b) {
      return;
    }

    if (rank[root_a] < rank[root_b]) {
      parent[root_a] = root_b;
    } else if (rank[root_a] > rank[root_b]) {
      parent[root_b] = root_a;
    } else {
      parent[root_b] = root_a;
      ++rank[a];
    }
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t{};
  std::cin >> t;
  for (int i = 1; i <= t; ++i) {
    int n{}, m{};
    std::cin >> n >> m;

    bool flag = false;
    DSU dsu(2 * n + 1);
    while (m--) {
      int a, b;
      std::cin >> a >> b;

      if (dsu.find(a) == dsu.find(b)) {
        flag = true;
      }

      dsu.unite(a, b + n);
      dsu.unite(b, a + n);
    }

    std::cout << "Scenario #" << i << ":\n";
    std::cout << (flag ? "Suspicious bugs found!" : "No suspicious bugs found!") << "\n\n";
  }
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>
![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260513172949630.png)




### M02186: Popular Cows

SCC, http://cs101.openjudge.cn/practice/02186/

思路：



代码

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{}, m{};
  std::cin >> n >> m;

  std::vector g(n, std::vector<int>());
  std::vector<int> u(m, 0), v(m, 0);
  for (int i = 0; i < m; ++i) {
    std::cin >> u[i] >> v[i];
    g[--u[i]].emplace_back(--v[i]);
  }

  std::vector<int> root(n, -1);
  std::vector<int> scc_size(n, 0);
  auto scc_condensation = [&]() -> void {
    int timer = 0;
    std::vector<int> dfn(n, -1);
    std::vector<int> low(n, -1);
    std::vector<int> stack;
    std::vector<bool> on_stack(n, false);

    auto dfs = [&](auto &&self, int u) -> void {
      dfn[u] = low[u] = timer++;
      on_stack[u] = true;
      stack.emplace_back(u);

      for (auto v : g[u]) {
        if (dfn[v] == -1) {
          self(self, v);
          low[u] = std::min(low[v], low[u]);
        } else if (on_stack[v]) {
          low[u] = std::min(low[u], dfn[v]);
        }
      }

      if (dfn[u] == low[u]) {
        while (true) {
          int node = stack.back();
          stack.pop_back();
          on_stack[node] = false;
          root[node] = u;
          ++scc_size[u];
          if (node == u) {
            break;
          }
        }
      }
    };

    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) {
        dfs(dfs, i);
      }
    }
  };

  scc_condensation();

  std::vector<int> outdegree(n, 0);
  for (int i = 0; i < m; ++i) {
    int root_u = root[u[i]], root_v = root[v[i]];
    if (root_u != root_v) {
      ++outdegree[root_u];
    }
  }

  int count = 0;
  int answer = 0;
  for (int i = 0; i < n; ++i) {
    if (root[i] == i && outdegree[i] == 0) {
      ++count;
      answer = scc_size[i];
    }
  }

  std::cout << (count == 1 ? answer : 0) << '\n';
}
```



<mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260513172712129.png)



### T01236: Network of Schools 238

SCC, http://cs101.openjudge.cn/practice/01236/

思路：



代码

```cpp
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;

  std::vector g(n, std::vector<int>());
  std::vector<std::pair<int, int>> edges;
  for (int i = 0; i < n; ++i) {
    int v{};
    while (std::cin >> v && v != 0) {
      --v;
      g[i].emplace_back(v);
      edges.emplace_back(i, v);
    }
  }

  std::vector<int> root(n, -1);
  int scc_count = 0;

  auto tarjan = [&]() -> void {
    int timer = 0;
    std::vector<int> dfn(n, -1);
    std::vector<int> low(n, -1);
    std::vector<int> stack;
    std::vector<bool> on_stack(n, false);

    auto dfs = [&](auto &&self, int u) -> void {
      dfn[u] = low[u] = timer++;
      stack.emplace_back(u);
      on_stack[u] = true;

      for (auto v : g[u]) {
        if (dfn[v] == -1) {
          self(self, v);
          low[u] = std::min(low[u], low[v]);
        } else if (on_stack[v]) {
          low[u] = std::min(low[u], dfn[v]);
        }
      }

      if (dfn[u] == low[u]) {
        ++scc_count;
        while (true) {
          int node = stack.back();
          stack.pop_back();
          on_stack[node] = false;
          root[node] = u;
          if (node == u) {
            break;
          }
        }
      }
    };

    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) {
        dfs(dfs, i);
      }
    }
  };

  tarjan();

  std::vector<int> indegree(n, 0);
  std::vector<int> outdegree(n, 0);
  for (const auto &[u, v] : edges) {
    int root_u = root[u];
    int root_v = root[v];
    if (root_u != root_v) {
      ++outdegree[root_u];
      ++indegree[root_v];
    }
  }

  int source_count = 0;
  int sink_count = 0;
  for (int i = 0; i < n; ++i) {
    if (root[i] == i) {
      if (indegree[i] == 0) {
        ++source_count;
      }
      if (outdegree[i] == 0) {
        ++sink_count;
      }
    }
  }

  std::cout << source_count << '\n';
  std::cout << (scc_count == 1 ? 0 : std::max(source_count, sink_count)) << '\n';
}

```



<mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260513173734211.png)



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

### LC 3548
```cpp
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

class Solution {
  auto rotate(std::vector<std::vector<int>> grid)
      -> std::vector<std::vector<int>> {
    int m = grid.size(), n = grid[0].size();
    std::vector rotated_grid(n, std::vector<int>(m));

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        rotated_grid[j][m - 1 - i] = grid[i][j];
      }
    }

    return rotated_grid;
  }

public:
  auto canPartitionGrid(std::vector<std::vector<int>> &grid) -> bool {
    long long total = 0;
    for (auto &&g : grid) {
      for (auto v : g) {
        total += v;
      }
    }

    auto check = [&](std::vector<std::vector<int>> g) -> bool {
      int m = g.size(), n = g[0].size();

      auto f = [&]() -> bool {
        std::unordered_set<long long> set = {0};
        long long s = 0;
        for (int i = 0; i < m - 1; ++i) {
          auto &row = g[i];
          for (int j = 0; j < n; ++j) {
            int v = row[j];
            s += v;
            if (i > 0 || j == 0 || j == n - 1) {
              set.insert(v);
            }
          }

          if (n == 1) {
            if (s * 2 == total || s * 2 - total == g[0][0] ||
                s * 2 - total == row[0]) {
              return true;
            }
            continue;
          }

          if (set.contains(2 * s - total)) {
            return true;
          }

          if (i == 0) {
            for (auto v : row) {
              set.insert(v);
            }
          }
        }

        return false;
      };

      if (f()) {
        return true;
      }
      std::ranges::reverse(g);
      return f();
    };

    return check(grid) || check(rotate(grid));
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<std::vector<int>> grid = {{1, 2}, {3, 4}};
  Solution sol;
  std::cout << sol.canPartitionGrid(grid) << '\n';
}
```

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260509195544265.png"/>

### LC 19
```cpp
#include <iostream>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  auto removeNthFromEnd(ListNode *head, int n) -> ListNode * {
    ListNode dummy(0, head);
    auto left = &dummy;
    auto right = &dummy;
    while (n--) {
      right = right->next;
    }
    while (right->next) {
      left = left->next;
      right = right->next;
    }
    auto next = left->next;
    left->next = left->next->next;
    delete next;
    return dummy.next;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  Solution sol;
  std::vector<int> data = {1, 2, 3, 4, 5};
  ListNode dummy;
  auto tail = &dummy;
  for (int d : data) {
    tail->next = new ListNode(d);
    tail = tail->next;
  }

  auto head = dummy.next;
  int n = 2;
  auto out = sol.removeNthFromEnd(head, n);
  while (out != nullptr) {
    std::cout << out->val << ' ';
    out = out->next;
  }
  std::cout << '\n';
}

```

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260511201408622.png"/>

### LC 142
```cpp
#include <cstddef>
#include <iostream>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  /* Floyd */
  auto detectCycle(ListNode *head) -> ListNode * {
    auto fast = head;
    auto slow = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) {
        while (slow != head) {
          slow = slow->next;
          head = head->next;
        }
        return slow;
      }
    }
    return nullptr;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  Solution sol;
  std::vector<int> data = {3, 2, 0, -4};
  int pos = 1;
  ListNode dummy;
  auto tail = &dummy;
  ListNode *insert = nullptr;
  for (int i = 0; i < data.size(); ++i) {
    tail->next = new ListNode(data[i]);
    tail = tail->next;
    if (i == pos) {
      insert = tail;
    }
  }
  tail->next = insert;
  auto head = dummy.next;
  std::cout << sol.detectCycle(head)->val << '\n';
}
```

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260511203339282.png"/>

### POJ 02815
```cpp
#include <array>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n = 0, m = 0;
  std::cin >> n >> m;
  std::vector matrix(n, std::vector<int>(m));
  for (auto &&row : matrix) {
    for (int &x : row) {
      std::cin >> x;
    }
  }

  const std::array<std::array<int, 2>, 4> dist = {
      {{{0, -1}}, {{-1, 0}}, {{0, 1}}, {{1, 0}}}};
  std::vector visited(n, std::vector<bool>(m, false));

  auto dfs = [&](auto &&self, int x, int y) -> int {
    if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y]) {
      return 0;
    }

    visited[x][y] = true;
    int size = 1;

    for (int i = 0; i < 4; ++i) {
      if (!(matrix[x][y] & (1 << i))) {
        size += self(self, x + dist[i][0], y + dist[i][1]);
      }
    }

    return size;
  };

  int max_size = 0;
  int counts = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!visited[i][j]) {
        max_size = std::max(max_size, dfs(dfs, i, j));
        ++counts;
      }
    }
  }

  std::cout << counts << '\n' << max_size << '\n';
}
```

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260511211843675.png"/>

### P3387
```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{}, m{};
  std::cin >> n >> m;

  std::vector<int> priority(n, 0);
  for (auto &a : priority) {
    std::cin >> a;
  }

  std::vector<int> u(m, 0);
  std::vector<int> v(m, 0);
  std::vector default_g(n, std::vector<int>());
  for (int i = 0; i < m; ++i) {
    std::cin >> u[i] >> v[i];
    default_g[--u[i]].emplace_back(--v[i]);
  }

  std::vector<int> indegree(n, 0);
  auto scc_condensation = [&]() -> std::unordered_map<int, std::vector<int>> {
    int timer = 0;
    std::vector<int> dfn(n, -1);
    std::vector<int> low(n, -1);
    std::vector<int> stack{};
    std::vector<bool> on_stack(n, false);
    std::vector<int> root(n, -1);

    auto dfs = [&](this auto &&self, int u) -> void {
      dfn[u] = timer;
      low[u] = timer;
      ++timer;
      stack.emplace_back(u);
      on_stack[u] = true;

      for (auto v : default_g[u]) {
        if (dfn[v] == -1) {
          self(v);
          low[u] = std::min(low[u], low[v]);
        } else if (on_stack[v]) {
          low[u] = std::min(low[u], dfn[v]);
        }
      }

      if (dfn[u] == low[u]) {
        while (true) {
          int node = stack.back();
          stack.pop_back();
          on_stack[node] = false;
          root[node] = u;
          if (node != u) {
            priority[u] += priority[node];
          } else {
            break;
          }
        }
      }
    };

    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) {
        dfs(i);
      }
    }
    std::unordered_map<int, std::vector<int>> new_g;
    for (int i = 0; i < n; ++i) {
      if (root[i] == i) {
        new_g.try_emplace(i);
      }
    }
    for (int i = 0; i < m; ++i) {
      int root_x = root[u[i]], root_y = root[v[i]];
      if (root_x != root_y) {
        new_g[root_x].emplace_back(root_y);
        ++indegree[root_y];
      }
    }

    return new_g;
  };
  auto condensed_g = scc_condensation();

  std::vector<int> dp(n, 0);
  auto topological_sort = [&]() -> int {
    std::queue<int> q;
    for (const auto &[u, _] : condensed_g) {
      if (!indegree[u]) {
        q.emplace(u);
        dp[u] = priority[u];
      }
    }

    while (!q.empty()) {
      auto u = q.front();
      q.pop();
      for (auto v : condensed_g[u]) {
        dp[v] = std::max(dp[v], dp[u] + priority[v]);
        --indegree[v];
        if (!indegree[v]) {
          q.emplace(v);
        }
      }
    }

    int max_res = 0;
    for (auto v : dp) {
      max_res = std::max(max_res, v);
    }
    return max_res;
  };

  std::cout << topological_sort() << '\n';
}

```

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260512221323868.png"/>

### CF 427C
```cpp
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n{};
  std::cin >> n;
  std::vector<int> costs(n, 0);
  for (auto &c : costs) {
    std::cin >> c;
  }

  int m{};
  std::cin >> m;
  std::vector g(n, std::vector<int>());
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    g[--u].emplace_back(--v);
  }

  constexpr int MOD = 1000000007;
  long long min_total_cost = 0;
  long long min_comb = 1;
  auto scc_condensation = [&]() -> void {
    int timer = 0;
    std::vector<int> dfn(n, -1);
    std::vector<int> low(n, -1);
    std::vector<int> stack;
    std::vector<bool> on_stack(n, false);

    auto dfs = [&](this auto &&self, int u) -> void {
      dfn[u] = low[u] = timer++;
      stack.emplace_back(u);
      on_stack[u] = true;

      for (auto v : g[u]) {
        if (dfn[v] == -1) {
          self(v);
          low[u] = std::min(low[u], low[v]);
        } else if (on_stack[v]) {
          low[u] = std::min(low[u], dfn[v]);
        }
      }

      if (dfn[u] == low[u]) {
        int min_cost = INT_MAX;
        int min_count = 0;
        while (true) {
          int node = stack.back();
          stack.pop_back();
          on_stack[node] = false;
          if (min_cost > costs[node]) {
            min_cost = costs[node];
            min_count = 1;
          } else if (min_cost == costs[node]) {
            ++min_count;
          }
          if (node == u) {
            break;
          }
        }
        min_total_cost += min_cost;
        min_comb = min_comb * min_count % MOD;
      }
    };

    for (int i = 0; i < n; ++i) {
      if (dfn[i] == -1) {
        dfs(i);
      }
    }
  };

  scc_condensation();
  std::cout << min_total_cost << ' ' << min_comb << '\n';
}
```

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260512230400178.png"/>


### POJ 01860
```cpp
#include <iostream>
#include <vector>

struct Node {
  int a;
  int b;
  double rab;
  double cab;
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N{}, M{}, S{};
  double V{};
  std::cin >> N >> M >> S >> V;

  std::vector<Node> edge;
  for (int i = 0; i < M; ++i) {
    int A, B;
    double R_ab, C_ab, R_ba, C_ba;
    std::cin >> A >> B >> R_ab >> C_ab >> R_ba >> C_ba;
    edge.emplace_back(Node{A, B, R_ab, C_ab});
    edge.emplace_back(Node{B, A, R_ba, C_ba});
  }

  std::vector<double> dp(N + 1, 0);
  dp[S] = V;

  for (int i = 0; i < N; ++i) {
    bool flag = false;
    for (auto &[u, v, rate, change] : edge) {
      if (dp[v] < (dp[u] - change) * rate) {
        dp[v] = (dp[u] - change) * rate;
        flag = true;
        if (v == S && dp[v] > V) {
          std::cout << "YES\n";
          return 0;
        }
      }
    }
    if (i == N - 1 && flag) {
      std::cout << "YES\n";
      return 0;
    }

    if (!flag) {
      break;
    }
  }

  std::cout << "NO\n";
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260515002527389.png)

### LC 787
```cpp
#include <iostream>
#include <vector>

class Solution {
public:
  auto findCheapestPrice(int n, std::vector<std::vector<int>> &flights, int src,
                         int dst, int k) -> int {
    std::vector<int> dist(n, INT_MAX / 2);
    dist[src] = 0;

    for (int i = 0; i < k + 1; ++i) {
      auto prev = dist;

      for (auto &edge : flights) {
        int u = edge[0], v = edge[1], w = edge[2];
        if (dist[v] > prev[u] + w) {
          dist[v] = prev[u] + w;
        }
      }
    }

    return dist[dst] == INT_MAX / 2 ? -1 : dist[dst];
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n = 4;
  std::vector<std::vector<int>> flights = {
      {0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}};
  int src = 0, dst = 3, k = 1;
  Solution sol;
  std::cout << sol.findCheapestPrice(n, flights, src, dst, k) << '\n';
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260516141745438.png)