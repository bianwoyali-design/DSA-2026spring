# DSA Assignment E: 20260603期末机考

*Updated 2026-05-20 16:47 GMT+8*
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

### E30646:缺失的第一个正数

http://cs101.openjudge.cn/practice/30646

思路：



代码：

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<int> nums(n);
  int minnum = 1;
  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }

  std::sort(nums.begin(), nums.end());
  for (int i = 0; i < n; ++i) {
    if (nums[i] == minnum) {
      ++minnum;
    }
  }

  std::cout << minnum << '\n';
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>


![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260603224103117.png)


### E30930:猫猫水群聊

 http://cs101.openjudge.cn/practice/30930


思路：



代码：

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<int> x(n);
  for (auto &a : x) {
    std::cin >> a;
  }

  std::sort(x.rbegin(), x.rend());

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (x[i] >= i + 1) {
      ans = i + 1;
    } else {
      break;
    }
  }

  std::cout << ans << '\n';
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260603224139815.png)



### M30874:匹配队友

http://cs101.openjudge.cn/practice/30874

思路：



代码：

```cpp
#include <deque>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::vector<int> team(n, 0);
  std::vector<char> p(n);

  int count = 1;
  std::deque<int> qt, qd, qh;

  for (int i = 0; i < n; ++i) {
    std::cin >> p[i];
  }

  for (int i = 0; i < n; ++i) {
    if (p[i] == 'D') {
      qd.emplace_back(i);
    }
    if (p[i] == 'H') {
      qh.emplace_back(i);
    }
    if (p[i] == 'T') {
      qt.emplace_back(i);
    }

    if (qt.size() >= 1 && qd.size() >= 3 && qh.size() >= 1) {
      team[qt.front()] = count;
      qt.pop_front();
      team[qh.front()] = count;
      qh.pop_front();
      for (int x = 0; x < 3; ++x) {
        team[qd.front()] = count;
        qd.pop_front();
      }
      ++count;
    }
  }

  for (int i = 0; i < n; ++i) {
    std::cout << team[i] << ' ';
  }
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260603224320866.png)



### M30680:森林局部排序遍历

http://cs101.openjudge.cn/practice/30680

思路：



代码：

```cpp
#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::unordered_map<int, std::vector<int>> tree;
  std::map<int, int> indegree;
  while (n--) {
    std::string str;
    std::getline(std::cin, str);

    bool first = true;
    int root;
    std::stringstream ss(str);
    for (int node; ss >> node;) {
      if (first) {
        root = node;
        if (!indegree[root])
          indegree[root] = 0;
        first = false;
      } else {
        tree[root].emplace_back(node);
        ++indegree[node];
      }
    }
  }

  std::vector<int> root;
  for (auto [node, d] : indegree) {
    if (!d) {
      root.emplace_back(node);
    }
  }

  auto dfs = [&](auto &&self, int root) -> void {
    if (tree[root].empty()) {
      std::cout << root << '\n';
      return;
    }

    std::vector<int> c;
    c.emplace_back(root);
    for (auto child : tree[root]) {
      c.emplace_back(child);
    }

    std::sort(c.begin(), c.end());

    for (auto node : c) {
      if (node == root) {
        std::cout << node << '\n';
      } else {
        self(self, node);
      }
    }
  };

  for (auto node : root) {
    dfs(dfs, node);
  }
}

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260603224222399.png)



### M30947:Ask for Likes

http://cs101.openjudge.cn/practice/30947

思路：



代码

