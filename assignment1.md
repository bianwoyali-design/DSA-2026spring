# Assignment #1: OOP

*Updated 2026-03-03 11:25 GMT+8*
 *Compiled by <mark>张真铭 元培学院</mark> (2026 Spring)*



**作业的各项评分细则及对应的得分**

| 标准                                 | 等级                                                         | 得分 |
| ------------------------------------ | ------------------------------------------------------------ | ---- |
| 按时提交                             | 完全按时提交：1分<br/>提交有请假说明：0.5分<br/>未提交：0分  | 1 分 |
| 源码、耗时（可选）、解题思路（可选） | 提交了4个或更多题目且包含所有必要信息：1分<br/>提交了2个或以上题目但不足4个：0.5分<br/>少于2个：0分 | 1 分 |
| AC代码截图                           | 提交了4个或更多题目且包含所有必要信息：1分<br/>提交了2个或以上题目但不足4个：0.5分<br/>少于：0分 | 1 分 |
| 清晰头像、PDF文件、MD/DOC附件        | 包含清晰的Canvas头像、PDF文件以及MD或DOC格式的附件：1分<br/>缺少上述三项中的任意一项：0.5分<br/>缺失两项或以上：0分 | 1 分 |
| 学习总结和个人收获                   | 提交了学习总结和个人收获：1分<br/>未提交学习总结或内容不详：0分 | 1 分 |
| 总得分： 5                           | 总分满分：5分                                                |      |
>
>
>
>**说明：**
>
>1. **解题与记录：**
>
>      对于每一个题目，请提供其解题思路（可选），并附上使用Python或C++编写的源代码（确保已在OpenJudge， Codeforces，LeetCode等平台上获得Accepted）。请将这些信息连同显示“Accepted”的截图一起填写到下方的作业模板中。（推荐使用Typora https://typoraio.cn 进行编辑，当然你也可以选择Word。）无论题目是否已通过，请标明每个题目大致花费的时间。
>
>2. **课程平台：**课程网站位于Canvas平台（https://pku.instructure.com ）。该平台将在<mark>第2周</mark>选课结束后正式启用。在平台启用前，请先完成作业并将作业妥善保存。待Canvas平台激活后，再上传你的作业。
>
>3. **提交安排：**提交时，请首先上传PDF格式的文件，并将.md或.doc格式的文件作为附件上传至右侧的“作业评论”区。确保你的Canvas账户有一个清晰可见的本人头像，提交的文件为PDF格式，并且“作业评论”区包含上传的.md或.doc附件。
>3. **延迟提交：**如果你预计无法在截止日期前提交作业，请提前告知具体原因。这有助于我们了解情况并可能为你提供适当的延期或其他帮助。  
>
>请按照上述指导认真准备和提交作业，以保证顺利完成课程要求。



## 1. 题目

### E27653: Fraction类

OOP, http://cs101.openjudge.cn/pctbook/E27653/

> 主要是练习面向对象编程写法，这样力扣题目，笔试都没有问题了。机考时候，不是必须OOP，能AC就可以。
>

思路：



代码：

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

