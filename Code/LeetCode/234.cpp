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