# DSA Assignment #7: 🌲（2/3）

*Updated 2026-04-09 15:45 GMT+8*
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

### M297.二叉树的序列化与反序列化

dfs, bfs, https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/

思路：



代码：

```cpp
#include <cstddef>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left{};
  TreeNode *right{};
  TreeNode(int x) : val(x) {}
};

class Codec {
public:
  // Encodes a tree to a single string.
  auto serialize(TreeNode *root) -> std::string {
    if (!root)
      return "";

    std::string data;
    std::deque<TreeNode *> q;
    q.emplace_back(root);

    while (!q.empty()) {
      auto front = q.front();
      q.pop_front();

      if (!front) {
        data += "null,";
      } else {
        data += std::to_string(front->val) + ',';
        q.emplace_back(front->left);
        q.emplace_back(front->right);
      }
    }
    data.pop_back();
    return data;
  }

  // Decodes your encoded data to tree.
  auto deserialize(const std::string &data) -> TreeNode * {
    if (data.empty())
      return nullptr;

    std::stringstream ss(data);
    std::string str;
    getline(ss, str, ',');

    auto root = new TreeNode(std::stoi(str));
    std::deque<TreeNode *> q;
    q.emplace_back(root);

    while (!q.empty()) {
      auto front = q.front();
      q.pop_front();

      if (getline(ss, str, ',')) {
        if (str != "null") {
          front->left = new TreeNode(std::stoi(str));
          q.push_back(front->left);
        }
      }

      if (getline(ss, str, ',')) {
        if (str != "null") {
          front->right = new TreeNode(std::stoi(str));
          q.push_back(front->right);
        }
      }
    }

    return root;
  }
};

auto same_tree(TreeNode *a, TreeNode *b) -> bool {
  if (!a || !b)
    return a == b;
  return a->val == b->val && same_tree(a->left, b->left) &&
         same_tree(a->right, b->right);
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  Codec ser, deser;
  std::string data = "1,2,3,null,null,4,5";
  auto root = deser.deserialize(data);

  TreeNode *ans = deser.deserialize(ser.serialize(root));
  std::cout << same_tree(root, ans) << '\n';
}
```

> 共用时30min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260414164957988.png"/>



### M129.求根节点到叶节点数字之和

dfs, https://leetcode.cn/problems/sum-root-to-leaf-numbers/


思路：



代码：

```cpp
#include <iostream>
#include <optional>
#include <queue>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class TreeUtils {
public:
  [[nodiscard]] static auto
  buildTree(const std::vector<std::optional<int>> &node) noexcept
      -> TreeNode * {
    if (node.empty() || node.front() == std::nullopt)
      return nullptr;

    auto root = new (std::nothrow) TreeNode(node.front().value());
    if (!root)
      return nullptr;

    std::queue<TreeNode *> q;
    q.push(root);

    const auto n = node.size();
    std::size_t i = 1;
    while (!q.empty() && i < n) {
      auto front = q.front();
      q.pop();

      if (i < n && node[i] != std::nullopt) {
        front->left = new (std::nothrow) TreeNode(node[i].value());
        if (front->left)
          q.push(front->left);
      }
      ++i;

      if (i < n && node[i] != std::nullopt) {
        front->right = new (std::nothrow) TreeNode(node[i].value());
        if (front->right)
          q.push(front->right);
      }
      ++i;
    }
    return root;
  }

  static auto destroyTree(TreeNode *root) noexcept -> void {
    if (!root)
      return;

    std::queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
      auto cur = q.front();
      q.pop();
      if (cur->left)
        q.push(cur->left);
      if (cur->right)
        q.push(cur->right);
      delete cur;
    }
  }
};

class Solution {
public:
  auto sumNumbers(TreeNode *root, int res = 0) -> int {
    if (!root) {
      return 0;
    }
    res = res * 10 + root->val;
    if (!root->left && !root->right) {
      return res;
    }
    return sumNumbers(root->left, res) + sumNumbers(root->right, res);
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<std::optional<int>> data = {0, 1};
  auto root = TreeUtils::buildTree(data);
  Solution sol;
  std::cout << sol.sumNumbers(root) << '\n';
}
```

