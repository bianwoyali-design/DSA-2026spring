# Assignment #2: 位运算、前缀和、树状数组、归并排序 & 状态压缩

*Updated 2026-03-10 11:00 GMT+8*
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

### E868.二进制间距

bit manipulation, https://leetcode.cn/problems/binary-gap/

> 主要是练习面向对象编程写法，这样力扣题目，笔试都没有问题了。机考时候，不是必须OOP，能AC就可以。
>

思路：



代码：

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

>共用时5min



代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260307101552434.png)



### M304.二维区域和检索 - 矩阵不可变

prefix sum, https://leetcode.cn/problems/range-sum-query-2d-immutable/


思路：



代码：

```cpp
#include <iostream>
#include <vector>
using namespace std;

class NumMatrix
{
    vector<vector<int>> sum;

public:
    NumMatrix(vector<vector<int>> &matrix)
    {
        int n = matrix.size(), m = matrix[0].size();
        sum.resize(n + 1, vector<int>(m + 1));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + matrix[i][j];
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        return sum[row2 + 1][col2 + 1] - sum[row2 + 1][col1] - sum[row1][col2 + 1] + sum[row1][col1];
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    vector<vector<int>> matrix = {{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}};
    NumMatrix *numMatrix = new NumMatrix(matrix);
    cout << numMatrix->sumRegion(2, 1, 4, 3) << '\n'; // return 8 (红色矩形框的元素总和)
    cout << numMatrix->sumRegion(1, 1, 2, 2) << '\n'; // return 11 (绿色矩形框的元素总和)
    cout << numMatrix->sumRegion(1, 2, 2, 4) << '\n'; // return 12 (蓝色矩形框的元素总和)
    return 0;
}
```

>共用时10min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>
![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260310214738831.png)




### M1680.连接连续二进制数字

bit manipulation, https://leetcode.cn/problems/concatenation-of-consecutive-binary-numbers/



思路：



代码：

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


>共用时5min


代码运行截图 <mark>（至少包含有"Accepted"）</mark>


![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260304165509214.png)


### M1461.检查一个字符串是否包含所有长度为 K 的二进制子串

bit manipulation, https://leetcode.cn/problems/check-if-a-string-contains-all-binary-codes-of-size-k/



思路：

代码：

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
        int total_needed = 1 << k;
        if (s.size() < (size_t)total_needed + k - 1)
            return false;

        vector<bool> seen(total_needed, false);

        int x = 0;
        int cnt = 0;
        int MASK = total_needed - 1;

        for (int i = 0; i < k - 1; ++i)
        {
            x = (x << 1) | (s[i] & 1);
        }

        for (int i = k - 1; i < s.length(); ++i)
        {
            x = ((x << 1) & MASK) | (s[i] & 1);
            if (!seen[x])
            {
                seen[x] = true;
                if (++cnt == total_needed)
                    return true;
            }
        }

        return false;
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
>共用时20min


代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260310221203666.png)



### M30178:数字华容道（Easy Version）

merge sort, binary indexed tree, http://cs101.openjudge.cn/practice/30178/

思路：



代码：

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Fenwick
{
private:
    int n;
    vector<int> tree;

public:
    Fenwick(int n) : n(n), tree(n + 1, 0) {}

    void update(int i)
    {
        while (i <= n)
        {
            ++tree[i];
            i = i + (i & -i);
        }
    }

    int query(int i)
    {
        int sum = 0;
        while (i > 0)
        {
            sum += tree[i];
            i &= i - 1;
        }
        return sum;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;
    int sz = n * n;
    vector<int> matrix;
    int bottom_up;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            int x;
            cin >> x;
            if (x == 0)
                bottom_up = n - i;
            else
                matrix.push_back(x);
        }

    Fenwick bit(sz);
    long long cnt = 0;

    for (int i = matrix.size() - 1; i >= 0; --i)
    {
        cnt += bit.query(matrix[i] - 1);
        bit.update(matrix[i]);
    }

    bool flag = false;
    if (n % 2 != 0)
    {
        if (cnt % 2 == 0)
            flag = true;
    }
    else
    {
        if ((cnt + bottom_up) % 2 == 1)
            flag = true;
    }

    cout << (flag == true ? "yes\n" : "no\n");
    return 0;
}
```
>共用时1h


代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260311174013563.png)



### T30201: 旅行售货商问题

bitmask dp, http://cs101.openjudge.cn/practice/30201/

思路：



代码：

```cpp
#include <iostream>
#include <vector>
using namespace std;

constexpr static int INF = 1e9;

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;
    vector<vector<int>> G(n, vector<int>(n));
    for (auto &g : G)
        for (auto &x : g)
            cin >> x;

    int N = 1 << n;
    vector<vector<int>> dp(N, vector<int>(n + 1, INF));
    dp[1][0] = 0;

    for (int mask = 1; mask < N; ++mask)
        for (int u = 0; u < n; ++u)
        {
            if (!(mask & (1 << u)))
                continue;
            if (dp[mask][u] == INF)
                continue;
            for (int v = 0; v < n; ++v)
            {
                if ((mask & (1 << v)))
                    continue;
                dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v], dp[mask][u] + G[u][v]);
            }
        }

    int ans = INF;
    for (int i = 1; i < n; ++i)
        ans = min(ans, dp[N - 1][i] + G[i][0]);
    cout << ans << '\n';
    return 0;
}
```
>共用时1h


代码运行截图 <mark>（至少包含有"Accepted"）</mark>

![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260311183641298.png)



## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2025spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>

### POJ 20018

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Fenwick
{
private:
    int n;
    vector<int> tree;

public:
    Fenwick(int n) : n(n), tree(n + 1, 0) {}

    void update(int i)
    {
        while (i <= n)
        {
            ++tree[i];
            i += (i & -i);
        }
    }

    long long query(int i)
    {
        long long s = 0;
        while (i > 0)
        {
            s += tree[i];
            i &= i - 1;
        }
        return s;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    int N;
    cin >> N;
    vector<int> v(N), vals(N);
    for (int i = 0; i < N; ++i)
    {
        int ipt;
        cin >> ipt;
        v[i] = ipt, vals[i] = ipt;
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    Fenwick BIT(N);

    long long ans = 0;
    for (const auto &x : vals)
    {
        int r = lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
        ans += BIT.query(r - 1);
        BIT.update(r);
    }

    cout << ans << '\n';
    return 0;
}
```


