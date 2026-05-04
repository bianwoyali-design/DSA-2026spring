# DSA Assignment #9: 图（1/3）

*Updated 2026-04-28 13:47 GMT+8*
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

### M28046: 词梯

bfs, http://cs101.openjudge.cn/practice/28046/

思路：



代码：

```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>
#include <unordered_map>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::vector<std::string> words(n);
  std::unordered_map<std::string, std::vector<int>> bucket;
  for (int i = 0; i < n; ++i) {
    std::cin >> words[i];

    for (int j = 0; j < 4; ++j) {
      auto pattern = words[i];
      pattern[j] = '*';
      bucket[pattern].emplace_back(i);
    }
  }

  std::string start, end;
  std::cin >> start >> end;
  const int start_ptr =
                std::find(words.begin(), words.end(), start) - words.begin(),
            end_ptr =
                std::find(words.begin(), words.end(), end) - words.begin();

  std::queue<int> q;
  std::vector<bool> visited(n, false);
  std::vector<int> parent(n, -1);
  visited[start_ptr] = true;
  q.emplace(start_ptr);

  while (!q.empty()) {
    auto ptr = q.front();
    q.pop();

    if (ptr == end_ptr)
      break;

    for (int i = 0; i < 4; ++i) {
      auto pattern = words[ptr];
      pattern[i] = '*';

      auto ptrs = bucket[pattern];
      for (auto &&p : ptrs) {
        if (!visited[p]) {
          visited[p] = true;
          parent[p] = ptr;
          q.emplace(p);
        }
      }
    }
  }

  if (!visited[end_ptr]) {
    std::cout << "NO";
  } else {
    std::vector<std::string> path;
    for (int ptr = end_ptr; ptr != -1; ptr = parent[ptr]) {
      path.emplace_back(words[ptr]);
    }

    std::reverse(path.begin(), path.end());
    for (auto &&str : path) {
      std::cout << str << ' ';
    }
  }
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260429220845040.png"/>



### M433.最小基因变化

bfs, https://leetcode.cn/problems/minimum-genetic-mutation/


思路：



代码：

```cpp
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>


