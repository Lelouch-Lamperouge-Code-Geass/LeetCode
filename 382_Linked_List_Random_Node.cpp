class Solution {
public:
  /** @param head The linked list's head.
      Note that the head is guaranteed to be not null, so it contains at least one node. */
  Solution(ListNode* head)  : m_head(head){

  }

  /** Returns a random node's value. */
  int getRandom() {
    ListNode * chosen = m_head;
    int reval = chosen->val;
    for (std::size_t i=1;chosen->next;++i) {
      chosen = chosen->next;
      std::size_t rand_i = rand() % (i+1);
      if (rand_i == i) reval = chosen->val;
    }
    return reval;
  }
private:
  ListNode * m_head;
};
