/*
Solution 1
*/
class Solution {
public:
  ListNode* swapPairs(ListNode* head) {
    if(!head || !head->next) return head;
    ListNode* next = head->next;
    head->next = swapPairs(head->next->next);
    next->next = head;
    return next;
  }
};

/*
Solution 2
*/
class Solution {
public:
  ListNode* swapPairs(ListNode* head) {
    ListNode dummy(0),*pre(&dummy),*left(nullptr),*right(nullptr);
    dummy.next = head;
    while(pre && pre->next && pre->next->next){
      left = pre->next;
      right = left->next;

      pre->next = right;
      left->next = right->next;
      right->next = left;
      pre = left;
    }
    return dummy.next;
  }
};
