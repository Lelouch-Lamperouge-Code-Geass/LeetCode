Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?

# Solution  

1. We need revert the reversed list back, that's what most developers usually forget.
2. You can't use recursion, since it is not O(1) space complexity.
3. You need set the tail node of left half to have nullptr next when compare two half. Otherwise it will have a problem.
  
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
    bool isPalindrome(ListNode* head) {
        if (!head) return true;
        ListNode *slow(head), *fast(head);
        
        while (fast && fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        
        // Make fast the head of right half.
        // Note that the right half may have one less node than left half
        fast = slow->next;
        
        slow->next = nullptr; // set tail of left half to be null
        
        
        // Right now slow is the head of left half,
        // fast is the head of right half
        
        bool reval(true);
        
        ListNode *left = head, *right = reverseList(fast), *right_head(right);
        
        while (left && right) {
            if (left->val != right->val) {
                reval = false;
                break;
            }
            left = left->next; 
            right = right->next;
        }
        
        reverseList(right_head); //reverse back
        
        slow->next = fast;
        
        return reval;
    }
private:
    // Reverse the list and return the new-head node.
    ListNode* reverseList(ListNode *head) {
        ListNode dummy(0), *next(nullptr);
        
        while (head) {
            next = head->next;
            head->next = dummy.next;
            dummy.next = head;
            head = next;
        }
        
        return dummy.next;
    }
};
```
