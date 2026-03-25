# DSA Assignment #4: 线性结构

*Updated 2026-03-23 22:22 GMT+8*
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

### E160.相交链表

hash table, linked list, two pinters, https://leetcode.cn/problems/intersection-of-two-linked-lists/

思路：



代码：

```cpp
struct ListNode {
  int val;
  ListNode *next{};
  ListNode(int x) : val(x) {}
};

class Solution {
public:
  auto getIntersectionNode(ListNode *headA, ListNode *headB) -> ListNode * {
    ListNode *a = headA;
    ListNode *b = headB;
    while (a != b) {
      a = a ? a->next : headB;
      b = b ? b->next : headA;
    }
    return a;
  }
};
```

> 共用时10min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260324160059281.png"/>



### E206.反转链表

recursion, linked list, https://leetcode.cn/problems/reverse-linked-list/


思路：



代码：

```cpp
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution1 {
public:
  auto reverseList(ListNode *head) -> ListNode * {
    if (head == nullptr || head->next == nullptr)
      return head;
    auto reversed_head = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return reversed_head;
  }
};

class Solution2 {
public:
  auto reverseList(ListNode *head) -> ListNode * {
    ListNode *reversed_head = nullptr;
    while (head) {
      ListNode *temp = head->next;
      head->next = reversed_head;
      reversed_head = head;
      head = temp;
    }
    return reversed_head;
  }
};
```

> 共用时30min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>



<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260324164756495.png"/>

### M234.回文链表

linked list, two pointers, https://leetcode.cn/problems/palindrome-linked-list/

<mark>请用快慢指针实现</mark> `O(1)` 空间复杂度。

思路：



代码：

```cpp
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  auto isPalindrome(ListNode *head) -> bool {
    if (!head || !head->next)
      return true;

    auto slow = head;
    auto fast = head->next;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    slow = slow->next;

    ListNode *reversed_half = nullptr;
    while (slow) {
      ListNode *temp = slow->next;
      slow->next = reversed_half;
      reversed_half = slow;
      slow = temp;
    }

    while (reversed_half) {
      if (reversed_half->val != head->val)
        return false;
      reversed_half = reversed_half->next;
      head = head->next;
    }

    return true;
  }
};
```

> 共用时20min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>



<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260324172515056.png"/>

### M24591:中序表达式转后序表达式

stack, http://cs101.openjudge.cn/practice/24591/

思路：



代码：

```cpp
#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

constexpr auto precedence(char op) -> int {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/')
    return 2;
  return 0;
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  while (n--) {
    std::string s;
    std::cin >> s;

    int l = static_cast<int>(s.length());

    std::stack<char> ops;
    std::vector<std::string> RPN;

    std::string num = "";
    for (int i = 0; i < l; ++i) {
      char c = s[i];

      if (std::isdigit(c) || c == '.')
        num += c;
      else {
        if (!num.empty()) {
          RPN.push_back(std::move(num));
          num = "";
        }

        if (c == '(')
          ops.push(c);
        else if (c == ')') {
          while (!ops.empty()) {
            if (ops.top() == '(') {
              ops.pop();
              break;
            }
            RPN.emplace_back(1, ops.top());
            ops.pop();
          }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
          while (!ops.empty() && precedence(c) <= precedence(ops.top())) {
            RPN.emplace_back(1, ops.top());
            ops.pop();
          }
          ops.push(c);
        }
      }
    }

    if (!num.empty())
      RPN.push_back(num);

    while (!ops.empty()) {
      RPN.emplace_back(1, ops.top());
      ops.pop();
    }

    for (const auto &s : RPN)
      std::cout << s << ' ';
    std::cout << '\n';
  }
}
```

> 共用时30min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260324194416604.png"/>



### M146.LRU缓存

hash table, doubly-linked list, https://leetcode.cn/problems/lru-cache/

思路：



代码

```cpp
#include <iterator>
#include <list>
#include <print>
#include <unordered_map>
#include <utility>

class LRUCache {
public:
  explicit LRUCache(int capacity) : capacity(capacity) {}

  auto get(int key) -> int {
    auto it = hash.find(key);
    if (it == hash.end())
      return -1;
    cache.splice(cache.begin(), cache, it->second);
    return it->second->second;
  }

  void put(int key, int value) {
    auto it = hash.find(key);
    if (it != hash.end()) {
      it->second->second = value;
      cache.splice(cache.begin(), cache, it->second);
    } else {
      if (cache.size() == capacity) {
        auto del = std::prev(cache.end());
        hash.erase(del->first);
        cache.pop_back();
      }
      hash[key] = cache.emplace(cache.begin(), key, value);
    }
  }

private:
  int capacity;
  std::list<std::pair<int, int>> cache;
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> hash;
};

auto main() -> int {
  auto *lRUCache = new LRUCache(2);
  lRUCache->put(1, 1);                  // 缓存是 {1=1}
  lRUCache->put(2, 2);                  // 缓存是 {1=1, 2=2}
  std::println("{}", lRUCache->get(1)); // 返回 1
  lRUCache->put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
  std::println("{}", lRUCache->get(2)); // 返回 -1 (未找到)
  lRUCache->put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
  std::println("{}", lRUCache->get(1)); // 返回 -1 (未找到)
  std::println("{}", lRUCache->get(3)); // 返回 3
  std::println("{}", lRUCache->get(4)); // 返回 4
}

```

> 共用时20min

<mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260324203945715.png"/>



### P2698 [USACO12MAR] Flowerpot S

monotonic queue, https://www.luogu.com.cn/problem/P2698

思路：

用单调队列维护最大值和最小值，其余实现即为滑动窗口，右端点不断右移，当满足D的条件时左端点逼近求最小值。注意到二分不一定能优化结果，因为查询区间最大最小值时会额外耗时（线段树/RMQ）。另外试了一下c++23新增的格式化输出方式print，和python用法几乎没什么区别了。

代码

```cpp
#include <algorithm>
#include <limits>
#include <print>
#include <iostream>
#include <deque>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int N, D;
  std::cin >> N >> D;

  std::vector<std::pair<int, int>> coordinates(N);
  for (auto &c : coordinates)
    std::cin >> c.first >> c.second;
  std::ranges::sort(coordinates);

  std::deque<int> maxq, minq;

  int l = 0, r = 0;
  int res = std::numeric_limits<int>::max();
  while (r < N) {
    while (!maxq.empty() &&
           coordinates[maxq.back()].second <= coordinates[r].second)
      maxq.pop_back();
    maxq.push_back(r);

    while (!minq.empty() &&
           coordinates[minq.back()].second >= coordinates[r].second)
      minq.pop_back();
    minq.push_back(r);

    while (l <= r && coordinates[maxq.front()].second - coordinates[minq.front()].second >= D) {
      res = std::min(res, coordinates[r].first - coordinates[l].first);
      ++l;
      if (!maxq.empty() && maxq.front() < l)
        maxq.pop_front();
      if (!minq.empty() && minq.front() < l)
        minq.pop_front();
    }
    ++r;
  }

  if (res == std::numeric_limits<int>::max())
    std::println("-1");
  else
    std::println("{}", res);
}
```

> 共用时1h

<mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260324233308352.png"/>



## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2026spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>





