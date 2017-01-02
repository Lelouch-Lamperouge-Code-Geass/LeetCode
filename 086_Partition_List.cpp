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
  ListNode* partition(ListNode* head, int x) {
    if(!head ||!head->next) return head;
    ListNode left(0),right(0),*lp(&left),*rp(&right);
    while(head){
      if(head->val < x){
        lp->next = head;
        lp = lp->next;
      } else {
        rp->next = head;
        rp = rp->next;
      }
      head = head ->next;
    }
    rp->next = nullptr;
    lp->next = right.next;
    return left.next;
  }
};
