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