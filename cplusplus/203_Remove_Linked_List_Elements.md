Remove all elements from a linked list of integers that have value val.

##### Example

```
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5
```

# Solution

This problem looks simple, but you need to think thoroughly about some cases.

Since we are returning a list, this in general implies that we need return a new list which has independent memory from original list.

Sure, we don't know whether the original list is a local list located on stack memory, or a dynamic allocated list located on heap memory, that is a question you can ask interviewer.

However, if it is dynamically allocated list, then it makes more sense to return a new list because it makes much easier to free memory considering we are using raw pointers here.

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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(0), *pre(&dummy);
        while (head) {
            if (head->val != val) {
                pre->next = new ListNode(head->val);
                pre = pre->next;
            }
            head = head->next;
        }
        return dummy.next;
    }
};
```
