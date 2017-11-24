Given a linked list, determine if it has a cycle in it.  

Follow up:  

Can you solve it without using extra space?  

# Solution
  
```cpp  
bool hasCycle(ListNode *head) {
  ListNode *slow(head),*fast(head);
  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
    if (slow == fast) return true;
  }
  return false;
}
```
