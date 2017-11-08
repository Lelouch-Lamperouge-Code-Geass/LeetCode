Given a non-negative integer represented as non-empty a singly linked list of digits, plus one to the integer.

You may assume the integer do not contain any leading zero, except the number 0 itself.

The digits are stored such that the most significant digit is at the head of the list.

##### Example:

```
Input:
1->2->3

Output:
1->2->4
```

# Solution

For C++ code, you must avoid return reference/pointer to a local dummy node.

Another solution can be : reverse list first, add one, and reverse back.

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
    ListNode* plusOne(ListNode* head) {
        ListNode *dummy = new ListNode(0), *last_not_nine_node(dummy);
        dummy->next = head;
        
        ListNode *node(head);
        while (node) {
            if (node->val != 9) {
                last_not_nine_node = node;
            }
            node = node->next;
        }
        
        ++ last_not_nine_node->val;
        
        node = last_not_nine_node->next;
        
        // convert tailing 9 to 0
        while (node) {
            node->val = 0;
            node = node->next;
        }
        
        if (dummy->val == 0) {
            node = dummy->next;
            delete dummy;
        } else {
            node = dummy;
        }
        
        return node;
    }
};
```
