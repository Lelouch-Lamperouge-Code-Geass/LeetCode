/*
  it is guaranteed that slow pointer won't travel more than 1 full circle, and
  that the fast pointer will only travel exactly one more circle than slow
  pointer before meeting slow pointer again.
  The key observation is that the speed of fast pointer is 2 times than that of
  slow pointer. Think of it this way: if two runners start running on a circle
  at the same time, fast runner is twice the speed of the slow runner, then when
  the slow runner finish the first circle, the fast runner will just finish
  second circle, and this is the first time they meet after starting. In this
  problem, when slow pointer start at the "entry point", the fast pointer is at
  the same point or ahead of the slow pointer, so you can apply the runners'
  situation here: they will meet before slow pointer start its second circle.
*/
ListNode *detectCycle(ListNode *head) {
  ListNode *slow(head), *fast(head);
  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
    if (slow == fast) break;
  }
  if (!fast || !fast->next) return nullptr;  // no cycle

  while (head != slow) {
    head = head->next;
    slow = slow->next;
  }

  return head;
}
