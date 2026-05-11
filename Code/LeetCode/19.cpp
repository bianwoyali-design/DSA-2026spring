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
  auto removeNthFromEnd(ListNode *head, int n) -> ListNode * {
    ListNode dummy(0, head);
    auto left = &dummy;
    auto right = &dummy;
    while (n--) {
      right = right->next;
    }
    while (right->next) {
      left = left->next;
      right = right->next;
    }
    auto next = left->next;
    left->next = left->next->next;
    delete next;
    return dummy.next;
  }
};

auto main() -> int {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  Solution sol;
  std::vector<int> data = {1, 2, 3, 4, 5};
  ListNode dummy;
  auto tail = &dummy;
  for (int d : data) {
    tail->next = new ListNode(d);
    tail = tail->next;
  }

  auto head = dummy.next;
  int n = 2;
  auto out = sol.removeNthFromEnd(head, n);
  while (out != nullptr) {
    std::cout << out->val << ' ';
    out = out->next;
  }
  std::cout << '\n';
}
