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

### POJ 02406

```cpp
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string s;
  while (std::cin >> s) {
    if (s == ".")
      break;

    int n = static_cast<int>(s.length());
    std::vector<int> lps(n, 0);
    int length = 0;
    for (int i = 1; i < n; ++i) {
      while (length > 0 && s[i] != s[length])
        length = lps[length - 1];
      if (s[i] == s[length])
        ++length;
      lps[i] = length;
    }

    int p = n - lps.back();
    if (n % p == 0)
      std::cout << n / p << '\n';
    else
      std::cout << 1 << '\n';
  }
}
```

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260325213735028.png"/>

### POJ 03129

```cpp
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string_view>

enum class WarriorType : std::uint8_t {
  DRAGON = 0,
  NINJA,
  ICEMAN,
  LION,
  WOLF,
  COUNT
};

constexpr int WARRIOR_COUNT = static_cast<int>(WarriorType::COUNT);

constexpr std::array<std::string_view, WARRIOR_COUNT> WARRIOR_NAMES = {
    "dragon", "ninja", "iceman", "lion", "wolf"};

constexpr std::array<WarriorType, 5> RED_ORDER = {
    WarriorType::ICEMAN, WarriorType::LION, WarriorType::WOLF,
    WarriorType::NINJA, WarriorType::DRAGON};

constexpr std::array<WarriorType, 5> BLUE_ORDER = {
    WarriorType::LION, WarriorType::DRAGON, WarriorType::NINJA,
    WarriorType::ICEMAN, WarriorType::WOLF};

class Headquarter {
public:
  Headquarter(std::string_view name, int initial_m,
              const std::array<int, WARRIOR_COUNT> &hp_costs,
              const std::array<WarriorType, 5> &build_order)
      : m_name(name), m_total_m(initial_m), m_costs(hp_costs),
        m_order(build_order) {}

  void step(int time) {
    if (m_stopped)
      return;

    for (int i = 0; i < 5; ++i) {
      WarriorType type = m_order[m_iter];
      int cost = m_costs[static_cast<int>(type)];

      if (m_total_m >= cost) {
        m_total_m -= cost;
        m_counts[static_cast<int>(type)]++;
        m_total_count++;

        log_production(time, type, cost);

        m_iter = (m_iter + 1) % 5;
        return;
      }

      m_iter = (m_iter + 1) % 5;
    }

    m_stopped = true;
    log_stop(time);
  }

  [[nodiscard]] auto is_stopped() const noexcept -> bool { return m_stopped; }

private:
  std::string_view m_name;
  int m_total_m;
  const std::array<int, WARRIOR_COUNT> &m_costs;
  const std::array<WarriorType, 5> &m_order;

  std::array<int, WARRIOR_COUNT> m_counts{0};
  int m_total_count{0};
  int m_iter{0};
  bool m_stopped{false};

  void print_time(int time) const {
    std::cout << std::setfill('0') << std::setw(3) << time << ' ';
  }

  void log_production(int time, WarriorType type, int cost) const {
    print_time(time);
    auto type_idx = static_cast<int>(type);
    std::cout << m_name << ' ' << WARRIOR_NAMES[type_idx] << ' '
              << m_total_count << " born with strength " << cost << ','
              << m_counts[type_idx] << ' ' << WARRIOR_NAMES[type_idx] << " in "
              << m_name << " headquarter\n";
  }

  void log_stop(int time) const {
    print_time(time);
    std::cout << m_name << " headquarter stops making warriors\n";
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  if (!(std::cin >> t))
    return 0;

  for (int caseIdx = 1; caseIdx <= t; ++caseIdx) {
    int M;
    std::cin >> M;
    std::array<int, WARRIOR_COUNT> warrior_HP;
    for (int &hp : warrior_HP) {
      std::cin >> hp;
    }

    std::cout << "Case:" << caseIdx << '\n';

    Headquarter red("red", M, warrior_HP, RED_ORDER);
    Headquarter blue("blue", M, warrior_HP, BLUE_ORDER);

    int time = 0;
    while (!red.is_stopped() || !blue.is_stopped()) {
      red.step(time);
      blue.step(time);
      time++;
    }
  }
}
```