> 共用时10min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260414192000650.png"/>



### M22158:根据二叉树前中序序列建树

tree, http://cs101.openjudge.cn/practice/22158/



思路：



代码：

```cpp
#include <iostream>
#include <string>

struct TreeNode {
  char val;
  TreeNode *left{};
  TreeNode *right{};
  TreeNode(char x) : val(x) {}
};

class TreeUtils {
private:
  static inline auto dfs(TreeNode *root, std::string &res) -> void {
    if (!root)
      return;

    dfs(root->left, res);
    dfs(root->right, res);
    res += root->val;
  }

public:
  [[nodiscard]] static auto buildTree(const std::string &preorder,
                                      const std::string &inorder) noexcept
      -> TreeNode * {
    if (preorder.empty() || inorder.empty()) {
      return nullptr;
    }

    char root_val = preorder.front();
    auto root = new TreeNode(root_val);
    int index = inorder.find(root_val);
    const int n = preorder.size();

    root->left = buildTree(preorder.substr(1, index), inorder.substr(0, index));
    root->right = buildTree(preorder.substr(index + 1, n - index - 1),
                            inorder.substr(index + 1, n - index - 1));
    return root;
  }

  [[nodiscard]] static auto postorderTraversal(TreeNode *root) -> std::string {
    std::string res = "";
    dfs(root, res);
    return res;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string preorder, inorder;
  while (std::cin >> preorder >> inorder) {
    auto root = TreeUtils::buildTree(preorder, inorder);
    std::cout << TreeUtils::postorderTraversal(root) << '\n';
  }
}
```

> 共用时20min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260414195450225.png"/>



### M24729:括号嵌套树

dfs, stack, http://cs101.openjudge.cn/practice/24729/



思路：

用长子兄弟法实现了一下。

代码：

```cpp
#include <cstddef>
#include <iostream>
#include <string>

struct TreeNode {
  char val;
  TreeNode *first_child{};
  TreeNode *next_sibling{};
  TreeNode(int x) : val(x) {}
};

class TreeUtils {
private:
  static auto parseNode(const std::string &data, size_t &ptr) -> TreeNode * {
    if (ptr >= data.size())
      return nullptr;

    auto root = new TreeNode(data[ptr]);
    ++ptr;

    if (ptr < data.size() && data[ptr] == '(') {
      ++ptr;

      TreeNode *prev = nullptr;
      while (ptr < data.size() && data[ptr] != ')') {
        auto child = parseNode(data, ptr);
        if (!root->first_child)
          root->first_child = child;
        else
          prev->next_sibling = child;
        prev = child;

        if (ptr < data.size() && data[ptr] == ',')
          ++ptr;
      }

      if (ptr < data.size() && data[ptr] == ')')
        ++ptr;
    }

    return root;
  }

  static auto preorder(std::string &res, TreeNode *root) -> void {
    if (!root)
      return;

    res += root->val;
    preorder(res, root->first_child);
    preorder(res, root->next_sibling);
  }

  static auto postorder(std::string &res, TreeNode *root) -> void {
    if (!root)
      return;

    postorder(res, root->first_child);
    res += root->val;
    postorder(res, root->next_sibling);
  }

public:
  static auto buildTree(const std::string &data) -> TreeNode * {
    if (data.empty())
      return nullptr;

    size_t ptr = 0;
    return parseNode(data, ptr);
  }

  static auto preorderTraversal(TreeNode *root) -> std::string {
    std::string res = "";
    preorder(res, root);
    return res;
  }

  static auto postorderTraversal(TreeNode *root) -> std::string {
    std::string res = "";
    postorder(res, root);
    return res;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string data;
  std::cin >> data;
  auto root = TreeUtils::buildTree(data);
  std::cout << TreeUtils::preorderTraversal(root) << '\n';
  std::cout << TreeUtils::postorderTraversal(root) << '\n';
}
```

