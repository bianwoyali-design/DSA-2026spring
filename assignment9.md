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

```python

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>





### M909.蛇梯棋

bfs, https://leetcode.cn/problems/snakes-and-ladders/

思路：



代码：

```python

```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>





### M28050: 骑士周游

dfs, http://cs101.openjudge.cn/practice/28050/

思路：



代码

```python

```



<mark>（至少包含有"Accepted"）</mark>





### T37.解数独

backtracking, hash table, https://leetcode.cn/problems/sudoku-solver/

思路：



代码

```python

```



<mark>（至少包含有"Accepted"）</mark>





## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2026spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>





