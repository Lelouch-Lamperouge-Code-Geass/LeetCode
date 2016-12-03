/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
  bool isPalindrome(ListNode* head) {
    if (!head || !head->next) return true;

    // find the middle node
    ListNode *slow(head),*fast(head);
    while(fast && fast->next && fast->next->next) {
      fast = fast->next->next;
      slow = slow->next;
    }

    // Reverse the right half
    ListNode *right_head = reverse(slow->next);
    ListNode *temp = right_head; // save it for recovery
    slow->next = nullptr;
    // right now we have two separate lists
    bool reval(true);
    while (head && right_head) {
      if (head->val != right_head->val) {
        reval = false;
        break;
      }
      head = head->next;
      right_head = right_head->next;
    }

    slow->next = reverse(temp); //recover
    return reval;
  }
private:
  ListNode* reverse(ListNode* head) {
    if(!head || !head->next) return head;
    ListNode dummy(0), *pre(head), *next(nullptr);
    dummy.next = head;
    while (head) {
      next = head->next;
      head->next = pre;
      pre = head;
      head = next;
    }
    dummy.next->next = nullptr; // set tail's next to be nullptr
    return pre;
  }
};