> 共用时30min

代码运行截图 <mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260414184938819.png"/>



### M01577: Falling Leaves

tree, http://cs101.openjudge.cn/practice/01577/



思路：



代码

```cpp
#include <atomic>
#include <cstddef>
#include <iostream>
#include <string>

struct TreeNode {
  char val;
  TreeNode *left{};
  TreeNode *right{};
  TreeNode(char x) : val(x) {}
};

class TreeUtils {
private:
  static inline auto insertNode(TreeNode *root, char val) -> TreeNode * {
    if (!root) {
      return new TreeNode(val);
    }

    if (val < root->val) {
      root->left = insertNode(root->left, val);
    } else {
      root->right = insertNode(root->right, val);
    }
    return root;
  }

  static inline auto dfs(TreeNode *root, std::string &res) -> void {
    if (!root)
      return;

    res += root->val;
    dfs(root->left, res);
    dfs(root->right, res);
  }

public:
  [[nodiscard]] static auto buildBST(const std::string &leaves) -> TreeNode * {
    if (leaves.empty()) {
      return nullptr;
    }

    TreeNode *root = nullptr;
    for (int i = leaves.size() - 1; i >= 0; --i) {
      root = insertNode(root, leaves[i]);
    }

    return root;
  }

  [[nodiscard]] static auto preorderTraversal(TreeNode *root) -> std::string {
    std::string res;
    dfs(root, res);
    return res;
  }
};

void delete_tree(TreeNode* root) {
    if (root == nullptr) return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::string leaves;
  while (true) {
    std::string line;
    std::cin >> line;
    
    if (line == "*") {
      auto root = TreeUtils::buildBST(leaves);
      std::cout << TreeUtils::preorderTraversal(root) << '\n';
      delete_tree(root);
      leaves.clear();
      continue;
    }
    if (line == "$") {
      auto root = TreeUtils::buildBST(leaves);
      std::cout << TreeUtils::preorderTraversal(root) << '\n';
      delete_tree(root);
      leaves.clear();
      break;
    }
    
    leaves += line;
  }
}
```

> 共用时30min

<mark>（至少包含有"Accepted"）</mark>

![image-20260414213607783](C:\Users\zho\AppData\Roaming\Typora\typora-user-images\image-20260414213607783.png)



### 1843D. Apple Tree

 Combinatorics, dfs and similar, dp, math, trees, 1200,  https://codeforces.com/problemset/problem/1843/D

思路：

可能是之前有图论基础，感觉是作业题里第二简单的，感觉最难的是括号嵌套树，可能是栈操作还不够熟练。

代码

```cpp
#include <iostream>
#include <vector>

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;

  while (t--) {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> g(n);

    for (int i = 0; i < n - 1; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;
      g[v].emplace_back(u);
      g[u].emplace_back(v);
    }

    std::vector<long long> leaves(n, 0);
    auto dfs = [&](this auto &&dfs, int root, int prev) -> void {
      if (g[root].size() == 1 && g[root][0] == prev) {
        leaves[root] = 1;
        return;
      }

      for (const auto v : g[root]) {
        if (v != prev) {
          dfs(v, root);
          leaves[root] += leaves[v];
        }
      }
    };

    dfs(0, -1);

    int q;
    std::cin >> q;
    while (q--) {
      int x, y;
      std::cin >> x >> y;
      --x, --y;
      std::cout << leaves[x] * leaves[y] << '\n';
    }
  }
}
```

> 共用时30min

<mark>（至少包含有"Accepted"）</mark>

<img src="https://raw.githubusercontent.com/bianwoyali-design/Img/main/Img/20260414223313771.png"/>



## 2. 学习总结和个人收获

<mark>如果发现作业题目相对简单，有否寻找额外的练习题目，如“数算2026spring每日选做”、LeetCode、Codeforces、洛谷等网站上的题目。</mark>





