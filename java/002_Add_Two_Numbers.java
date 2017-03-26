public class Solution {
      public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(0);
        ListNode pre = dummy;
        int carry = 0;
        while (l1 != null || l2 != null || carry != 0) {
          int cur_val = 0;
          if (l1 != null) { cur_val += l1.val; l1 = l1.next;}
          if (l2 != null) { cur_val += l2.val; l2 = l2.next;}
          cur_val += carry;
          carry = cur_val / 10;

          ListNode curr = new ListNode(cur_val % 10);

          pre.next = curr;
          pre = curr;
        }

        return dummy.next;
      }
}
