Given a singly linked list, return a random node's value from the linked list. Each node must have the same probability of being chosen.

Follow up:
What if the linked list is extremely large and its length is unknown to you? Could you solve this efficiently without using extra space?

Example:
```
// Init a singly linked list [1,2,3].
ListNode head = new ListNode(1);
head.next = new ListNode(2);
head.next.next = new ListNode(3);
Solution solution = new Solution(head);

// getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.
solution.getRandom();
```

# Reservoir sampling

Reservoir sampling is a family of randomized algorithms for randomly choosing a sample of k items from a list S containing n items, where n is either a very large or unknown number. Typically n is large enough that the list doesn't fit into main memory.

#### Example: Sample size 1

Suppose we see a sequence of items, one at a time. We want to keep a single item in memory, and we want it to be selected at random from the sequence. If we know the total number of items (n), then the solution is easy: select an index i between 1 and n with equal probability, and keep the i-th element. The problem is that we do not always know n in advance. A possible solution is the following:

1. Keep the first item in memory.
2. When the i-th item arrives (for i > 1 ):
   * with probability  1/i, keep the new item (discard the old one)
   * with probability  i-1/i, keep the old item (ignore the new one)

So:
   * when there is only one item, it is kept with probability 1;
   * when there are 2 items, each of them is kept with probability 1/2;
   * when there are 3 items, the third item is kept with probability 1/3, and each of the previous 2 items are also kept with probability (1/2)(1-1/3) = (1/2)(2/3) = 1/3;

by induction, it is easy to prove that when there are n items, each item is kept with probability 1/n.

# Solution

This is a Reservoir sampling problem.
Here is the basic idea.
1. If there is only one node, there is 1/1 probability to return it.
2. If there are two nodes, when we reach the second node, we make sure there are 1/2 to choose 
   the second node(by replacing the return value).Then the probabily to return the second node is 1/2, and the probability of return the    first node is 1 * 1/2 == 1/2.
3. If there are three nodes, when we reach the thrid node,we make sure there is 1/3 to choose the third node. Then the probability to return the first node or the second node are all 1/2 * 2/3. Here 1/2 is the probabilyt to return either the first node or second node before we reach the third node.
4. and so no....  
  
In summury, we just keep iterating the list till the end, and on i-th node, make sure 1/i probability to replace the previous choosen return value.

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
  /** @param head The linked list's head.
      Note that the head is guaranteed to be not null, so it contains at least one node. */
  Solution(ListNode* head) : m_head(head) {

  }

  /** Returns a random node's value. */
  int getRandom() {
    int reval = m_head->val;
    ListNode *curr(m_head);
    for (int i = 1;curr; ++i) {
      // For i-th node, we make sure there are 1/i probability to replace
      // the previous choosen value.
      if (rand() % i == i - 1) reval = curr->val;
      curr = curr->next;
    }

    return reval;
  }
private:
  ListNode *m_head;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(head);
 * int param_1 = obj.getRandom();
 */
```
