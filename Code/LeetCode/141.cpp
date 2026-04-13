#include <cstddef>
#include <iostream>
#include <vector>

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next{};
  ListNode(int x) : val(x) {}
};

class ListUtils {
public:
  [[nodiscard]] static auto buildList(const std::vector<int> &list, int pos)
      -> ListNode * {
    if (list.empty()) {
      return nullptr;
    }

    auto head = new ListNode(list[0]);
    auto tail = head;
    ListNode *entry = (pos == 0 ? head : nullptr);

    for (std::size_t i = 1; i < list.size(); ++i) {
      tail->next = new ListNode(list[i]);
      tail = tail->next;

      if (static_cast<int>(i) == pos) {
        entry = tail;
      }
    }

    if (pos >= 0 && entry) {
      tail->next = entry;
    }

    return head;
  }
};

class Solution {
public:
  auto hasCycle(ListNode *head) -> bool {
    if (!head)
      return false;

    auto slow = head;
    auto fast = head->next;
    while (fast && fast->next) {
      if (slow == fast)
        return true;
      slow = slow->next;
      fast = fast->next->next;
    }
    return false;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::vector<int> list = {3, 2, 0, -4};
  int pos = -1;

  auto head = ListUtils::buildList(list, pos);
  Solution sol;
  std::cout << sol.hasCycle(head) << '\n';
}