class Fraction
{
public:
    void plus(int a, int b, int c, int d)
    {
        int numerator = a * d + b * c;
        int lcm = b * d;
        int gcd2 = abs(__gcd(lcm, numerator));
        if (lcm / gcd2 != 1)
            cout << numerator / gcd2 << '/' << lcm / gcd2 << '\n';
        else
            cout << numerator / gcd2 << '\n';
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Fraction frac;
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    frac.plus(a, b, c, d);
    return 0;
}
```

>共用时5min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>
![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260303172851760.png)




### E190.颠倒二进制位

bit manipulation, https://leetcode.cn/problems/reverse-bits/


思路：
掩码


代码：

```cpp
#include <iostream>
using namespace std;

class Solution
{
private:
    const uint32_t M1 = 0x55555555; // 01010101010101010101010101010101
    const uint32_t M2 = 0x33333333; // 00110011001100110011001100110011
    const uint32_t M4 = 0x0f0f0f0f; // 00001111000011110000111100001111
    const uint32_t M8 = 0x00ff00ff; // 00000000111111110000000011111111

public:
    uint32_t reverseBits(uint32_t n)
    {
        n = n >> 1 & M1 | (n & M1) << 1;
        n = n >> 2 & M2 | (n & M2) << 2;
        n = n >> 4 & M4 | (n & M4) << 4;
        n = n >> 8 & M8 | (n & M8) << 8;
        return n >> 16 | n << 16;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    uint32_t n = 43261596;
    cout << sol.reverseBits(n) << '\n';
    return 0;
}
```

>共用时10min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260303225648710.png)



### E1356.根据数字二进制下 1 的数目排序

bit manipulation, https://leetcode.cn/problems/sort-integers-by-the-number-of-1-bits/

思路：



代码：

```cpp
#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> sortByBits(vector<int> &arr)
    {
        vector<int> bit(10001, 0);
        for (int i = 0; i < 10001; ++i)
            bit[i] = bit[i >> 1] + (i & 1);

        ranges::sort(arr, [&](int x, int y)
                     {
            if (bit[x] < bit[y])
                return true;
            if (bit[x] > bit[y])
                return false;
            return x < y; });

        return arr;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    for (auto a : sol.sortByBits(arr))
        cout << a << ' ';
    return 0;
}
```

>共用时10min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260303225840993.png)



### M27300: 模型整理

sortings, AI, http://cs101.openjudge.cn/pctbook/M27300/



思路：



代码：

```cpp
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;
    map<string, vector<string>> mp;
    while (n--)
    {
        string str;
        cin >> str;
        int it = str.find("-");
        string first = str.substr(0, it);
        string second = str.substr(it + 1);
        mp[first].push_back(second);
    }

