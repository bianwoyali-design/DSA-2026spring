# DSA Assignment #5: 20260401 cs201 Mock Exam

*Updated 2026-04-01 15:20 GMT+8*
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

### E02039: 反反复复	

matrix, http://cs101.openjudge.cn/practice/02039/

思路：



代码：

```python
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int col;
  std::cin >> col;
  std::string s;
  std::cin >> s;

  std::vector<std::vector<char>> matrix;
  std::vector<char> row;
  for (const auto c : s) {
    row.emplace_back(c);
    if (row.size() == col) {
      if (matrix.size() % 2 == 0) {
        matrix.emplace_back(std::move(row));
      } else {
        std::reverse(row.begin(), row.end());
        matrix.emplace_back(std::move(row));
      }
    }
  }

  for (int i = 0; i < col; ++i)
    for (auto &j : matrix)
      std::cout << j[i];
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260401210935443.png"/>



### E02092: Grandpa is Famous	

implementation, http://cs101.openjudge.cn/practice/02092/


思路：



代码：

```python
#include <iostream>
#include <map>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N, M;
  while (std::cin >> N >> M && M != 0 && N != 0) {
    std::map<int, int> status;
    for (int i = 0; i < M; ++i)
      for (int j = 0; j < N; ++j) {
        int id;
        std::cin >> id;
        ++status[id];
      }

    int max_score = 0;
    for (const auto &m : status)
      max_score = std::max(max_score, m.second);

    int second_score = 0;
    for (const auto &m : status)
      if (m.second > second_score && m.second < max_score)
        second_score = m.second;

    for (const auto &m : status)
      if (m.second == second_score)
        std::cout << m.first << ' ';
    std::cout << '\n';
  }
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>



<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260401211442882.png"/>

### M02774: 木材加工	

binary search, http://cs101.openjudge.cn/practice/02774/

思路：



代码：

```python
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N, K;
  std::cin >> N >> K;
  std::vector<int> length(N);
  for (auto &l : length)
    std::cin >> l;

  auto check = [&](int len) -> bool {
    int num = 0;
    for (const auto &l : length)
      num += (l / len);
    return num >= K;
  };

  int l = 1, r = *std::max_element(length.begin(), length.end());
  int ans = 0;
  while (l <= r) {
    int mid = l + ((r - l) >> 1);
    if (check(mid)) {
      ans = mid;
      l = mid + 1;
    } else
      r = mid - 1;
  }

  std::cout << ans << '\n';
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260401211938682.png"/>



### M04077: 出栈序列统计

dp, dfs, math, http://cs101.openjudge.cn/practice/04077/

思路：
Catalan数 $𝐶_𝑛$ 的递推关系有着天然的递归结构：规模为 $𝑛$ 的计数问题 $𝐶_𝑛$ ，可以通过枚举分界点，分拆为两个规模分别为 $𝑖$ 和 $(𝑛−1-𝑖)$ 的子问题。这一递推关系使得Catalan数广泛出现于各类具有类似递归结构的问题中。

**路径计数问题**：有一个大小为 $n\times n$ 的方格图，左下角为 $(0,0)(0, 0)$，右上角为 $(𝑛,𝑛)(n, n)$ 。从左下角开始，每次都只能向右或者向上走一单位，不走到对角线 $y=x$ 上方（但可以触碰）的情况下，到达右上角的路径总数为 $C_n$ 。

**圆内不相交弦计数问题**：圆上有 $2n$ 个点，将这些点成对连接起来且使得所得到的 $n$ 条线段两两不交的方案数是 $C_n$。

**三角剖分计数问题**：对角线不相交的情况下，将一个凸 $(n + 2)$ 边形区域分成三角形区域的方法数为 $C_n$ 。

**二叉树计数问题**：含有 $n$ 个结点的形态不同的二叉树数目为 $C_n$ 。等价地，含有 $n$ 个非叶结点的形态不同的满二叉树数目为 $C_{n}$ 。

**括号序列计数问题**：由 $n$ 对括号构成的合法括号序列数为 $C_n$ 。

**出栈序列计数问题**：一个栈（无穷大）的进栈序列为 $1,2,3, \ldots ,n$ ，合法出栈序列的数目为 $C_n$ 。

**数列计数问题**：由 $n$ 个 $+1$ 和 $n$ 个 $-1$ 组成的数列 $a_1,a_2, \ldots ,a_{2n}$ 中，部分和满足 $a_1+a_2+ \ldots +a_k \geq 0~(k=1,2,3, \ldots ,2n)$ 的数列数目为 $C_n$ 。


$C_n = \frac{(4n - 2)}{n + 1} C_{n-1},\ n > 0,\ C_0 = 1.$


代码：

```python
#include <iostream>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  int c_prev = 1;
  int c_curr = 1;
  for (int i = 1; i <= n; ++i) {
    c_prev = c_curr;
    c_curr = (4 * i - 2) * c_prev / (i + 1);
  }
  std::cout << c_curr << '\n';
}
```



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260401212053491.png"/>



### M30637: 合法出栈序列pub

stack, http://cs101.openjudge.cn/practice/M30637/

思路：



代码

```python
#include <iostream>
#include <stack>
#include <string>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string s;
  std::getline(std::cin, s);
  std::string ipt;
  while (std::getline(std::cin, ipt)) {
    if (!ipt.empty() && ipt.back() == '\r')
      ipt.pop_back();
    if (s.length() != ipt.length()) {
      std::cout << "NO\n";
      continue;
    }

    std::stack<char> st;
    int i = 0, j = 0;
    while (j < ipt.length()) {
      if (!st.empty() && st.top() == ipt[j]) {
        st.pop();
        ++j;
      } else if (i < s.length()) {
        st.push(s[i]);
        ++i;
      } else {
        break;
      }
    }

    if (j == ipt.length())
      std::cout << "YES\n";
    else
      std::cout << "NO\n";
  }
}
```



<mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260401212219868.png"/>



### T30102:完美交易窗口

monotonic stack, http://cs101.openjudge.cn/practice/T30102/

思路：



代码

```python
#include <iostream>
#include <vector>
#include <algorithm>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<int> h(n);
  for (auto &v : h)
    std::cin >> v;

  std::vector<int> st_max;
  std::vector<int> st_min;

  int ans = 0;
  for (int j = 0; j < n; ++j) {
    while (!st_max.empty() && h[st_max.back()] < h[j])
      st_max.pop_back();

    int left_border = st_max.empty() ? -1 : st_max.back();

    while (!st_min.empty() && h[st_min.back()] >= h[j])
      st_min.pop_back();

    if (!st_min.empty()) {
      auto it = std::upper_bound(st_min.begin(), st_min.end(), left_border);
      if (it != st_min.end()) {
        int min_l = *it;
        ans = std::max(ans, j - min_l + 1);
      }
    }

    st_max.emplace_back(j);
    st_min.emplace_back(j);
  }

  std::cout << ans << '\n';
}
```



<mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260401213839569.png"/>



## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2026spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>





