class Solution {
public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    ListNode dummy(INT_MIN), *pre(&dummy);
    // this priority queue could be considered as a min-heap
    std::priority_queue<ListNode*,vector<ListNode*>,Compare> pqueue;
    for (ListNode * node : lists) {
      if(node) pqueue.push(node);
    }

    while( !pqueue.empty() ) {
      ListNode* curr = pqueue.top();
      pqueue.pop();
      pre->next = curr;
      pre = pre->next;
      if(curr->next) pqueue.push(curr->next);
    }
    pre->next = nullptr;
    return dummy.next;
  }
private:
  class Compare {
  public:
    bool operator() (ListNode* left, ListNode* right) {
      return left->val > right->val;
    }
  };
};
