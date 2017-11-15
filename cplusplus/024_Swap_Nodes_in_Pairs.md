Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.

# Solution
  
```cpp
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
```
