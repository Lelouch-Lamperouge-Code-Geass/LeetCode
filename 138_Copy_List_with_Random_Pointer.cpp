// Copyright (C) 2016 by Yang Liu
RandomListNode *copyRandomList(RandomListNode *head) {
  RandomListNode *curr(head),*temp(nullptr);
  // clone each node and append it to the original node
  while (curr) {
    temp = new RandomListNode(curr->label);
    temp->next = curr->next;
    temp->random = curr->random;
    curr->next = temp;
    curr = temp->next;
  }

  // adjust random pointer of clone nodes
  curr = head;
  while (curr) {
    if(curr->random)curr->next->random = curr->random->next;
    curr = curr->next->next;
  }
  // split the list
  RandomListNode dummy(0),*pre(&dummy);
  curr = head;
  while (curr) {
    pre->next = curr->next;
    if(curr->next)curr->next = curr->next->next;

    pre = pre->next;
    curr = curr->next;
  }
  return dummy.next;
}
