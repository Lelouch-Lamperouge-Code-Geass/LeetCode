Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,  
Given 1->1->2, return 1->2.  
Given 1->1->2->3->3, return 1->2->3.  

# Solution

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
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode dummy(head->val - 1),*pre(&dummy),*curr(head);
        dummy.next = head;
        while(curr){
            if(curr->val == pre->val){
                pre->next = curr->next;
            } else {
                pre = curr;
            }
            curr = curr->next;
        }
        return dummy.next;
    }
};
```
