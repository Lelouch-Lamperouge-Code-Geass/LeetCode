/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode reverseKGroup(ListNode head, int k) {
        ListNode dummy = new ListNode(0), pre = dummy, curr = head, next = null;
        dummy.next = head;
        
        // get total nodes count
        int count = 0;
        while (curr != null) {
            ++ count;
            curr = curr.next;
        }
        
        
        while (count >= k) {
            curr = pre.next;
            next = curr.next;
            
            for (int i = 0; i < k - 1; ++ i) {
                // Here we keep appending next node to pre node
                curr.next = next.next;
                next.next = pre.next;
                pre.next = next;
                
                next = curr.next;
            }
            
            count -= k;
            pre = curr;
        }
        
        return dummy.next;
    }
}