```cpp
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, q;
  std::cin >> n >> q;

  std::vector<long long> need;
  bool has_free = false;

  for (int i = 0; i < n; ++i) {
    long long c;
    std::cin >> c;

    if (c <= 1) {
      // 0 可以继续保持 0 不参与乘积，也可以加到任意正数；
      // 1 可以保持 1，也可以加到任意更大的数。
      // 所以这样的表情位可以吸收最后剩下的乘积因子。
      has_free = true;
    } else {
      // c > 1 的位置已经非零，且只能变大，最终必须参与乘积，
      // 因此要给它分配一个 >= c 的因子。
      need.push_back(c);
    }
  }

  std::sort(need.rbegin(), need.rend());

  // suffix[i] 是 need[i..] 的最小可能乘积。
  // 若 suffix[i] > rest，则剩下这些必须位置无论怎么分配都不可能塞进 rest。
  constexpr long long limit = 1000000001LL;
  std::vector<long long> suffix(need.size() + 1, 1);
  for (int i = static_cast<int>(need.size()) - 1; i >= 0; --i) {
    if (suffix[i + 1] > limit / need[i]) {
      suffix[i] = limit;
    } else {
      suffix[i] = suffix[i + 1] * need[i];
    }
  }

  auto factorize = [](long long x) -> std::vector<std::pair<long long, int>> {
    std::vector<std::pair<long long, int>> factors;

    for (long long p = 2; p * p <= x; ++p) {
      if (x % p != 0) {
        continue;
      }

      int count = 0;
      while (x % p == 0) {
        x /= p;
        ++count;
      }
      factors.emplace_back(p, count);
    }

    if (x > 1) {
      factors.emplace_back(x, 1);
    }

    return factors;
  };

  auto get_divisors = [&](long long x) -> std::vector<long long> {
    auto factors = factorize(x);
    std::vector<long long> divisors{1};

    // 如果 x = p1^a1 * p2^a2 * ...，
    // 所有约数就是每个质因数各选 0..ai 次后的乘积。
    for (auto [p, count] : factors) {
      int size = static_cast<int>(divisors.size());
      long long power = 1;

      for (int e = 1; e <= count; ++e) {
        power *= p;
        for (int i = 0; i < size; ++i) {
          divisors.push_back(divisors[i] * power);
        }
      }
    }

    std::sort(divisors.rbegin(), divisors.rend());
    return divisors;
  };

  while (q-- > 0) {
    long long x;
    std::cin >> x;

    if (suffix[0] > x) {
      std::cout << "No\n";
      continue;
    }

    auto divisors = get_divisors(x);
    std::vector<std::unordered_set<long long>> failed(need.size() + 1);

    auto dfs = [&](auto &&self, int index, long long rest) -> bool {
      if (suffix[index] > rest) {
        return false;
      }

      if (index == static_cast<int>(need.size())) {
        // 所有 c > 1 的位置都分配完了。
        // 如果有 0/1 位置，剩余 rest 可以交给它吸收；
        // 否则必须刚好用完，也就是 rest == 1。
        return has_free || rest == 1;
      }

      if (failed[index].count(rest)) {
        return false;
      }

      // 给 need[index] 分配一个最终值 d。
      // d 必须是 rest 的约数，否则乘积无法刚好变成目标 x；
      // d 还必须 >= need[index]，因为这个位置只能增加不能减少。
      for (long long d : divisors) {
        if (d < need[index]) {
          break;
        }

        if (rest % d != 0) {
          continue;
        }

        if (self(self, index + 1, rest / d)) {
          return true;
        }
      }

      failed[index].insert(rest);
      return false;
    };

    std::cout << (dfs(dfs, 0, x) ? "Yes\n" : "No\n");
  }
}
```



<mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260603224456066.png)



### T30913:猫猫逛公园 

http://cs101.openjudge.cn/practice/30913

思路：



代码

```cpp
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;

  std::vector g(n, std::vector<std::pair<int, int>>());

  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    g[u].emplace_back(v, w);
  }

  int src;
  std::cin >> src;
  --src;

  int timer = 0;
  int component_count = 0;
  std::vector<int> dfn(n, -1);
  std::vector<int> low(n, -1);
  std::vector<int> stack{};
  std::vector<bool> on_stack(n, false);
  std::vector<int> comp(n, -1);

  auto dfs = [&](auto &&self, int u) -> void {
    dfn[u] = low[u] = ++timer;
    stack.emplace_back(u);
    on_stack[u] = true;

    for (auto [v, _] : g[u]) {
      if (dfn[v] == -1) {
        self(self, v);
        low[u] = std::min(low[u], low[v]);
      } else if (on_stack[v]) {
        low[u] = std::min(low[u], dfn[v]);
      }
    }

    if (low[u] == dfn[u]) {
      while (true) {
        int x = stack.back();
        stack.pop_back();
        on_stack[x] = false;
        comp[x] = component_count;
        if (x == u) {
          break;
        }
      }
      ++component_count;
    }
  };

  for (int i = 0; i < n; ++i) {
    if (dfn[i] == -1) {
      dfs(dfs, i);
    }
  }

  std::vector dag(component_count, std::vector<std::pair<int, long long>>());
  std::vector<int> indegree(component_count, 0);
  std::vector<long long> value(component_count, 0);

  auto collect = [&](int w) -> long long {
    long long k = std::ceil((std::sqrt(8 * w + 1) - 1) / 2.0) + 1;
    long long t = k - 1;
    return t * w - (t - 1) * t * (t + 1) / 6;
  };

  for (int u = 0; u < n; ++u) {
    for (auto [v, w] : g[u]) {
      int cu = comp[u], cv = comp[v];
      if (cu == cv) {
        value[cu] += collect(w);
        continue;
      }
      dag[cu].emplace_back(cv, w);
    }
  }

  for (int u = 0; u < component_count; ++u) {
    for (auto [v, _] : dag[u]) {
      ++indegree[v];
    }
  }

  std::queue<int> q;
  std::vector<int> topo;
  for (int i = 0; i < component_count; ++i) {
    if (!indegree[i]) {
      q.emplace(i);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    topo.emplace_back(u);

    for (auto [v, _] : dag[u]) {
      --indegree[v];
      if (!indegree[v]) {
        q.emplace(v);
      }
    }
  }

  std::vector<long long> dp(component_count, 0);
  for (int i = 0; i < component_count; ++i) {
    dp[i] = value[i];
  }
  for (int i = topo.size() - 1; i >= 0; --i) {
    int u = topo[i];
    long long best = 0;
    for (auto [v, w] : dag[u]) {
      best = std::max(best, dp[v] + w);
    }
    dp[u] += best;
  }

  std::cout << dp[comp[src]] << '\n';
}
```





