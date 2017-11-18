Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,

Given 1->2->3->3->4->4->5, return 1->2->5.  
Given 1->1->1->2->3, return 2->3.  


# Solution

Some corner cases:

```
1. []  
2. [1]  
3. [1,1]  
4. [1,1,2]  
```

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
        ListNode dummy(head->val-1),*pre(&dummy),*cur(head);
        dummy.next = head;
        while(cur){
            if(cur && cur->next && cur->val == cur->next->val){
                const int dup_val(cur->val);
                while(cur && cur->val == dup_val) cur = cur->next;
                
                // Note that we make pre->next point to cur even tough
                // cur right now still might be a duplicate value node.
                // We do this to take care of corner case like [1,1].
                pre->next = cur; 
            } else {
                pre = cur;
                cur = cur->next;
            }
        }
        return dummy.next;
    }
};
```
