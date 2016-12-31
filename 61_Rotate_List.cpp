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
  ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next) return head;
    int count(1);
    ListNode *curr(head);
    while(curr->next) {
      ++ count;
      curr = curr->next;
    }
    // now curr is at tail node
    k = count - k % count;
    curr->next = head;
    while(k--) {
      curr = curr->next;
    }
    head = curr->next;
    curr->next = nullptr;
    return head;
  }
};
