Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

```
A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
```

begin to intersect at node c1.


##### Notes:

* If the two linked lists have no intersection at all, return null.  
* The linked lists must retain their original structure after the function returns.  
* You may assume there are no cycles anywhere in the entire linked structure.  
* Your code should preferably run in O(n) time and use only O(1) memory.  


# Solution

Let's assume that these two linkedlist have intersection. We let L1 represents the length from headA to intersection point, L2 represents the length from headB to intersction point, C represents the overlapped length. Then we know that if we make pointer p begin at headA and travel L1 + C + L2 distance, and make pointer q begin at headB and travel L2 + C + L1, then they will definitely meet at intersection point if there is one.

What if they have no intersection? The p and q will be null at the same time.
    
    
Edge cases:

1. Either linked list can be empty.
2. These two linked list may have no intersection at ll.
    
### Solution one    
    
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;
        ListNode *p(headA), *q(headB);
        bool switched_p(false), switched_q(false);
        while (p != q) {
            if (p->next) {
                p = p->next;
            } else {
                if (switched_p) return nullptr;
                p = headB;
                switched_p = true;
            }
            
            if (q->next) {
                q = q->next;
            } else {
                if (switched_q) return nullptr;
                q = headA;
                switched_q = true;
            }
            
        }      
        return p;
    }
};
```

    
    
### Solution two    

Above solution can be simplified.

If one of them reaches the end earlier then reuse it by moving it to the beginning of other list.
Once both of them go through reassigning, they will be equidistant from the collision point.
    
__If no intersection, p1 and p2 will reach NULL at the same time.__ 

```cpp
class Solution {
 public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *a(headA), *b(headB);
    while (a && b && a != b) {
      a = a->next;
      b = b->next;
      if (a == b) return a;
      if (!a) a = headB;
      if (!b) b = headA;
    }
    return a == b ? a : nullptr;
  }
};
```