![image-20260325162200712](C:\Users\zho\AppData\Roaming\Typora\typora-user-images\image-20260325162200712.png)

### POJ 16926

> @🗿:当暴力成为主流，人类科研的希望将不复存在……

做了一下程设魔兽三，感觉就是暴力翻译，把人话翻译成代码（

主要就是练习oop里的继承多态，其实不太需要动脑子，还有就是这种复杂的程序对代码稳健性还是有要求的

再次吐槽cout的流输出，丑的批爆，oj快点用c++23吧，其实我早就是```std::print```和```std::ranges```的粉丝了，至于cout，我祝他好运。

码力耗尽，一段时间之内不会写代码了，歇逼。

```cpp
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <format>
#include <iostream>
#include <memory>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

enum class WarriorType : std::uint8_t {
  DRAGON = 0,
  NINJA,
  ICEMAN,
  LION,
  WOLF,
  COUNT
};

constexpr int WARRIOR_COUNT = std::to_underlying(WarriorType::COUNT);

constexpr std::array<std::string_view, WARRIOR_COUNT> WARRIOR_NAMES = {
    "dragon", "ninja", "iceman", "lion", "wolf"};

constexpr std::array<WarriorType, 5> RED_ORDER = {
    WarriorType::ICEMAN, WarriorType::LION, WarriorType::WOLF,
    WarriorType::NINJA, WarriorType::DRAGON};

constexpr std::array<WarriorType, 5> BLUE_ORDER = {
    WarriorType::LION, WarriorType::DRAGON, WarriorType::NINJA,
    WarriorType::ICEMAN, WarriorType::WOLF};

enum class WeaponType : std::uint8_t { SWORD = 0, BOMB, ARROW, COUNT };

constexpr int WEAPON_COUNT = std::to_underlying(WeaponType::COUNT);

constexpr std::array<std::string_view, WEAPON_COUNT> WEAPON_NAMES = {
    "sword", "bomb", "arrow"};

struct Config {
  int id;
  int hp;
  int atk;
  int res_m;
  WarriorType type;
  std::string_view headquarter;
};

class Warrior {
public:
  explicit Warrior(const Config &cfg)
      : m_id(cfg.id), m_hp(cfg.hp), m_atk(cfg.atk),
        m_headquarter(cfg.headquarter), m_type(cfg.type) {}

  virtual ~Warrior() = default;

  void get_damage(int damage) {
    m_hp -= damage;
    if (m_hp < 0)
      m_hp = 0;
  }

  [[nodiscard]] auto get_id() const noexcept -> int { return m_id; }
  [[nodiscard]] auto get_hp() const noexcept -> int { return m_hp; }
  [[nodiscard]] auto get_atk() const noexcept -> int { return m_atk; }
  [[nodiscard]] auto get_type() const noexcept -> WarriorType { return m_type; }
  [[nodiscard]] auto get_headquarter_name() const noexcept -> std::string_view {
    return m_headquarter;
  }

  [[nodiscard]] auto get_weapons_state() const noexcept -> int {
    int state = 0;
    for (const auto &w : m_weapons)
      state += w.usage;
    return state;
  }

  struct WeaponInfo {
    WeaponType type;
    int usage;
    WeaponInfo(WeaponType t, int c) : type(t), usage(c) {}
  };
  std::vector<WeaponInfo> m_weapons;

  void before_fight() {
    std::ranges::sort(m_weapons, [](const WeaponInfo &a, const WeaponInfo &b) {
      if (a.type == b.type)
        return a.usage < b.usage;
      return std::to_underlying(a.type) < std::to_underlying(b.type);
    });
  }

  void cleanup_weapons() {
    std::erase_if(m_weapons, [](const WeaponInfo &w) { return w.usage <= 0; });
    m_iter = 0;
  }

  void loot(Warrior *obj) {
    if (!obj)
      return;
    int size = static_cast<std::uint8_t>(obj->m_weapons.size());
    int i = 0;
    for (; i < size && m_weapons.size() < m_max_weapons &&
           obj->m_weapons[i].type != WeaponType::ARROW;
         ++i) {
      m_weapons.emplace_back(obj->m_weapons[i]);
    }
    for (int j = size - 1; j >= i && m_weapons.size() < m_max_weapons &&
                           obj->m_weapons[j].type == WeaponType::ARROW;
         --j) {
      m_weapons.emplace_back(obj->m_weapons[j]);
    }
  }

  void report_weapons(std::string_view time) const noexcept {
    std::array<int, 3> counts{0, 0, 0};
    for (const auto &w : m_weapons) {
      if (w.usage > 0)
        ++counts[std::to_underlying(w.type)];
    }
    std::println("{} {} {} {} has {} sword {} bomb {} arrow and {} elements",
                 time, get_headquarter_name(),
                 WARRIOR_NAMES[std::to_underlying(get_type())], m_id, counts[0],
                 counts[1], counts[2], m_hp);
  }

  virtual void print_extra_info() const noexcept = 0;

  virtual void attack(Warrior *obj) noexcept {
    if (!obj || m_weapons.empty() || m_hp == 0)
      return;

    int n = static_cast<std::uint8_t>(m_weapons.size());
    for (int i : std::views::iota(0, n)) {
      auto &weapon = m_weapons[m_iter];

      if (weapon.usage > 0) {
        int damage = weapon_damage(weapon.type);
        obj->get_damage(damage);

        if (weapon.type == WeaponType::BOMB) {
          if (m_type != WarriorType::NINJA) {
            m_hp -= (damage / 2);
            if (m_hp < 0)
              m_hp = 0;
          }
          weapon.usage = 0;
        } else if (weapon.type == WeaponType::ARROW) {
          --weapon.usage;
        }

        m_iter = (m_iter + 1) % n;
        return;
      }
      m_iter = (m_iter + 1) % n;
    }
  }

  void reset_iter() { m_iter = 0; }
  virtual void yell(std::string_view time, int pos) const noexcept {}

protected:
  int m_id;
  int m_hp;
  int m_atk;
  WarriorType m_type;
  const int m_max_weapons = 10;
  std::string_view m_headquarter;
  int m_iter{0};

  [[nodiscard]] auto weapon_damage(WeaponType type) const noexcept -> int {
    switch (type) {
    case WeaponType::ARROW:
      return m_atk * 3 / 10;
    case WeaponType::BOMB:
      return m_atk * 4 / 10;
    case WeaponType::SWORD:
      return m_atk * 2 / 10;
    default:
      return 0;
    }
  }
};

class Dragon : public Warrior {
public:
  explicit Dragon(const Config &cfg) : Warrior(cfg) {
    m_weapons.emplace_back(
        static_cast<WeaponType>(cfg.id % 3),
        static_cast<WeaponType>(cfg.id % 3) == WeaponType::ARROW ? 2 : 1);
  }
  void yell(std::string_view time, int pos) const noexcept override {
    std::println("{} {} dragon {} yelled in city {}", time,
                 get_headquarter_name(), get_id(), pos);
  }
  void print_extra_info() const noexcept override {}
};

class Ninja : public Warrior {
public:
  explicit Ninja(const Config &cfg) : Warrior(cfg) {
    m_weapons.emplace_back(
        static_cast<WeaponType>(cfg.id % 3),
        static_cast<WeaponType>(cfg.id % 3) == WeaponType::ARROW ? 2 : 1);
    m_weapons.emplace_back(
        static_cast<WeaponType>((cfg.id + 1) % 3),
        static_cast<WeaponType>((cfg.id + 1) % 3) == WeaponType::ARROW ? 2 : 1);
  }
  void print_extra_info() const noexcept override {}
};

class Iceman : public Warrior {
public:
  explicit Iceman(const Config &cfg) : Warrior(cfg) {
    m_weapons.emplace_back(
        static_cast<WeaponType>(cfg.id % 3),
        static_cast<WeaponType>(cfg.id % 3) == WeaponType::ARROW ? 2 : 1);
  }

  void move_take_blood() { m_hp -= m_hp / 10; }
  void print_extra_info() const noexcept override {}
};

int K;
class Lion : public Warrior {
public:
  explicit Lion(const Config &cfg) : Warrior(cfg) {
    m_loyalty = cfg.res_m;
    m_weapons.emplace_back(
        static_cast<WeaponType>(cfg.id % 3),
        static_cast<WeaponType>(cfg.id % 3) == WeaponType::ARROW ? 2 : 1);
  }
  [[nodiscard]] auto is_loyal() const noexcept -> bool { return m_loyalty > 0; }
  void down_loyalty() { m_loyalty -= m_K; }
  void print_extra_info() const noexcept override {
    std::println("Its loyalty is {}", m_loyalty);
  }

private:
  int m_loyalty;
  const int m_K = K;
};

class Wolf : public Warrior {
public:
  using Warrior::Warrior;

  void snatch(Warrior *obj, int city_pos, std::string_view time) {
    if (!obj)
      return;
    before_fight();
    obj->before_fight();

    if (!obj->m_weapons.empty() && m_weapons.size() < m_max_weapons) {
      int snatch_num = 0;
      auto obj_type = obj->m_weapons.front().type;

      if (obj_type == WeaponType::ARROW) {
        for (int i = static_cast<std::uint8_t>(obj->m_weapons.size() - 1);
             i >= 0 && m_weapons.size() < m_max_weapons; --i) {
          m_weapons.emplace_back(obj->m_weapons[i]);
          obj->m_weapons.erase(obj->m_weapons.begin() + i);
          ++snatch_num;
        }
      } else {
        while (!obj->m_weapons.empty() &&
               obj->m_weapons.front().type == obj_type &&
               m_weapons.size() < m_max_weapons) {
          m_weapons.emplace_back(obj->m_weapons.front());
          obj->m_weapons.erase(obj->m_weapons.begin());
          ++snatch_num;
        }
      }

      if (snatch_num > 0) {
        std::println("{} {} wolf {} took {} {} from {} {} {} in city {}", time,
                     m_headquarter, m_id, snatch_num,
                     WEAPON_NAMES[std::to_underlying(obj_type)],
                     obj->get_headquarter_name(),
                     WARRIOR_NAMES[std::to_underlying(obj->get_type())],
                     obj->get_id(), city_pos);
      }
    }
  }
  void print_extra_info() const noexcept override {}
};

class Headquarter {
public:
  explicit Headquarter(const std::array<int, WARRIOR_COUNT> &atk, int initial_m,
                       const std::array<int, WARRIOR_COUNT> &hp_costs, int N)
      : m_atk(atk), m_total_m(initial_m), m_costs(hp_costs), m_N(N) {}

  virtual ~Headquarter() = default;

  [[nodiscard]] virtual auto get_name() const noexcept -> std::string_view = 0;
  [[nodiscard]] virtual auto get_order() const noexcept
      -> const std::array<WarriorType, 5> & = 0;

  void report_elements(std::string_view time) const {
    std::println("{} {} elements in {} headquarter", time, m_total_m,
                 get_name());
  }

  [[nodiscard]] auto step(std::string_view time) noexcept
      -> std::unique_ptr<Warrior> {
    if (m_stopped)
      return nullptr;

    const auto &order = get_order();
    WarriorType type = order[m_iter];
    int cost = m_costs[std::to_underlying(type)];

    if (m_total_m >= cost) {
      m_total_m -= cost;
      ++m_counts[std::to_underlying(type)];
      int id = ++m_total_count;
      int atk = m_atk[std::to_underlying(type)];

      auto warrior = create_warrior(id, type, cost, atk);
      log_production(time, type);
      warrior->print_extra_info();

      m_iter = (m_iter + 1) % 5;
      return warrior;
    }

    m_stopped = true;
    return nullptr;
  }

  [[nodiscard]] auto is_stopped() const noexcept -> bool { return m_stopped; }

protected:
  int m_total_m;
  int m_N;
  const std::array<int, WARRIOR_COUNT> &m_costs;
  const std::array<int, WARRIOR_COUNT> &m_atk;
  std::array<int, WARRIOR_COUNT> m_counts{0};
  int m_total_count{0};
  int m_iter{0};
  bool m_stopped{false};

private:
  void log_production(std::string_view time, WarriorType type) const {
    std::println("{} {} {} {} born", time, get_name(),
                 WARRIOR_NAMES[std::to_underlying(type)], m_total_count);
  }

  [[nodiscard]] auto create_warrior(int id, WarriorType type, int cost,
                                    const int atk) const noexcept
      -> std::unique_ptr<Warrior> {
    Config cfg = {.id = id,
                  .hp = cost,
                  .atk = atk,
                  .res_m = m_total_m,
                  .type = type,
                  .headquarter = get_name()};
    switch (type) {
    case WarriorType::DRAGON:
      return std::make_unique<Dragon>(cfg);
    case WarriorType::NINJA:
      return std::make_unique<Ninja>(cfg);
    case WarriorType::ICEMAN:
      return std::make_unique<Iceman>(cfg);
    case WarriorType::LION:
      return std::make_unique<Lion>(cfg);
    case WarriorType::WOLF:
      return std::make_unique<Wolf>(cfg);
    default:
      return nullptr;
    }
  }
};

class RedHeadquarter : public Headquarter {
public:
  using Headquarter::Headquarter;
  [[nodiscard]] auto get_name() const noexcept -> std::string_view override {
    return "red";
  }
  [[nodiscard]] auto get_order() const noexcept
      -> const std::array<WarriorType, 5> & override {
    return RED_ORDER;
  }
};

class BlueHeadquarter : public Headquarter {
public:
  using Headquarter::Headquarter;
  [[nodiscard]] auto get_name() const noexcept -> std::string_view override {
    return "blue";
  }
  [[nodiscard]] auto get_order() const noexcept
      -> const std::array<WarriorType, 5> & override {
    return BLUE_ORDER;
  }
};

class City {
public:
  explicit City(int i) : m_pos(i) {}

  [[nodiscard]] auto get_red() const noexcept -> Warrior * {
    return m_red_warrior.get();
  }
  [[nodiscard]] auto get_blue() const noexcept -> Warrior * {
    return m_blue_warrior.get();
  }
  [[nodiscard]] auto red_leaves() -> std::unique_ptr<Warrior> {
    return std::move(m_red_warrior);
  }
  [[nodiscard]] auto blue_leaves() -> std::unique_ptr<Warrior> {
    return std::move(m_blue_warrior);
  }

  void produce_red(std::unique_ptr<Warrior> w) { m_red_warrior = std::move(w); }
  void produce_blue(std::unique_ptr<Warrior> w) {
    m_blue_warrior = std::move(w);
  }
  void accept_incoming_red(std::unique_ptr<Warrior> w) {
    m_incoming_red = std::move(w);
  }
  void accept_incoming_blue(std::unique_ptr<Warrior> w) {
    m_incoming_blue = std::move(w);
  }

  [[nodiscard]] auto is_taken() const noexcept -> bool {
    return m_enemy_count >= 1;
  }

  void check_lion(std::string_view time, int N) {
    if (m_red_warrior && m_red_warrior->get_type() == WarriorType::LION &&
        m_pos < N + 1) {
      auto *lion = static_cast<Lion *>(m_red_warrior.get());
      if (!lion->is_loyal()) {
        std::println("{} red lion {} ran away", time, lion->get_id());
        m_red_warrior = nullptr;
      }
    }
    if (m_blue_warrior && m_blue_warrior->get_type() == WarriorType::LION &&
        m_pos > 0) {
      auto *lion = static_cast<Lion *>(m_blue_warrior.get());
      if (!lion->is_loyal()) {
        std::println("{} blue lion {} ran away", time, lion->get_id());
        m_blue_warrior = nullptr;
      }
    }
  }

  void commit_arrivals(std::string_view time, int N) {
    if (m_incoming_red) {
      m_red_warrior = std::move(m_incoming_red);
      if (m_red_warrior->get_type() == WarriorType::ICEMAN)
        static_cast<Iceman *>(m_red_warrior.get())->move_take_blood();
      else if (m_red_warrior->get_type() == WarriorType::LION)
        static_cast<Lion *>(m_red_warrior.get())->down_loyalty();

      std::print("{} red {} {} ", time,
                 WARRIOR_NAMES[std::to_underlying(m_red_warrior->get_type())],
                 m_red_warrior->get_id());

      if (m_pos == N + 1) {
        std::println("reached blue headquarter with {} elements and force {}",
                     m_red_warrior->get_hp(), m_red_warrior->get_atk());
        ++m_enemy_count;
        if (is_taken())
          std::println("{} blue headquarter was taken", time);
      } else {
        std::println("marched to city {} with {} elements and force {}", m_pos,
                     m_red_warrior->get_hp(), m_red_warrior->get_atk());
      }
    }

    if (m_incoming_blue) {
      m_blue_warrior = std::move(m_incoming_blue);
      if (m_blue_warrior->get_type() == WarriorType::ICEMAN)
        static_cast<Iceman *>(m_blue_warrior.get())->move_take_blood();
      else if (m_blue_warrior->get_type() == WarriorType::LION)
        static_cast<Lion *>(m_blue_warrior.get())->down_loyalty();

      std::print("{} blue {} {} ", time,
                 WARRIOR_NAMES[std::to_underlying(m_blue_warrior->get_type())],
                 m_blue_warrior->get_id());

      if (m_pos == 0) {
        std::println("reached red headquarter with {} elements and force {}",
                     m_blue_warrior->get_hp(), m_blue_warrior->get_atk());
        ++m_enemy_count;
        if (is_taken())
          std::println("{} red headquarter was taken", time);
      } else {
        std::println("marched to city {} with {} elements and force {}", m_pos,
                     m_blue_warrior->get_hp(), m_blue_warrior->get_atk());
      }
    }
  }

  void wolf_snatch(std::string_view time) {
    if (!m_red_warrior || !m_blue_warrior)
      return;
    bool red_is_wolf = (m_red_warrior->get_type() == WarriorType::WOLF);
    bool blue_is_wolf = (m_blue_warrior->get_type() == WarriorType::WOLF);

    if (red_is_wolf && !blue_is_wolf)
      static_cast<Wolf *>(m_red_warrior.get())
          ->snatch(m_blue_warrior.get(), m_pos, time);
    else if (!red_is_wolf && blue_is_wolf)
      static_cast<Wolf *>(m_blue_warrior.get())
          ->snatch(m_red_warrior.get(), m_pos, time);
  }

  void fight(std::string_view time) {
    if (!m_red_warrior || !m_blue_warrior)
      return;
    bool both_no_weapons =
        m_red_warrior->m_weapons.empty() && m_blue_warrior->m_weapons.empty();

    if (!both_no_weapons) {
      m_red_warrior->before_fight();
      m_blue_warrior->before_fight();
      m_red_warrior->reset_iter();
      m_blue_warrior->reset_iter();

      Warrior *first =
          (m_pos % 2 == 1) ? m_red_warrior.get() : m_blue_warrior.get();
      Warrior *second =
          (m_pos % 2 == 1) ? m_blue_warrior.get() : m_red_warrior.get();

      int unchanged_rounds = 0;

      while (true) {
        int r_hp = m_red_warrior->get_hp(),
            r_ws = m_red_warrior->get_weapons_state();
        int b_hp = m_blue_warrior->get_hp(),
            b_ws = m_blue_warrior->get_weapons_state();

        first->attack(second);
        if (first->get_hp() <= 0 || second->get_hp() <= 0)
          break;

        second->attack(first);
        if (first->get_hp() <= 0 || second->get_hp() <= 0)
          break;

        if (r_hp == m_red_warrior->get_hp() &&
            r_ws == m_red_warrior->get_weapons_state() &&
            b_hp == m_blue_warrior->get_hp() &&
            b_ws == m_blue_warrior->get_weapons_state()) {
          unchanged_rounds++;
        } else {
          unchanged_rounds = 0;
        }

        if (unchanged_rounds >= 20)
          break;
      }
    }

    handle_result_and_logs(time);
  }

  void report_warrior_status(std::string_view time) const {
    if (m_red_warrior)
      m_red_warrior->report_weapons(time);
    if (m_blue_warrior)
      m_blue_warrior->report_weapons(time);
  }

private:
  int m_pos;
  int m_enemy_count{0};
  std::unique_ptr<Warrior> m_red_warrior;
  std::unique_ptr<Warrior> m_blue_warrior;
  std::unique_ptr<Warrior> m_incoming_red;
  std::unique_ptr<Warrior> m_incoming_blue;

  void print_both_died_log(std::string_view time) const noexcept {
    std::println("{} both red {} {} and blue {} {} died in city {}", time,
                 WARRIOR_NAMES[std::to_underlying(m_red_warrior->get_type())],
                 m_red_warrior->get_id(),
                 WARRIOR_NAMES[std::to_underlying(m_blue_warrior->get_type())],
                 m_blue_warrior->get_id(), m_pos);
  }

  void print_alive_log(std::string_view time) const noexcept {
    std::println("{} both red {} {} and blue {} {} were alive in city {}", time,
                 WARRIOR_NAMES[std::to_underlying(m_red_warrior->get_type())],
                 m_red_warrior->get_id(),
                 WARRIOR_NAMES[std::to_underlying(m_blue_warrior->get_type())],
                 m_blue_warrior->get_id(), m_pos);
  }

  void handle_result_and_logs(std::string_view time) noexcept {
    bool red_dead = (m_red_warrior->get_hp() <= 0);
    bool blue_dead = (m_blue_warrior->get_hp() <= 0);

    if (red_dead && blue_dead) {
      print_both_died_log(time);
      m_red_warrior = nullptr;
      m_blue_warrior = nullptr;
    } else if (red_dead) {
      m_red_warrior->cleanup_weapons();
      m_blue_warrior->cleanup_weapons();
      m_blue_warrior->loot(m_red_warrior.get());
      std::println(
          "{} blue {} {} killed red {} {} in city {} remaining {} elements",
          time, WARRIOR_NAMES[std::to_underlying(m_blue_warrior->get_type())],
          m_blue_warrior->get_id(),
          WARRIOR_NAMES[std::to_underlying(m_red_warrior->get_type())],
          m_red_warrior->get_id(), m_pos, m_blue_warrior->get_hp());
      m_red_warrior = nullptr;
      if (m_blue_warrior->get_type() == WarriorType::DRAGON)
        m_blue_warrior->yell(time, m_pos);
    } else if (blue_dead) {
      m_blue_warrior->cleanup_weapons();
      m_red_warrior->cleanup_weapons();
      m_red_warrior->loot(m_blue_warrior.get());
      std::println(
          "{} red {} {} killed blue {} {} in city {} remaining {} elements",
          time, WARRIOR_NAMES[std::to_underlying(m_red_warrior->get_type())],
          m_red_warrior->get_id(),
          WARRIOR_NAMES[std::to_underlying(m_blue_warrior->get_type())],
          m_blue_warrior->get_id(), m_pos, m_red_warrior->get_hp());
      m_blue_warrior = nullptr;
      if (m_red_warrior->get_type() == WarriorType::DRAGON)
        m_red_warrior->yell(time, m_pos);
    } else {
      m_red_warrior->cleanup_weapons();
      m_blue_warrior->cleanup_weapons();
      print_alive_log(time);
      if (m_red_warrior->get_type() == WarriorType::DRAGON)
        m_red_warrior->yell(time, m_pos);
      if (m_blue_warrior->get_type() == WarriorType::DRAGON)
        m_blue_warrior->yell(time, m_pos);
    }
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  if (!(std::cin >> t))
    return 0;

  for (int caseIdx : std::views::iota(1, t + 1)) {
    int M, N, T;
    std::cin >> M >> N >> K >> T;
    std::array<int, WARRIOR_COUNT> warrior_HP;
    for (int &hp : warrior_HP)
      std::cin >> hp;
    std::array<int, WARRIOR_COUNT> warrior_ATK;
    for (int &atk : warrior_ATK)
      std::cin >> atk;

    std::println("Case {}:", caseIdx);

    std::array<std::unique_ptr<Headquarter>, 2> bases = {
        std::make_unique<RedHeadquarter>(warrior_ATK, M, warrior_HP, N),
        std::make_unique<BlueHeadquarter>(warrior_ATK, M, warrior_HP, N)};

    std::vector<City> cities;
    cities.reserve(N + 2);
    for (int i : std::views::iota(0, N + 2))
      cities.emplace_back(i);

    int hour = 0;
    bool game_over = false;

    while (true) {
      if (hour * 60 > T || game_over)
        break;

      std::string time_00 = std::format("{:03}:00", hour);
      cities[0].produce_red(bases[0]->step(time_00));
      cities[N + 1].produce_blue(bases[1]->step(time_00));

      if (hour * 60 + 5 > T)
        break;
      std::string time_05 = std::format("{:03}:05", hour);
      for (int i : std::views::iota(0, N + 2))
        cities[i].check_lion(time_05, N);

      if (hour * 60 + 10 > T)
        break;
      std::string time_10 = std::format("{:03}:10", hour);

      for (int i : std::views::iota(0, N + 2)) {
        if (cities[i].get_red() && i < N + 1)
          cities[i + 1].accept_incoming_red(cities[i].red_leaves());
        if (cities[i].get_blue() && i > 0)
          cities[i - 1].accept_incoming_blue(cities[i].blue_leaves());
      }

      for (int i : std::views::iota(0, N + 2)) {
        cities[i].commit_arrivals(time_10, N);
        if (cities[i].is_taken())
          game_over = true;
      }
      if (game_over)
        break;

      if (hour * 60 + 35 > T)
        break;
      std::string time_35 = std::format("{:03}:35", hour);
      for (int i : std::views::iota(1, N + 1))
        cities[i].wolf_snatch(time_35);

      if (hour * 60 + 40 > T)
        break;
      std::string time_40 = std::format("{:03}:40", hour);
      for (int i : std::views::iota(1, N + 1))
        cities[i].fight(time_40);

      if (hour * 60 + 50 > T)
        break;
      std::string time_50 = std::format("{:03}:50", hour);
      bases[0]->report_elements(time_50);
      bases[1]->report_elements(time_50);

      if (hour * 60 + 55 > T)
        break;
      std::string time_55 = std::format("{:03}:55", hour);
      for (int i : std::views::iota(0, N + 2))
        cities[i].report_warrior_status(time_55);

      ++hour;
    }
  }
  return 0;
}
```

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/b7bbb1661a5052fec366524fd35dfff7.png"/>
