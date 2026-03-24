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