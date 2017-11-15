Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
  
# Solution

The most intuitive solution is : we traverse the "current head node" of all the lists and take the node with minimal value, add it to the final list, and move the minimal "current head node" to its next node. This operation takes O(K). Since we need to perform this operation everytime we add a node to final list and there are N nodes in total. The total time complexity is O(NK).

How to improve it? We can improve it only if we can improve on "get the minimal value node" operation. We can do that with priority queue. 

Suppose the total number of nodes is n, and the list count is k. The total time complexity if (n * log k) .For a priority queue, insertion takes logK time.  

Note here that comparing to above brute-force solution which costs O(1) space complexity, here we introduced a priority queue, which makes space complexity to be O(k). Hence here we did Space–time tradeoff. 

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