<mark>（至少包含有"Accepted"）</mark>



### U30919:猫猫去旅行 

http://cs101.openjudge.cn/practice/30919

思路：



代码

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

class MedianCost {
private:
  std::priority_queue<long long> low;
  std::priority_queue<long long, std::vector<long long>, std::greater<>> high;
  long long sum_low = 0;
  long long sum_high = 0;

  void balance() {
    while (low.size() < high.size()) {
      long long x = high.top();
      high.pop();
      sum_high -= x;
      low.push(x);
      sum_low += x;
    }

    while (low.size() > high.size() + 1) {
      long long x = low.top();
      low.pop();
      sum_low -= x;
      high.push(x);
      sum_high += x;
    }
  }

public:
  void insert(long long x) {
    if (low.empty() || x <= low.top()) {
      low.push(x);
      sum_low += x;
    } else {
      high.push(x);
      sum_high += x;
    }

    balance();
  }

  auto cost() -> long long {
    if (low.empty()) {
      return 0;
    }

    long long median = low.top();
    return median * static_cast<long long>(low.size()) - sum_low + sum_high -
           median * static_cast<long long>(high.size());
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::vector<long long> x(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> x[i];
  }

  std::vector<long long> prefix(n + 1, 0);
  std::vector<long long> suffix(n + 2, 0);

  MedianCost left;
  for (int i = 1; i <= n; ++i) {
    left.insert(x[i]);
    prefix[i] = left.cost();
  }

  MedianCost right;
  for (int i = n; i >= 1; --i) {
    right.insert(x[i]);
    suffix[i] = right.cost();
  }

  long long answer = prefix[n];

  for (int t = 0; t <= n; ++t) {
    answer = std::min(answer, prefix[t] + suffix[t + 1]);
  }

  std::cout << answer * 2 << '\n';
}
```



<mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260603224555933.png)

## 2. 课程总结

如果愿意，请同学或多或少做一个本门课程的学习总结。便于之后师弟师妹跟进学习，也便于教师和助教改进教学。例如：分享自己的学习心得、笔记。

课程repo：[DSA-2026spring](https://github.com/bianwoyali-design/DSA-2026spring)
Cheat Sheet：[Cheat Sheet](https://github.com/bianwoyali-design/DSA-2026spring/blob/main/Final_cheat_sheet.md) 成功猜中最后两题，可惜做不完

本学期还是花了很多心思在数算上的，可惜成绩并不尽如人意。
做的磕磕绊绊的，T3 在输入上面卡了很久，最后发现忘记写`cin.ignore()`了，其实主要是不会写`stringstream`，早知道就选个程设了😡；
T4 也是很久没做这种计概题了，都生疏了；
T5 被强控，完全做不出，即使有约数分解的板子也难以想到；
T6 是最可惜的，一个大模版题，完全可以做出来，最后没时间了。
![一共做了224道题](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260603230048801.png)
一共做了229道题，当然其中有很多水题（

最大的收获可能不在于课内，而是重新喜欢上了 Coding 和计算机。感觉到了热爱是什么吧。
跟上了 Agent 时代的节奏，了解了很多 LLM 的信息和知识，同时对 AI 时代的学习有了自己的看法（指 Codex 辅助编程）。
计算机基础知识的入门， Linux 的使用，深刻体会到了 Windows 不是给人用的🥵。
![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/19dae9c3ae07374e62ee5090cbefed80.png)
参加了一些项目，但是大部分都烂尾了😥，希望 Clab v2 不会烂尾🙏。