class Solution {
public:
  auto minMutation(const std::string &startGene, const std::string &endGene,
                   std::vector<std::string> &bank) -> int {
    const auto n = bank.size();

    int end_idx = -1;
    for (int i = 0; i < n; ++i) {
      if (bank[i] == endGene) {
        end_idx = i;
        break;
      }
    }
    if (end_idx == -1)
      return -1;
    if (startGene == endGene)
      return 0;

    auto bucket = _make_bucket(startGene, bank);

    std::queue<int> q;
    std::vector<bool> visited(n + 1, false);

    q.emplace(n);
    visited[n] = true;
    int steps = 0;
    while (!q.empty()) {
      ++steps;
      int sz = q.size();
      for (int k = 0; k < sz; ++k) {
        auto front = q.front();
        q.pop();

        for (int i = 0; i < 8; ++i) {
          auto pattern = front == n ? startGene : bank[front];
          pattern[i] = '*';
          for (auto &&p : bucket[pattern]) {
            if (!visited[p]) {
              if (p == end_idx)
                return steps;
              visited[p] = true;
              q.emplace(p);
            }
          }
        }
      }
    }

    return -1;
  }

private:
  auto _make_bucket(const std::string &startGene,
                    const std::vector<std::string> &bank)
      -> std::unordered_map<std::string, std::vector<int>> {
    const auto n = bank.size();
    std::unordered_map<std::string, std::vector<int>> res;

    for (int i = 0; i < 8; ++i) {
      auto pattern = startGene;
      pattern[i] = '*';
      res[pattern].emplace_back(n);
    }

    for (int i = 0; i < n; ++i) {
      const auto &gene = bank[i];

      for (int j = 0; j < 8; ++j) {
        auto pattern = gene;
        pattern[j] = '*';
        res[pattern].emplace_back(i);
      }
    }

    return res;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string start = "AAAAACCC";
  std::string end = "AACCCCCC";
  std::vector<std::string> bank = {"AAAACCCC", "AAACCCCC", "AACCCCCC"};

  Solution sol;
  std::cout << sol.minMutation(start, end, bank) << '\n';
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260429225618775.png"/>



### sy382: 有向图判环 中等

Karn, dfs, Floyd-Warshall, https://sunnywhy.com/sfbj/10/3/382

思路：



代码：

```cpp
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;

  std::vector g(n, std::vector<int>());
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    g[u].emplace_back(v);
  }

  std::vector<bool> visited(n, false);
  std::vector<bool> stack(n, false);

  auto dfs = [&](auto &&self, int node) -> bool {
    visited[node] = true;
    stack[node] = true;

    for (auto &&v : g[node]) {
      if (!visited[v] && self(self, v)) {
        return true;
      } else if (stack[v]) {
        return true;
      }
    }

    stack[node] = false;
    return false;
  };

  bool flag = false;
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      flag = dfs(dfs, i);
      if (flag) {
        break;
      }
    }
  }

  if (flag) {
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
  }
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260503204636815.png"/>



### M909.蛇梯棋

bfs, https://leetcode.cn/problems/snakes-and-ladders/

思路：



代码：

```cpp
#include <iostream>
#include <queue>
#include <vector>

class Solution {
  auto _build_targets(const std::vector<std::vector<int>> &board)
      -> std::vector<int> {
    const int side = board.size();
    std::vector<int> targets(side * side);
    int index = 0;

    bool left_to_right = true;
    for (int row = side - 1; row >= 0; --row) {
      if (left_to_right) {
        for (int col = 0; col < side; ++col) {
          targets[index] = board[row][col] == -1 ? index : board[row][col] - 1;
          ++index;
        }
      } else {
        for (int col = side - 1; col >= 0; --col) {
          targets[index] = board[row][col] == -1 ? index : board[row][col] - 1;
          ++index;
        }
      }
      left_to_right = !left_to_right;
    }

    return targets;
  }

public:
  auto snakesAndLadders(const std::vector<std::vector<int>> &board) -> int {
    const auto targets = _build_targets(board);
    const int n = targets.size();

    std::queue<int> q;
    std::vector<int> dist(n, -1);
    q.emplace(0);
    dist[0] = 0;

    while (!q.empty()) {
      int front = q.front();
      q.pop();

      if (front == n - 1) {
        return dist[front];
      }

      for (int step = 1; step <= 6 && front + step < n; ++step) {
        int next = targets[front + step];

        if (dist[next] == -1) {
          dist[next] = dist[front] + 1;
          q.emplace(next);
        }
      }
    }

    return -1;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  Solution sol;
  std::vector<std::vector<int>> board = {
      {-1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1, -1}, {-1, 35, -1, -1, 13, -1},
      {-1, -1, -1, -1, -1, -1}, {-1, 15, -1, -1, -1, -1}};
  std::cout << sol.snakesAndLadders(board) << '\n';
}

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260503212849499.png"/>



### M28050: 骑士周游

dfs, http://cs101.openjudge.cn/practice/28050/

思路：



代码

```cpp
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <vector>

class Warnsdorff {
private:
  int n{};
  int size{};
  std::bitset<19 * 19> visited;
  std::vector<std::vector<int>> g{};

  constexpr static std::array<std::array<int, 2>, 8> dist = {{{{-2, -1}},
                                                              {{-2, 1}},
                                                              {{-1, -2}},
                                                              {{-1, 2}},
                                                              {{1, -2}},
                                                              {{1, 2}},
                                                              {{2, -1}},
                                                              {{2, 1}}}};

  auto _get_id(int row, int col) -> int { return row * n + col; }

  auto _is_valid(int row, int col) -> bool {
    return row >= 0 && row < n && col >= 0 && col < n;
  }

  auto _make_graph() -> void {
    for (int row = 0; row < n; ++row) {
      for (int col = 0; col < n; ++col) {
        for (const auto &[dr, dc] : dist) {
          const int next_row = row + dr;
          const int next_col = col + dc;
          if (_is_valid(next_row, next_col)) {
            g[_get_id(row, col)].emplace_back(_get_id(next_row, next_col));
          }
        }
      }
    }
  }

  auto _get_degree(int node) -> int {
    int count = 0;
    for (auto &&v : g[node]) {
      if (!visited[v]) {
        ++count;
      }
    }
    return count;
  }

public:
  Warnsdorff(int n) : n(n), size(n * n), g(size) { _make_graph(); }

  auto check(int node, int count) -> bool {
    if (count == size) {
      return true;
    }

    std::vector<int> candidates;
    candidates.reserve(g[node].size());
    for (int v : g[node]) {
      if (!visited[v]) {
        candidates.emplace_back(v);
      }
    }

    std::sort(candidates.begin(), candidates.end(), [&](int a, int b) -> bool {
      return _get_degree(a) < _get_degree(b);
    });

    for (int next : candidates) {
      visited[next] = true;
      if (check(next, count + 1)) {
        return true;
      }
      visited[next] = false;
    }

    return false;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n = 0;
  std::cin >> n;
  int sr = 0, sc = 0;
  std::cin >> sr >> sc;

  auto g = Warnsdorff(n);
  std::cout << (g.check(sr * n + sc, 1) ? "success\n" : "fail\n");
}

```



<mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260503225623721.png"/>



### T37.解数独

backtracking, hash table, https://leetcode.cn/problems/sudoku-solver/

思路：

**位运算版数独回溯**。核心思想是：用 9 个 bit 表示数字 `1~9` 是否已经出现，比 `bool[9]` 更快也更省空间。

比如：

```cpp
1 << 0  // 数字 1
1 << 1  // 数字 2
...
1 << 8  // 数字 9
```

所以：

```cpp
constexpr std::uint16_t full_mask = (1 << 9) - 1;
```

表示低 9 位全是 `1`，也就是：

```text
111111111
```

代表数字 `1~9` 全部可选。

---

这三组数组记录已经被占用的数字：

```cpp
std::array<std::uint16_t, 9> row_mask{};
std::array<std::uint16_t, 9> col_mask{};
std::array<std::uint16_t, 9> box_mask{};
```

含义是：

```cpp
row_mask[i]  // 第 i 行已经用了哪些数字
col_mask[j]  // 第 j 列已经用了哪些数字
box_mask[k]  // 第 k 个 3x3 宫已经用了哪些数字
```

比如某一行已经有 `1, 3, 5`，那对应 mask 大概是：

```text
000010101
```

---

空格位置存在这里：

```cpp
std::array<std::uint8_t, 81> empty_box{};
int empty_count = 0;
```

因为数独最多 81 个格子，所以不用 `vector`。每个空格只存一个编号：

```cpp
i * 9 + j
```

比如第 `2` 行第 `5` 列就是：

```cpp
2 * 9 + 5
```

取出来时再还原：

```cpp
int i = empty_box[k] / 9;
int j = empty_box[k] % 9;
```

---

初始化时：

```cpp
if (board[i][j] == '.') {
  empty_box[empty_count++] = static_cast<std::uint8_t>(i * 9 + j);
} else {
  int num = static_cast<int>(board[i][j] - '1');
  auto bit = static_cast<std::uint16_t>(1 << num);
  row_mask[i] |= bit;
  col_mask[j] |= bit;
  box_mask[box_id(i, j)] |= bit;
}
```

如果是空格，就记下来。  
如果是数字，比如 `'5'`，那么：

```cpp
num = '5' - '1' = 4
bit = 1 << 4
```

然后把这个数字标记到对应的行、列、宫里。

---

这个函数计算某个格子还能填哪些数字：

```cpp
auto get_candidates = [&](int i, int j) -> std::uint16_t {
  return static_cast<std::uint16_t>(
      full_mask & ~(row_mask[i] | col_mask[j] | box_mask[box_id(i, j)]));
};
```

这一句是整份代码最关键的地方。

```cpp
row_mask[i] | col_mask[j] | box_mask[box_id(i, j)]
```

表示这个格子的行、列、宫里已经出现过的数字。

然后取反：

```cpp
~(...)
```

得到“没出现过的数字”。

再和 `full_mask` 相与：

```cpp
full_mask & ~(...)
```

只保留低 9 位，得到合法候选数字。

---

DFS 部分：

```cpp
auto dfs = [&](this auto &&self, int index) -> bool
```

`index` 表示当前要填第几个空格。  
如果所有空格都填完了：

```cpp
if (index == empty_count) {
  return true;
}
```

说明数独解出来了。

---

每一层递归都会选一个“候选数最少”的空格：

```cpp
int best_index = index;
std::uint16_t best_candidates = 0;
int best_count = 10;
```

然后扫描剩下没填的空格：

```cpp
for (int k = index; k < empty_count; ++k) {
  int i = empty_box[k] / 9;
  int j = empty_box[k] % 9;
  std::uint16_t candidates = get_candidates(i, j);
  int count = std::popcount(static_cast<unsigned>(candidates));
```

`std::popcount` 统计候选 mask 里有几个 `1`，也就是有几个可填数字。

比如：

```text
001010001
```

有 3 个 `1`，说明有 3 个候选数字。

选择候选数最少的格子，这是一个经典优化，叫 **MRV：Minimum Remaining Values**。它可以让搜索树小很多。

---

如果某个格子没有候选数：

```cpp
if (best_count == 0) {
  return false;
}
```

说明当前走法错了，回溯。

---

选中最优空格后，把它换到当前 `index` 位置：

```cpp
std::swap(empty_box[index], empty_box[best_index]);
```

这样后续递归只需要处理 `index + 1` 之后的空格。

---

枚举候选数字：

```cpp
while (candidates != 0) {
  auto bit = static_cast<std::uint16_t>(candidates & -candidates);
```

这句取出最低位的 `1`。

比如：

```text
candidates = 001010100
bit        = 000000100
```

然后：

```cpp
int num = std::countr_zero(static_cast<unsigned>(bit));
```

`std::countr_zero` 统计末尾有多少个 `0`，也就是这个 bit 对应的数字下标。

比如：

```text
000010000
```

末尾有 4 个 `0`，说明是 `num = 4`，对应数字 `'5'`。

所以：

```cpp
board[i][j] = static_cast<char>('1' + num);
```

把数字填进棋盘。

---

填入后更新状态：

```cpp
row_mask[i] |= bit;
col_mask[j] |= bit;
box_mask[box] |= bit;
```

表示这个数字已经被当前行、列、宫使用了。

然后继续递归：

```cpp
if (self(index + 1)) {
  return true;
}
```

如果后面成功，就一路返回 `true`。

---

如果失败，需要撤销刚才的选择：

```cpp
row_mask[i] ^= bit;
col_mask[j] ^= bit;
box_mask[box] ^= bit;
```

这里用 `^=` 是因为这个 bit 一定是刚刚加进去的，所以异或一次就能清掉。

然后：

```cpp
candidates ^= bit;
```

从候选集合里删除刚试过的数字，继续试下一个。

---

如果所有候选都试完了还不行：

```cpp
board[i][j] = '.';
std::swap(empty_box[index], empty_box[best_index]);
return false;
```

恢复棋盘和空格顺序，回溯到上一层。

---

整体流程就是：

```text
1. 扫描棋盘，建立行/列/宫 mask
2. 记录所有空格
3. DFS：
   选择候选数最少的空格
   枚举它的候选数字
   填入并更新 mask
   递归
   失败则撤销
4. 全部空格填完，结束
```

这份写法相比普通 `bool row[9][9]` 的优势是：

```text
候选计算更快：一次位运算得到所有候选
枚举更快：每次取最低位 1
内存更小：mask 只用 16 位
搜索更少：每层优先填候选最少的空格
```

代码

```cpp
#include <array>
#include <bit>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

class Solution {
public:
  auto solveSudoku(std::vector<std::vector<char>> &board) -> void {
    constexpr std::uint16_t full_mask = (1 << 9) - 1;
    std::array<std::uint16_t, 9> row_mask{};
    std::array<std::uint16_t, 9> col_mask{};
    std::array<std::uint16_t, 9> box_mask{};
    std::array<int, 81> empty_box{};
    int empty_count = 0;

    auto box_id = [](int i, int j) -> int { return i / 3 * 3 + j / 3; };

    auto add_digit = [&](int i, int j, int box, std::uint16_t bit) -> void {
      row_mask[i] |= bit;
      col_mask[j] |= bit;
      box_mask[box] |= bit;
    };
    auto remove_digit = [&](int i, int j, int box, std::uint16_t bit) -> void {
      row_mask[i] ^= bit;
      col_mask[j] ^= bit;
      box_mask[box] ^= bit;
    };

    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        if (board[i][j] == '.') {
          empty_box[empty_count++] = i * 9 + j;
        } else {
          int num = static_cast<int>(board[i][j] - '1');
          add_digit(i, j, box_id(i, j), static_cast<std::uint16_t>(1u << num));
        }
      }
    }

    auto get_candidates = [&](int i, int j) -> std::uint16_t {
      return static_cast<std::uint16_t>(
          full_mask & ~(row_mask[i] | col_mask[j] | box_mask[box_id(i, j)]));
    };

    auto dfs = [&](this auto &&self, int index) -> bool {
      if (index == empty_count) {
        return true;
      }

      int best_index = index;
      std::uint16_t best_candidates = 0;
      int best_count = 10;
      for (int k = index; k < empty_count; ++k) {
        int i = empty_box[k] / 9;
        int j = empty_box[k] % 9;
        std::uint16_t candidates = get_candidates(i, j);
        int count = std::popcount(static_cast<unsigned>(candidates));
        if (count < best_count) {
          best_index = k;
          best_candidates = candidates;
          best_count = count;
          if (count == 1) {
            break;
          }
        }
      }

      if (best_count == 0) {
        return false;
      }

      std::swap(empty_box[index], empty_box[best_index]);
      int i = empty_box[index] / 9;
      int j = empty_box[index] % 9;
      int box = box_id(i, j);
      std::uint16_t candidates = best_candidates;

      while (candidates != 0) {
        auto bit = static_cast<std::uint16_t>(candidates & -candidates);
        int num = std::countr_zero(static_cast<unsigned>(bit));
        board[i][j] = static_cast<char>('1' + num);
        add_digit(i, j, box, bit);

        if (self(index + 1)) {
          return true;
        }

        remove_digit(i, j, box, bit);
        candidates ^= bit;
      }

      std::swap(empty_box[index], empty_box[best_index]);
      return false;
    };

    dfs(0);
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<std::vector<char>> board{
      {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
      {'.', '.', '.', '.', '8', '.', '.', '7', '9'},
  };
  Solution sol;
  sol.solveSudoku(board);

  for (auto &&row : board) {
    for (auto [i, v] : std::views::zip(std::views::iota(0), row)) {
      std::cout << v << " \n"[i == 8];
    }
  }
}

```



<mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260504120835598.png"/>



## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2026spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>





