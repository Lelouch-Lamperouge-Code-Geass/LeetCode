Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

__Follow up:__

Can you solve it without using extra space?

# Solution
  
##### Step 1: Determine whether there is a cycle

1.1) Using a slow pointer that move forward 1 step each time

1.2) Using a fast pointer that move forward 2 steps each time

1.3) If the slow pointer and fast pointer both point to the same location after several moving steps, there is a cycle;

1.4) Otherwise, if (fast->next == NULL || fast->next->next == NULL), there has no cycle.
  
##### Step 2: If there is a cycle, return the entry location of the cycle

2.1) L1 is defined as the distance between the head point and entry point

2.2) L2 is defined as the distance between the entry point and the meeting point

2.3) C is defined as the length of the cycle

2.4) n is defined as the travel times of the fast pointer around the cycle When the first encounter of the slow pointer and the fast pointer  

According to the definition of L1, L2 and C, we can obtain:

* the total distance of the slow pointer traveled when encounter is L1 + L2

* the total distance of the fast pointer traveled when encounter is L1 + L2 + n * C

Because the total distance the fast pointer traveled is twice as the slow pointer, Thus:

```
2 * (L1+L2) = L1 + L2 + n * C => L1 + L2 = n * C => L1 = (n - 1) C + (C - L2)
```  
 
Here we can prove that ```n == 1```, and above equation can become ```L1 = C - L2  => L1 + L2 = C```.  

It is guaranteed that slow pointer won't travel more than 1 full circle, and that the fast pointer will only travel exactly one more circle than slow pointer before meeting slow pointer again.

The key observation is that the speed of fast pointer is 2 times than that of slow pointer. Think of it this way: if two runners start running on a circle at the same time, fast runner is twice the speed of the slow runner, then when the slow runner finish the first circle, the fast runner will just finish second circle, and this is the first time they meet after starting. In this problem, when slow pointer start at the "entry point", the fast pointer is at the same point or ahead of the slow pointer, so you can apply the runners'situation here: they will meet before slow pointer start its second circle.

__It can be concluded that the distance between the head location and entry location is equal to the distance between the meeting location and the entry location along the direction of forward movement.__  
  
```cpp  
ListNode *detectCycle(ListNode *head) {
  ListNode *slow(head), *fast(head);
  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
    if (slow == fast) break;
  }
  if (!fast || !fast->next) return nullptr;  // no cycle

  while (head != slow) {
    head = head->next;
    slow = slow->next;
  }

  return head;
}
```
