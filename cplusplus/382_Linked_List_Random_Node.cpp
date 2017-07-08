/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// This is a Reservoir sampling problem.
// Here is the basic idea.
// 1. If there is only one node, there is 1/1 probability to return it.
// 2. If there are two nodes, when we reach the second node, we make sure there are 1/2 to choose
// the second node(by replacing the return value).
// Then the probabily to return the second node is 1/2, and the probability of return the first node is 1 * 1/2 == 1/2.
// 3. If there are three nodes, when we reach the thrid node,we make sure there is 1/3 to choose the third node.
// Then the probability to return the first node or the second node are all 1/2 * 2/3. Here 1/2 is the probabilyt to return
// either the first node or second node before we reach the third node.
// 4. and so no....
// In summury, we just keep iterating the list till the end, and on i-th node, make sure 1/i probability to replace
// the previous choosen return value.
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
