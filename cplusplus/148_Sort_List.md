
Sort a linked list in O(n log n) time using constant space complexity.
  
# Solution  
  
This problem requires O(n log n) time complexity, so we have two most common algorithm candidates, merge-sort and quick-sort.
  
Since here we have a linked list, we'd better go with merge-sort. For more information, please refer "Knowledge" section.

Note that this problem requires __constant space complexity__.
  
Therefore we can't us top-down merge sort, instead we need to use  bottom-up merge sort.

### Solution 1 : bottom-up merge sort 

  
```cpp
class Solution {
public:
  ListNode* sortList(ListNode* head) {
    ListNode dummy(0);
    dummy.next = head;

    int count(0);
    while(head){
      ++ count;
      head = head->next;
    }

    ListNode *left(nullptr), *right(nullptr), *pre(nullptr);
    for(int len = 1; len < count; len <<= 1){
      head = dummy.next;
      pre = & dummy;
      while(head){
        left = head;
        right = split(left,len);// strip off len nodes
        head = split(right,len);// strip off len nodes

        // merge and append to previous list.
        // move pre to the end.
        pre->next = merge(left,right);
        while(pre->next) pre = pre->next;

      }
    }
    return dummy.next;
  }
private:
  /**
   * Divide the linked list into two lists,
   * while the first list contains first n ndoes
   * return the second list's head
   */
  ListNode* split(ListNode *head, int n){
    //if(!head) return NULL;
    for(int i = 1; head && i < n; ++i) head = head->next;

    if(!head) return NULL;
    ListNode *second = head->next;
    head->next = NULL;
    return second;
  }

  ListNode* merge(ListNode* left, ListNode* right){
    ListNode dummy(0),*pre(&dummy);
    while(left && right){
      if(left->val < right->val){
        pre->next = left;
        left = left->next;
      } else {
        pre->next = right;
        right = right->next;
      }
      pre = pre->next;
    }
    pre->next = left? left : right;
    return dummy.next;
  }
};
```


### Solution 2 : top-down merge sort

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
  ListNode* sortList(ListNode* head) {
    if (!head||!head->next) return head;
    ListNode *slow(head),*fast(head);
    while (fast&&fast->next&&fast->next->next) {
      fast = fast->next->next;
      slow = slow->next;
    }

    ListNode *right_head(slow->next);
    slow->next = nullptr;

    ListNode* left_head = sortList(head);
    right_head = sortList(right_head);
    return mergeList(left_head, right_head);
  }
private:
  ListNode *mergeList(ListNode* left, ListNode* right){
    ListNode dummy(0),*pre(&dummy);
    while (left && right) {
      if (left->val<right->val) {
        pre->next = left;
        left = left->next;
      } else {
        pre->next = right;
        right = right->next;
      }
      pre = pre->next;
    }
    pre->next = left? left : right;
    return dummy.next;
  }
};
```

# Knowledge

### Why Quick Sort preferred for Arrays and Merge Sort for Linked Lists?

##### Why is Quick Sort preferred for arrays?

* Quick Sort in its general form is an in-place sort (i.e. it doesn’t require any extra storage) whereas merge sort requires O(N) extra storage, N denoting the array size which may be quite expensive. Allocating and de-allocating the extra space used for merge sort increases the running time of the algorithm.

* Comparing average complexity we find that both type of sorts have O(NlogN) average complexity but the constants differ. For arrays, merge sort loses due to the use of extra O(N) storage space.
  
* Most practical implementations of Quick Sort use randomized version. The randomized version has expected time complexity of O(nLogn). The worst case is possible in randomized version also, but worst case doesn’t occur for a particular pattern (like sorted array) and randomized Quick Sort works well in practice.
  
* Quick Sort is also a cache friendly sorting algorithm as it has good locality of reference when used for arrays.
  
* Quick Sort is also tail recursive, therefore tail call optimizations is done.

##### Why is Merge Sort preferred for Linked Lists?
  
* In case of linked lists the case is different mainly due to difference in memory allocation of arrays and linked lists. Unlike arrays, linked list nodes may not be adjacent in memory.
  
* Unlike array, in linked list, we can insert items in the middle in O(1) extra space and O(1) time. Therefore merge operation of merge sort can be implemented without extra space for linked lists.
  
* In arrays, we can do random access as elements are continuous in memory. Let us say we have an integer (4-byte) array A and let the address of A[0] be x then to access A[i], we can directly access the memory at (x + i*4). Unlike arrays, we can not do random access in linked list.
  
* Quick Sort requires a lot of this kind of access. In linked list to access i’th index, we have to travel each and every node from the head to i’th node as we don’t have continuous block of memory. Therefore, the overhead increases for quick sort. Merge sort accesses data sequentially and the need of random access is low.  
