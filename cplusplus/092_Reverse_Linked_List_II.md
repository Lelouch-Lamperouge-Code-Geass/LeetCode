Reverse a linked list from position m to n. Do it in-place and in one-pass.  

For example:

```
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.
```

__Note:__  
Given m, n satisfy the following condition:  
1 ≤ m ≤ n ≤ length of list.  

# Solution

Note that since it is guranteed that ```1 ≤ m ≤ n ≤ length of list```, we don't need to check those related corner cases. However, int real interview you need to check that with interviewer.

The solution works like this:  

```
pre  p    q
1 -> 2 -> 3 -> 4 -> 5


pre       p    q
1 -> 3 -> 2 -> 4 -> 5


pre            p    q
1 -> 4 -> 3 -> 2 -> 5

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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode dummy(0),*pre(&dummy);
        dummy.next = head;
        for(int i=1;i<m && pre;++i){
            pre = pre -> next;
        }
        if(!pre) return head;
       
        ListNode *cur(pre->next),*next(nullptr);
        for(int i=m;cur && i<n; ++i){
            next = cur->next;
            cur->next = next->next;
            next->next = pre->next;
            pre->next = next;
        }

        return dummy.next;
    }
};
```