![](https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/322d366a-38b7-4950-968c-303989fb912f.png)

### POJ 01019
```cpp
#include <iostream>
using namespace std;

typedef long long ll;
class Solution
{
private:
    ll get_Sk_len(ll k)
    {
        ll len = 0;
        for (ll start = 1, digits = 1; start <= k; start *= 10, digits++)
        {
            ll end = start * 10 - 1;
            if (end > k)
                end = k;
            len += (end - start + 1) * digits;
        }
        return len;
    }

    ll get_total_len(ll k)
    {
        ll total = 0;
        for (ll start = 1, digits = 1; start <= k; start *= 10, digits++)
        {
            ll end = start * 10 - 1;
            if (end > k)
                end = k;

            ll first_Sk_len = get_Sk_len(start);
            ll last_Sk_len = get_Sk_len(end);
            ll n = (end - start + 1);

            total += (first_Sk_len + last_Sk_len) * n / 2;
        }
        return total;
    }

public:
    char solve(int x)
    {
        ll l = 1, r = 31268, k = 1;
        while (l <= r)
        {
            ll mid = l + (r - l) / 2;
            if (get_total_len(mid) >= x)
            {
                k = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }

        x -= get_total_len(k - 1);

        l = 1, r = k;
        ll num = 1;
        while (l <= r)
        {
            ll mid = l + (r - l) / 2;
            if (get_Sk_len(mid) >= x)
            {
                num = mid;
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }

        x -= get_Sk_len(num - 1);
        string s = to_string(num);
        return s[x - 1];
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    Solution sol;
    while (t--)
    {
        ll x;
        cin >> x;
        cout << sol.solve(x) << '\n';
    }
    return 0;
}
```

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260316204220895.png"/>


### LC 303

```cpp
#include <iostream>
#include <ranges>
#include <vector>
using namespace std;

class NumArray
{
private:
    vector<int> prefixSum;

public:
    NumArray(vector<int> &nums) : prefixSum(nums.size() + 1)
    {
        for (auto [i, v] : nums | views::enumerate)
            prefixSum[i + 1] = prefixSum[i] + v;
    }

    int sumRange(int left, int right)
    {
        return prefixSum[right + 1] - prefixSum[left];
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    int left = 2, right = 5;
    NumArray *obj = new NumArray(nums);
    int param_1 = obj->sumRange(left, right);
    cout << param_1 << '\n';
    return 0;
}

```
<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260316204343874.png"/>



### LC 1545

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    char findKthBit(int n, int k)
    {
        if (n == 1)
            return '0';
        if (k == (1 << (n - 1)))
            return '1';
        if (k < (1 << (n - 1)))
            return findKthBit(n - 1, k);
        return findKthBit(n - 1, (1 << n) - k) ^ 1;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    int n = 4, k = 11;
    cout << sol.findKthBit(n, k) << '\n';
    return 0;
}
```

被0神的方法震撼到了。。。数学，很神奇吧
```cpp
class Solution
{
public:
    char findKthBit(int n, int k)
    {
        if (k % 2)
            return '0' + k / 2 % 2;
        k /= k & -k;
        return '1' - k / 2 % 2;
    }
};
```

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260316211833462.png"/>

### LC 647

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int countSubstrings(string s)
    {
        string t = "^#";
        for (char c : s)
        {
            t += c;
            t += "#";
        }
        t += "$";

        int n = t.size();
        int ans = 0;
        vector<int> p(n);
        int r = 0, c = 0;
        for (int i = 1; i < n - 1; ++i)
        {
            if (i < r)
                p[i] = min(p[(c << 1) - i], r - i);
            else
                p[i] = 1;
            while (t[i - p[i]] == t[i + p[i]])
                ++p[i];
            if (i + p[i] > r)
                r = i + p[i], c = i;
            ans += p[i] / 2;
        }

        return ans;
    }
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution sol;
    string s = "aaa";
    cout << sol.countSubstrings(s) << '\n';
    return 0;
}
```

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260316215410024.png"/>

### LC 131

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<vector<string>> partition(string s)
    {
        int n = s.length();
        vector<vector<string>> ans;
        vector<string> a;

        auto dfs = [&](this auto &&dfs, int i)
        {
            if (i == n)
            {
                ans.emplace_back(a);
                return;
            }

            for (int j = i; j < n; ++j)
            {
                string sub = s.substr(i, j - i + 1);
                if (isPanlindromic(sub))
                {
                    a.emplace_back(sub);
                    dfs(j + 1);
                    a.pop_back();
                }
            }
        };

        dfs(0);
        return ans;
    }

private:
    inline bool isPanlindromic(const string &s)
    {
        int l = 0, r = s.length() - 1;
        while (l < r)
            if (s[l++] != s[r--])
                return false;
        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    string s = "aab";
    for (auto i : sol.partition(s))
    {
        for (auto j : i)
            cout << j << ' ';
        cout << '\n';
    }
    return 0;
}
```

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260316230555064.png"/>