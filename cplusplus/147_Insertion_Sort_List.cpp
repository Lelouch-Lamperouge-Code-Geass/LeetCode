/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
 public:
  ListNode* insertionSortList(ListNode* head) {
    ListNode dummy(INT_MIN), *pre(&dummy), *next(nullptr);
    dummy.next = head;
    while (head) {
      if (head->next && head->val > head->next->val) {
        next = head->next->next;
        pre = &dummy;
        while (pre->next && pre->next->val < head->next->val) pre = pre->next;
        head->next->next = pre->next;
        pre->next = head->next;
        head->next = next;
      } else {
        head = head->next;
      }
    }
    return dummy.next;
  }
};
