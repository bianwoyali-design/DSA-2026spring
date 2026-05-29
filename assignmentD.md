# DSA Assignment D: 20260527模拟考

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

### M27351:01最小生成树

补图的连通分量, http://cs101.openjudge.cn/practice/27351

思路：



代码：

```cpp
#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <tuple>
#include <vector>

class DSU {
private:
  std::vector<int> parent;
  std::vector<int> rank;

public:
  explicit DSU(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  auto Find(int x) -> int {
    if (parent[x] == x) {
      return x;
    }
    return parent[x] = Find(parent[x]);
  }

  auto Union(int x, int y) -> bool {
    int root_x = Find(x);
    int root_y = Find(y);
    if (root_x == root_y) {
      return false;
    }

    if (rank[root_x] < rank[root_y]) {
      parent[root_x] = root_y;
    } else if (rank[root_x] > rank[root_y]) {
      parent[root_y] = root_x;
    } else {
      parent[root_x] = root_y;
      ++rank[root_y];
    }
    return true;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector<std::tuple<int, int, int>> edge;
  edge.reserve(m);
  std::vector neighbor(n, std::vector<int>());
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    edge.emplace_back(1, u, v);
    neighbor[u].emplace_back(v);
    neighbor[v].emplace_back(u);
  }

  int comp_count = 0;
  std::vector comp(n, -1);
  std::list<int> unvisited;
  for (int i = 0; i < n; ++i) {
    unvisited.emplace_back(i);
  }
  std::vector<int> marked(n, 0);
  int stamp = 0;

  while (!unvisited.empty()) {
    int start = unvisited.front();
    unvisited.pop_front();
    comp[start] = comp_count;

    std::queue<int> q;
    q.emplace(start);

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      ++stamp;
      for (int v : neighbor[u]) {
        marked[v] = stamp;
      }

      for (auto it = unvisited.begin(); it != unvisited.end();) {
        int v = *it;

        if (marked[v] != stamp) {
          comp[v] = comp_count;
          q.emplace(v);
          it = unvisited.erase(it);
        } else {
          ++it;
        }
      }
    }

    ++comp_count;
  }

  std::sort(edge.begin(), edge.end());
  long long mst_weight = 0;
  int count = 0;
  DSU dsu(comp_count);
  for (auto &&[w, u, v] : edge) {
    if (count == comp_count - 1) {
      break;
    }

    int cu = comp[u];
    int cv = comp[v];
    if (cu != cv && dsu.Union(cu, cv)) {
      mst_weight += w;
      ++count;
    }
  }

  std::cout << mst_weight << '\n';
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>


![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260529155541662.png)


### M30910:邮递员送快递

正向/反向图 Dijkstra, http://cs101.openjudge.cn/practice/30910


思路：



代码：

```cpp
#include <iostream>
#include <queue>
#include <vector>

auto dijkstra(int start,
              const std::vector<std::vector<std::pair<int, int>>> &adj) -> int {
  int n = adj.size();
  constexpr static int INF = 1e9;
  std::vector<int> dist(n, INF);
  dist[start] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<>>
      pq;
  pq.emplace(0, start);

  while (!pq.empty()) {
    auto [du, u] = pq.top();
    pq.pop();
    if (du > dist[u])
      continue;
    for (auto [v, weight] : adj[u]) {
      if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.emplace(dist[v], v);
      }
    }
  }

  int time = 0;
  for (int i = 1; i < n; ++i) {
    time += dist[i];
  }
  return time;
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  std::vector adj1(n, std::vector<std::pair<int, int>>());
  std::vector adj2(n, std::vector<std::pair<int, int>>());
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    adj1[u].emplace_back(v, w);
    adj2[v].emplace_back(u, w);
  }

  int time = 0;
  time += dijkstra(0, adj1);
  time += dijkstra(0, adj2);

  std::cout << time << '\n';
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260529155831579.png)


### M30912:累加树

构建 BST + 右-根-左累加 + BFS 输出, http://cs101.openjudge.cn/practice/30912

思路：



代码：

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

struct BSTNode {
    int value;
    BSTNode *left{};
    BSTNode *right{};
    explicit BSTNode(int value) :value(value) {}
};

class TreeUtils {
private:
    auto insertNode(BSTNode *root, int value) -> BSTNode * {
        if (!root)
            return new BSTNode(value);
        if (value < root->value)
            root->left = insertNode(root->left, value);
        else
            root->right = insertNode(root->right, value);
        return root;
    }
public:
    auto buildBST(const std::vector<int> &data) -> BSTNode * {
        BSTNode *root = nullptr;
        for (int i = 0; i < data.size(); ++i)
            root = insertNode(root, data[i]);
        return root;
    }
};

auto main() -> int {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::vector<int> data(n);
    for (auto &d : data)
        std::cin >> d;
    
    TreeUtils bst;
    auto root = bst.buildBST(data);
    
    std::sort(data.rbegin(), data.rend());
    std::vector<int> prefix(n, 0);
    prefix[0] = data[0];
    for (int i = 1; i < n; ++i){
        prefix[i] = prefix[i - 1] + data[i];
    }
    std::reverse(prefix.begin(), prefix.end());

    std::queue<BSTNode *> q;
    q.emplace(root);
    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            auto front = q.front();
            q.pop();
            std::cout << prefix[static_cast<int>(std::lower_bound(data.rbegin(), data.rend(), front->value) - data.rbegin())] << ' ';

            if (front->left) {
                q.emplace(front->left);
            }
            if (front->right){
                q.emplace(front->right);
            }
        }
    }
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260529155924323.png)



