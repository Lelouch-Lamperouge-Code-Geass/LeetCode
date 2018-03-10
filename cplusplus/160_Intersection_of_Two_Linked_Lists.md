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
2. These two linked list may have no intersection at all.
3. The two linked list are actually the same linked list. So ```headA``` and ```headB``` at the same node from the start.


__The most hideous trap of this problem is that how to avoid infinite loop. You need to be very careful about it.__
    
### Solution one    
    
```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;
        ListNode *pa(headA), *pb(headB);
        bool switched_pa(false), switched_pb(false);
        while (pa != pb) {
            if (pa->next) {
                pa = pa->next;
            } else {
                if (switched_pa) return nullptr;
                pa = headB;
                switched_pa = true;
            }
            
            if (pb->next) {
                pb = pb->next;
            } else {
                if (switched_pb) return nullptr;
                pb = headA;
                switched_pb = true;
            }
            
        }      
        return pa;
    }
};
```

    
    
### Solution two    

Above solution can be simplified. But this solution is a little bit tricky to understand, so I would say its readability and maintainability is not as good as above code.

If one of them reaches the end earlier then reuse it by moving it to the beginning of other list. Once both of them go through reassigning, they will be equidistant from the collision point.

* If no intersection, after ```size_of_a + size_of_b``` steps, ```p1``` and ```p2``` will reach nullptr at the same time, in that case, we are still able to terminate the loop.
* If there is intersection, after travel the same distances, ```p1``` and ```p2``` will definitely meet at one node.
    
__If no intersection, p1 and p2 will reach NULL at the same time.__ 

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
        ListNode *pa(headA), *pb(headB);
        while (pa && pb && pa != pb) {
            pa = pa->next;
            pb = pb->next;
            
            if (pa == pb) return pa;
            
            if (!pa) pa = headB;
            if (!pb) pb = headA;
        }
        
        return pa == pb ? pa : nullptr;
    }
};
```

Shorter code.

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
        if (headA == headB) return headA;
        
        ListNode *pa(headA), *pb(headB);
        while (pa != pb) {
            pa = pa? pa->next : headB;
            pb = pb? pb->next : headA;
        }
        
        return pa;
    }
};
```

### Solution three

We can calculate what's the maximum steps we need to do in order to find the intersection node if it exists.

This solution is a little slower than above solutions, but in practical, its readability and maintainability is pretty good since it is very straightforward and it's quite clear that it avoid the infinite loop in a very clear way.

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
private:
    size_t getLengthOfList(ListNode *node) {
        size_t len(0);
        while (node) {
            ++ len;
            node = node->next;
        }
        return len;
    }
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;
        if (headA == headB) return headA;
        
        size_t total_steps = getLengthOfList(headA) + getLengthOfList(headB) ;
        ListNode *pa(headA), *pb(headB);
        for (size_t i = 0; i < total_steps; ++i) {
            pa = pa->next? pa->next : headB;
            pb = pb->next? pb->next : headA;
            
            if (pa == pb) return pa;
        }
        
        
        return nullptr;
    }
};
```
