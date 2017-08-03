Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
  
# Solution
  
It's easy to solve with priority queue.
Suppose the total number of nodes is n, and the list count is k. The total time complexity if (n * log k) .For a priority queue, insertion takes logK time  

### Solution with C++98
```cpp
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
```

### Solution with C++11


```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode dummy(INT_MIN), *pre(&dummy);
        static auto NodeComparator = [](ListNode * left, ListNode * right) {
            return left->val > right->val;
        };
        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(NodeComparator)> min_heap(NodeComparator);
        
        for (ListNode *node : lists) {
            if (node) min_heap.push(node);
        }
        
        while (!min_heap.empty()) {
            ListNode *cur_node = min_heap.top();
            min_heap.pop();
            pre->next = cur_node;
            pre = pre->next;
            if (cur_node->next) {
                min_heap.push(cur_node->next);
            }
        }
        pre->next = nullptr;
        return dummy.next;
    }
};
```
