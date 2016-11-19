bool hasCycle(ListNode *head) {
  ListNode *slow(head),*fast(head);
  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
    if (slow == fast) return true;
  }
  return false;
}