    for (auto &sub : mp)
    {
        sort(sub.second.begin(), sub.second.end(), [](const string &a, const string &b) {
            if (a.back() == b.back())
                return stod(a.substr(0, a.size() - 1)) < stod(b.substr(0, b.size() - 1));
            return a.back() > b.back();
        });
        cout << sub.first << ": ";
        for (int i = 0; i < sub.second.size(); i++)
        {
            cout << sub.second[i];
            if (i != sub.second.size() - 1)
                cout << ", ";
            else
                cout << '\n';
        }
    }
    return 0;
}
```
>共用时5min


代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260303225910768.png)



### M1536.排布二进制网格的最少交换次数

greedy, matrix, https://leetcode.cn/problems/minimum-swaps-to-arrange-a-binary-grid/



思路：



代码：

```cpp
#include <iostream>
#include <ranges>
#include <vector>
using namespace std;

class Solution
{
private:
    int collect(vector<int> row)
    {
        int i = row.size() - 1;
        while (i >= 0 && row[i] == 0)
            --i;
        return row.size() - i - 1;
    }

public:
    int minSwaps(vector<vector<int>> &grid)
    {
        int n = grid.size();
        vector<int> counter(n);
        for (auto [i, v] : grid | views::enumerate)
            counter[i] = collect(v);

        int steps = 0;
        for (int i = 0; i < n; ++i)
        {
            if (counter[i] < n - i - 1)
            {
                for (int j = i + 1; j < n; ++j)
                {
                    swap(counter[i], counter[j]);
                    ++steps;
                    if (counter[i] >= n - i - 1)
                        break;
                }
                if (counter[i] < n - i - 1)
                    return -1;
            }
        }

        return steps;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    vector<vector<int>> grid = {{0, 0, 1}, {1, 1, 0}, {1, 0, 0}};
    cout << sol.minSwaps(grid) << '\n';
    return 0;
}
```

>共用时20min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>
![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260303230021184.png)


### T20052:最大点数（同2048规则）

dfs, matrices, http://cs101.openjudge.cn/pctbook/T20052/

思路：
平衡了一下耗时和内存占用，用了脏标记、剪枝和move函数。

可以加个记忆化搜索和bitset压缩内存占用，但是太难写了，Gemini大人写出来的也报错，就没有深究了。


代码：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

enum class Direction
{
    Left,
    Right,
    Up,
    Down
};

class Solution
{
private:
    int p;
    int maxVal;

    bool process(vector<int> &row)
    {
        int n = row.size();
        vector<int> nextRow(n, 0);
        int writeIdx = 0;
        bool changed = false; // Dirty flag
        for (int i = 0; i < n; ++i)
            if (row[i])
                nextRow[writeIdx++] = row[i];

        for (int i = 0; i < writeIdx - 1; ++i)
        {
            if (nextRow[i] != 0 && nextRow[i] == nextRow[i + 1])
            {
                nextRow[i] *= 2;
                maxVal = max(maxVal, nextRow[i]);

                for (int j = i + 1; j < writeIdx - 1; ++j)
                    nextRow[j] = nextRow[j + 1];
                nextRow[--writeIdx] = 0;
                changed = true;
            }
        }

        if (!changed)
            for (int i = 0; i < n; ++i)
                if (row[i] != nextRow[i])
                {
                    changed = true;
                    break;
                }

        row = move(nextRow);
        return changed;
    }

    bool moveBoard(vector<vector<int>> &grid, Direction dir)
    {
        int m = grid.size(), n = grid[0].size();
        bool gridChanged = false;

        if (dir == Direction::Left || dir == Direction::Right)
            for (auto &g : grid)
            {
                if (dir == Direction::Right)
                    reverse(g.begin(), g.end());
                if (process(g))
                    gridChanged = true;
                if (dir == Direction::Right)
                    reverse(g.begin(), g.end());
            }
        else
            for (int j = 0; j < n; ++j)
            {
                vector<int> v;
                for (auto &g : grid)
                    v.emplace_back(g[j]);
                if (dir == Direction::Down)
                    reverse(v.begin(), v.end());
                if (process(v))
                    gridChanged = true;
                if (dir == Direction::Down)
                    reverse(v.begin(), v.end());
                for (int i = 0; i < m; ++i)
                    grid[i][j] = v[i];
            }

        return gridChanged;
    }

    void dfs(vector<vector<int>> grid, int steps)
    {
        if (steps == p)
            return;

        vector<vector<int>> backup = grid;
        for (auto dir : {Direction::Left, Direction::Right, Direction::Up, Direction::Down})
            // 如果棋盘发生了变化，才继续向下搜索
            if (moveBoard(grid, dir))
            {
                dfs(move(grid), steps + 1);
                grid = backup;
            }
        // move()直接移动，直接把 grid 的所有权移交给下一层递归函数，极大地减少了内存分配和数据复制带来的延迟
    }

public:
    explicit Solution(int p) : p(p), maxVal(0) {}

    int maximumPoint(vector<vector<int>> grid)
    {
        for (const auto &row : grid)
            for (int val : row)
                maxVal = max(maxVal, val);
        dfs(grid, 0);
        return maxVal;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int m, n, p;
    cin >> m >> n >> p;
    vector<vector<int>> grid(m, vector<int>(n));

    for (auto &g : grid)
        for (auto &v : g)
            cin >> v;

    Solution sol(p);
    cout << sol.maximumPoint(grid) << '\n';
    return 0;
}
```
>共用时50min


代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260304163509940.png)



## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>


### LC 1680

```cpp
#include <iostream>
#include <numeric>
using namespace std;

class Solution
{
public:
    int concatenatedBinary(int n)
    {
        constexpr int MOD = 1000000007;
        long long res = 0;
        for (int i = 1; i <= n; ++i)
        {
            int w = bit_width((uint32_t)i);
            res = (res << w | i) % MOD;
        }
        return res;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    int n = 12;
    cout << sol.concatenatedBinary(n) << '\n';
    return 0;
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260304165509214.png)


### LC 155

```cpp
#include <iostream>
#include <climits>
#include <stack>
using namespace std;

class MinStack
{
private:
    stack<int> st;
    stack<int> min_st;
public:
    MinStack()
    {
        min_st.push(INT_MAX);
    }

    void push(int val)
    {
        st.push(val);
        min_st.push(min(min_st.top(), val));
    }

    void pop()
    {
        st.pop();
        min_st.pop();
    }

    int top()
    {
        return st.top();
    }

