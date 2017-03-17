// Copyright (C) 2016 by Yang Liu

void reorderList(ListNode* head) {
  if (!head || !head->next) return;
  ListNode *slow(head), *fast(head), *lt(nullptr);
  while (fast && fast->next) {
    fast = fast->next->next;
    lt = slow;
    slow = slow->next;
  }

  // lt is the tail of left half.
  // reverse the right half.
  ListNode *pre(lt), *next(nullptr);
  while (slow) {
    next = slow->next;
    slow->next = pre;
    pre = slow;
    slow = next;
  }

  // pre is the head of right half now
  lt->next->next = nullptr;
  lt->next = nullptr;

  ListNode dummy(0), *pp(&dummy);
  while (head && pre) {
    pp->next = head;
    head = head->next;
    pp = pp->next;

    pp->next = pre;
    pre = pre->next;
    pp = pp->next;
  }
  pp->next = head ? head : pre;
  head =  dummy.next;
}
