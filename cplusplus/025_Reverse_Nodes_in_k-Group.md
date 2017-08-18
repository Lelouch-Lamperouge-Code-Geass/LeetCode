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
    ListNode* reverseKGroup(ListNode* head, int k) {
        std::size_t len = getListLength(head);
        ListNode  dummy(0), *pre(&dummy), *curr(head);
        dummy.next = head;
        while (len >= k) {
            ListNode* left_head = splitList(curr, k);
            ListNode* new_left_head = reverseList(left_head);
            pre->next = new_left_head;
            // now left_head is the tail node of left list
            left_head->next = curr;
            pre = left_head;
            len -= k;
        }
        
        return dummy.next;
    }
private:
    std::size_t getListLength(ListNode* head) {
        std::size_t len(0);
        while (head) {
            head = head->next;
            ++ len;
        }
        return len;
    }
    // Strip num nodes and return the head node of stripped list.
    // The input list will be splitted into two seperate lists. 
    ListNode* splitList(ListNode* &node, int num) {
        ListNode  dummy(0), *pre(&dummy);
        dummy.next = node;
        while (node && num > 1) {
            node = node->next;
            -- num;
        }
        
        ListNode *next = node->next;
        node->next = nullptr;
        node = next;
        return dummy.next;
    }
    
    // Reverse the whole list
    ListNode* reverseList(ListNode* node) {
        ListNode dummy(0), *next(nullptr);
        while (node) {
            next = node->next;
            node->next = dummy.next;
            dummy.next = node;
            node = next;
        }
        return dummy.next;
    }
};
```

###  Solution 3

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
