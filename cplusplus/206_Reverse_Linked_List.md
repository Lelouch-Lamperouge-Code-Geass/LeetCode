Reverse a singly linked list.

Hint:  
A linked list can be reversed either iteratively or recursively. Could you implement both?  

# Solution

### Solution 1 

Iterative solution.

```
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
        if(!head || !head->next) return head;
        ListNode dummy(0), *pre(&dummy), *next(nullptr);
        dummy.next = head;
        while(head){
            next = head->next;
            head->next = pre;
            pre = head;
            head = next;
        }
        dummy.next->next = nullptr; // set tail->next to be nullptr
        return pre;
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
