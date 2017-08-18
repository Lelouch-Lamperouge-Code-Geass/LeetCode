Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

# Solution
  
### Solution 1 

```cpp
class Solution {
public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if(!head || k<=1) return head;
    ListNode* curr(head);
    int count(0);
    while (curr) {
      ++count;
      curr = curr->next;
    }

    ListNode dummy(0),*pre(&dummy),*next(nullptr);
    dummy.next = head;
    while (count>=k) {
      curr = pre->next;
      next = curr->next;
      // keep appending next node to pre
      for (int i=1;i<k;++i) {
        curr->next = next->next;
        next->next = pre->next;
        pre->next = next;
        next = curr->next;
      }
      pre = curr;
      count -= k;
    }
    return dummy.next;
  }
};
```
### Solution 2: 

keep stripping nodes from the list and reverse it 

```cpp
class Solution {
public:
  // strip node from list, and
  // return header of the stripped list
  ListNode* Strip(ListNode*& head, int k){
    if(!head) return head;
    ListNode dummy(0),*pre(&dummy);
    dummy.next = head;
    for (int i=1;i<k && head;++i) {
      pre = head;
      head = head->next;
    }
    if (!head) {
      head = dummy.next;
    } else {
      pre = head;
      head = head->next;
      pre->next = nullptr;
    }
    return dummy.next;
  }
  // reverse a list and return its head node
  ListNode* Reverse(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode dummy(0),*pre(&dummy),*next(nullptr);
    dummy.next = head;
    while (head) {
      next = head->next;
      head->next = pre;
      pre = head;
      head = next;
    }
    dummy.next->next = nullptr;
    return pre;
  }
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (k<=0) return head;
    ListNode dummy(0),*pre(&dummy);
    dummy.next = head;
    while(head) {
      ListNode* stripped_head = Strip(head,k);
      if(stripped_head!=head) {
        ListNode* rev_head = Reverse(stripped_head);
        pre->next = rev_head;
        // after reverse, the strippead_head become the
        // tail node of the reversed list
        stripped_head->next = head;
        pre = stripped_head;
      } else {
        // if stripped_head == head, then it means
        // no stripped happens at all!
        pre->next = head;
        break;
      }
    }
    return dummy.next;
  }
};
```

###  Solution1 3 
Please notice that since this solution uses recursion, its space complexity is not constant.
  
```cpp
class Solution {
public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if(!head || k<=0) return head;
    ListNode *curr(head);
    int count(k-1);
    while(curr && count){
      curr = curr->next;
      -- count;
    }
    if(!curr) return head;

    ListNode* right_head = reverseKGroup(curr->next,k);
    curr->next = nullptr;
    ListNode *next(nullptr);
    while(head){
      next = head->next;
      head->next = right_head;
      right_head = head;
      head = next;
    }
    return right_head;
  }
};
```
