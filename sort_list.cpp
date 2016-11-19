// Copyright (C) 2016 by Yang Liu
/*
 * Bottom-up mergesort
*/
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
/*
 * Top-down mergesort
*/
class Solution {
public:
  ListNode* sortList(ListNode* head) {
    if(!head || !head->next) return head;
    ListNode *slow(head), *fast(head);
    while (fast && fast->next && fast->next->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    ListNode* r_head = sortList(slow->next);
    slow->next = nullptr;
    ListNode* l_head = sortList(head);
    return merge(l_head,r_head);
  }

  ListNode* merge(ListNode* left,ListNode* right) {
    ListNode dummy(INT_MIN),*pre(&dummy);
    while (left && right) {
      if (left->val < right->val) {
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
