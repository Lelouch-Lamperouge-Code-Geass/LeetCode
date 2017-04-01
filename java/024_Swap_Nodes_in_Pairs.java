/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode swapPairs(ListNode head) {
        ListNode dummy = new ListNode(0), pre = dummy;
        dummy.next = head;
        
        while (pre.next != null && pre.next.next != null) {
            ListNode left = pre.next, right = left.next;
            pre.next = right;
            left.next = right.next;
            right.next = left;
            pre = left;
        }
        
        return dummy.next;
    }
}
