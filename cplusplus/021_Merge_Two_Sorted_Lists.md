Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

# Solution

Note that you need to talk to interviewer about how should we form the new list.

Should we create a new list and keet previous two lists intact? Or should we merge those two lists together?

And you also need to check whether the list are allocated on stack memory or heap memory. A raw pointer won't give you any information about the allocated memory, it could possibly point to local variable. Even smatr pointer like shared pointer can be point to stack memory too.

__About this problem, you need to check with interviewer about memory allocation.__

In below solution, we keep original lists intact and return a new list. 

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(INT_MIN), *pre(&dummy);
        while(l1 || l2){
            if (l1 && l2) {
                if(l1->val < l2->val){
                    pre->next = new ListNode(l1->val);
                    l1 = l1->next;
                } else {
                    pre->next = new ListNode(l2->val);
                    l2 = l2->next;
                }
            } else {
                if (l1) {
                   pre->next = new ListNode(l1->val);
                   l1 = l1->next; 
                } else {
                    pre->next = new ListNode(l2->val);
                    l2 = l2->next;
                }
            }
            pre = pre->next;
        }

        return dummy.next;
    }
};
```
