struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  auto reverseList(ListNode *head) -> ListNode * {
    ListNode *reverse_head = nullptr;
    while (head) {
      ListNode *tmp = head->next;
      head->next = reverse_head;
      reverse_head = head;
      head = tmp;
    }
    return reverse_head;
  }
};