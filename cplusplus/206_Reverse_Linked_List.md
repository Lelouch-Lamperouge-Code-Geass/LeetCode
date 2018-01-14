Reverse a singly linked list.

Hint:  
A linked list can be reversed either iteratively or recursively. Could you implement both?  

# Solution

### Solution 1 

Iterative solution.

Note here we did not make dummy.next = head at first. In this way, we can easily make sure that the next pointer of the final node will be nullptr.

And this code can handle empty list pretty good too.

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
    ListNode* reverseList(ListNode* head) {
        ListNode dummy(0), *pre(&dummy), *curr(head), *next(nullptr);
        while (curr) {
            next = curr->next;
            curr->next = pre->next;
            pre->next = curr;
            curr = next;
        }
        
        return dummy.next;
    }
};
```

### Solution 2

Recursive solution

```cpp
class Solution {
public:
    // return tail of the list
    ListNode* reverseList(ListNode* head) {
        if(!head||!head->next) return head;
        ListNode* node(reverseList(head->next));
        head->next->next = head;
        head->next = nullptr;
        return node;
    }
};
```
