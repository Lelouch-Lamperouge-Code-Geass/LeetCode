Given a list, rotate the list to the right by k places, where k is non-negative.


Example:

```
Given 1->2->3->4->5->NULL and k = 2,

return 4->5->1->2->3->NULL.
```  

# Solution

__Note that k could be larger than the length of the whole list!__

Therefore, we need to get the length of the whole list first, and make ``` k %= len```.

And what we need to do is to make the list as a circle and also find the tail node of final result.
  
Since the list is a circle, right now the node after the tail node is our new head of the list.

We need return that head node and don't forget to set tail.next to be null.  
  

Some edge cases:

1. head is null
2. k <= 0
3. k is larger than length of the whole list  
  
```cpp
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
```
