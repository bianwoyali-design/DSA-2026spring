#include <cstddef>
#include <iostream>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  /* Floyd */
  auto detectCycle(ListNode *head) -> ListNode * {
    auto fast = head;
    auto slow = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) {
        while (slow != head) {
          slow = slow->next;
          head = head->next;
        }
        return slow;
      }
    }
    return nullptr;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  Solution sol;
  std::vector<int> data = {3, 2, 0, -4};
  int pos = 1;
  ListNode dummy;
  auto tail = &dummy;
  ListNode *insert = nullptr;
  for (int i = 0; i < data.size(); ++i) {
    tail->next = new ListNode(data[i]);
    tail = tail->next;
    if (i == pos) {
      insert = tail;
    }
  }
  tail->next = insert;
  auto head = dummy.next;
  std::cout << sol.detectCycle(head)->val << '\n';
}