### M30899:火星大工程

关键路径, http://cs101.openjudge.cn/practice/30899

思路：



代码：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

auto main() -> int {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;
    
    std::vector adj(n, std::vector<std::pair<int, int>>());
    std::vector<std::tuple<int, int, int>> edges;
    std::vector<int> indegree(n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v, w);
        edges.emplace_back(u, v, w);
        ++indegree[v];
    }

    std::queue<int> q;
    std::vector<int> topo;
    std::vector<long long> ve(n, 0);

    for (int i = 0; i < n; ++i) {
        if (!indegree[i]) {
            q.emplace(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);

        for (auto [v, w] :adj[u]) {
            ve[v] = std::max(ve[v], ve[u] + w);
            if (--indegree[v] == 0) {
                q.emplace(v);
            }
        }
    }

    long long project_time = *std::max_element(ve.begin(), ve.end());

    std::vector<long long>vl(n, project_time);
    for (int i = n - 1; i >= 0; --i) {
        int u = topo[i];
        for (auto [v, w] : adj[u]) {
            vl[u] = std::min(vl[u], vl[v] - w);
        }
    }

    std::vector<std::pair<int, int>> critical_path;
    for (auto [u, v, w] : edges) {
        long long earliest = ve[u];
        long long latest = vl[v] - w;
        if (earliest == latest) {
            critical_path.emplace_back(u, v);
        }
    }

    std::cout << project_time << '\n';
    std::sort(critical_path.begin(), critical_path.end(), [](std::pair<int, int> &a, std::pair<int, int> b) -> bool { if (a.first == b.first) return a.second < b.second; return a.first < b.first;});
    for (auto [u, v] : critical_path) {
        std::cout << ++u << ' ' << ++v << '\n';
    }
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260529155701374.png)



### T30868:upstairs

同余最短路, http://cs101.openjudge.cn/practice/30868

思路：



代码

```cpp
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  long long a, b, c;
  std::cin >> a >> b >> c;

  std::vector<long long> step;
  for (long long x : {a, b, c}) {
    if (x > 0) {
      step.push_back(x);
    }
  }

  if (step.empty()) {
    int q;
    std::cin >> q;
    while (q--) {
      long long tgt;
      std::cin >> tgt;
      std::cout << (tgt == 0 ? "Yes\n" : "No\n");
    }
    return 0;
  }

  int mod = static_cast<int>(*std::min_element(step.begin(), step.end()));
  int start = 0;
  constexpr static long long INF = 4e18;

  std::vector<long long> dist(mod, INF);
  dist[start] = start;
  std::priority_queue<std::pair<long long, int>,
                      std::vector<std::pair<long long, int>>, std::greater<>>
      pq;
  pq.emplace(dist[start], start);

  while (!pq.empty()) {
    auto [du, u] = pq.top();
    pq.pop();

    if (du != dist[u])
      continue;

    for (long long w : step) {
      int v = static_cast<int>((u + w) % mod);
      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pq.emplace(dist[v], v);
      }
    }
  }

  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    long long tgt;
    std::cin >> tgt;
    int r = static_cast<int>(tgt % mod);
    if (dist[r] != INF && dist[r] <= tgt) {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  }
}
```



<mark>（至少包含有"Accepted"）</mark>


![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260529160024140.png)


### T30921:猫猫搭积木

并查集, http://cs101.openjudge.cn/practice/30921

思路：



代码

```cpp
#include <iostream>
#include <numeric>
#include <vector>

class DisjSet {
private:
  int n;
  std::vector<int> parent;
  std::vector<int> size;
  std::vector<std::vector<int>> member;

public:
  explicit DisjSet(int n) : n(n), parent(n), size(n, 1), member(n) {
    std::iota(parent.begin(), parent.end(), 0);
    for (int i = 0; i < n; ++i) {
      member[i].emplace_back(i);
    }
  }

  auto find(int x) -> int { return parent[x] == x ? x : find(parent[x]); }

  auto unite(int x, int y, int s) -> int {
    int root_x = find(x);
    int root_y = find(y);

    if (root_x == root_y) {
      return n;
    }

    if (size[root_x] < size[root_y]) {
      std::swap(root_x, root_y);
    }

    size[root_x] += size[root_y];
    for (auto m : member[root_y]) {
      parent[m] = root_x;
      member[root_x].emplace_back(m);
    }
    member[root_y].clear();

    --n;

    if (size[root_x] >= s) {
      n += size[root_x] - 1;
      auto nodes = std::move(member[root_x]);
      for (auto m : nodes) {
        parent[m] = m;
        size[m] = 1;
        member[m].clear();
        member[m].emplace_back(m);
      }
    }

    return n;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, q, s;
  std::cin >> n >> q >> s;
  DisjSet dsu(n);
  while (q--) {
    int a, b;
    std::cin >> a >> b;
    --a;
    --b;
    std::cout << dsu.unite(a, b, s) << '\n';
  }
}
```



<mark>（至少包含有"Accepted"）</mark>


![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260529160106788.png)


## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2026spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>





