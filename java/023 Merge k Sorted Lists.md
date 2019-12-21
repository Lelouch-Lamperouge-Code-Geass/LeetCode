Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
  
# Solution

### Analysis

The most intuitive solution is : we traverse the "current head node" of all the lists and take the node with minimal value, add it to the final list, and move the minimal "current head node" to its next node. This operation takes O(K). Since we need to perform this operation everytime we add a node to final list and there are N nodes in total. The total time complexity is O(NK).

How to improve it? We can improve it only if we can improve on "get the minimal value node" operation. We can do that with priority queue. 

Suppose the total number of nodes is n, and the list count is k. The total time complexity if ```(n * log k)``` .For a priority queue, insertion takes ```logK``` time.  

Note here that comparing to above brute-force solution which costs O(1) space complexity, here we introduced a priority queue, which makes space complexity to be ```O(k)```. Hence here we did Space–time tradeoff. 

### Code

Callout : in general, we should return a whole new list without modifying the input lists.

```java
class Solution {
    public ListNode mergeKLists(ListNode[] lists) {
        if (lists == null || lists.length == 0) return null;

        /* Before Java 8
        PriorityQueue<ListNode> priorityQueue = new PriorityQueue<ListNode>(lists.length,
                new Comparator<ListNode>(){
                    @Override
                    public int compare(ListNode listNode1,ListNode listNode2){
                        return listNode1.val - listNode2.val;
                    }
        });
        */
        
        PriorityQueue<ListNode> queue= new PriorityQueue<ListNode>(lists.length, (a, b)-> a.val - b.val);
        
        for (ListNode listNode : lists) {
            if (listNode != null) {
                priorityQueue.add(listNode);
            }
        }

        ListNode preHead = new ListNode(Integer.MIN_VALUE);
        ListNode tail = preHead;

        while (!priorityQueue.isEmpty()) {
            ListNode polledNode = priorityQueue.poll();
            if (polledNode.next != null) {
                priorityQueue.add(polledNode.next);
            }
            tail.next = new ListNode(polledNode.val);
            tail = tail.next;
        }

        return preHead.next;
    }
}
```