    int getMin()
    {
        return min_st.top();
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << minStack.getMin() << '\n';
    minStack.pop();
    cout << minStack.top() << '\n';
    cout << minStack.getMin() << '\n';
    return 0;
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260304165730779.png)

### LC 868

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int binaryGap(int n)
    {
        int last = -1, ans = 0;
        for (int i = 0; n; ++i)
        {
            if (n & 1)
            {
                if (last != -1)
                    ans = max(ans, i - last);
                last = i;
            }
            n >>= 1;
        }

        return ans;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    cout << sol.binaryGap(22) << '\n';
    return 0;
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260307101552434.png)

### LC 1404

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int numSteps(string s)
    {
        int ans = 0, n = s.length();
        bool flag = false;
        for (int i = n - 1; i >= 0; --i)
            if (s[i] == '0')
                ans += (flag ? 2 : 1);
            else if (!flag)
            {
                if (i != 0)
                    ans += 2;
                flag = true;
            }
            else
                ++ans;
        return ans;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    cout << sol.numSteps("1") << '\n';
    return 0;
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260307104024252.png)


### POJ 05467

```cpp
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution
{
private:
    map<int, int, greater<int>> mp;

public:
    void init()
    {
        int x, y;
        while (cin >> x >> y)
        {
            if (y < 0)
                break;
            mp[y] += x;
        }
    }

    void output()
    {
        bool first = true;
        for (auto &m : mp)
        {
            if (m.second == 0)
                continue;
            if (!first)
                cout << " ";
            cout << "[ " << m.second << " " << m.first << " ]";
            first = false;
        }
        cout << '\n';
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--)
    {
        Solution sol;
        sol.init();
        sol.init();
        sol.output();
    }

    return 0;
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260309231109859.png)


### LC 3827

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Solution
{
public:
    int countMonobit(int n)
    {
        int monobit = 1;
        int ans = 1;
        while (monobit <= n)
        {
            ++ans;
            monobit = (monobit << 1) | 1;
        }

        return ans;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    cout << sol.countMonobit(1000);
    return 0;
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260308145518796.png)


### LC 1461

```cpp
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    bool hasAllCodes(string s, int k)
    {
        if (s.size() < (1 << k) + k - 1)
            return false;

        int num = stoi(s.substr(0, k), nullptr, 2);
        unordered_set<int> hash = {num};

        for (int i = 1; i + k <= s.size(); ++i)
        {
            num = (num - ((s[i - 1] - '0') << (k - 1))) * 2 + (s[i + k - 1] - '0');
            hash.insert(num);
        }

        return hash.size() == (1 << k);
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    string s = "0110";
    int k = 2;
    cout << sol.hasAllCodes(s, k) << '\n';
    return 0;
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260309223512178.png)


### POJ 20169

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Disjoint
{
    vector<int> pa;

public:
    Disjoint(int n) : pa(n + 1)
    {
        for (int i = 1; i <= n; ++i)
            pa[i] = i;
    }

    int find(int x)
    {
        return pa[x] == x ? x : pa[x] = find(pa[x]);
    }

    void unite(int i, int j)
    {
        int irep = find(i);
        int jrep = find(j);
        if (irep == jrep)
            return;
        pa[irep] = jrep;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        cin >> n >> m;
        Disjoint dsu(n);
        while (m--)
        {
            int i, j;
            cin >> i >> j;
            dsu.unite(i, j);
        }

        for (int i = 1; i <= n; ++i)
            cout << dsu.find(i) << ' ';
        cout << '\n';
    }

    return 0;
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260309230456741.png)


### POJ 07207

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<vector<int>> buildMagicSquare(int n)
    {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int x = 0, y = n / 2;
        for (int i = 1; i <= n * n; ++i)
        {
            matrix[x][y] = i;
            if (x == 0 && y == n - 1)
                x = (x + n + 1) % n;
            else
            {
                if (matrix[(x + n - 1) % n][(y + n + 1) % n] != 0)
                    x = (x + n + 1) % n;
                else
                    x = (x + n - 1) % n, y = (y + n + 1) % n;
            }
        }

        return matrix;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    int n;
    cin >> n;
    for (const auto &m : sol.buildMagicSquare(2 * n - 1))
    {
        for (const auto &v : m)
            cout << v << ' ';
        cout << '\n';
    }
    return 0;
}
```

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260309231227282.png)