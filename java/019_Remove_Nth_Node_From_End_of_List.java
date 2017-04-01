/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode curr = dummy, pre = dummy;
        
        // Move curr in front so that the gap between pre and curr becomes n
        while (n > 0 && curr != null) {
            -- n;
            curr = curr.next;
        }
        
        //Move curr to the end, maintaining the gap between pre and curr
        if (curr == null) return head;
        while (curr.next != null) {
            curr = curr.next;
            pre = pre.next;
        }
        
        // remove the target node
        pre.next = pre.next.next;
        
        return dummy.next;
    }
}
