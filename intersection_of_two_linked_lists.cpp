/*
    If one of them reaches the end earlier then reuse it
         by moving it to the beginning of other list.
         Once both of them go through reassigning,
         they will be equidistant from the collision point.
If no intersection, p1 and p2 will reach NULL at the same time.
*/
class Solution {
 public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *a(headA), *b(headB);
    while (a && b && a != b) {
      a = a->next;
      b = b->next;
      if (a == b) return a;
      if (!a) a = headB;
      if (!b) b = headA;
    }
    return a == b ? a : nullptr;
  }
};
