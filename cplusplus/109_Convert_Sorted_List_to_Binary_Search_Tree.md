Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

# Solution

This problem is quite similar to convert a sorted array to height balanced BST.

Similarlly, we need to find the mid point first, and then we build left tree based on left part, build right tree based on right part.

And then you realize we just conver the original problem into two smaller subproblems.

> In computer science, divide and conquer is an algorithm design paradigm based on multi-branched recursion. A divide and conquer algorithm works by recursively breaking down a problem into two or more sub-problems of the same or related type, until these become simple enough to be solved directly. The solutions to the sub-problems are then combined to give a solution to the original problem.

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return build(head,nullptr);
    }
private:
    TreeNode * build(ListNode* begin,ListNode* end){
        if(begin==end) return nullptr;
        if(begin->next == end) return new TreeNode(begin->val);
        ListNode *mid(begin),*fast(begin);
        while(fast != end && fast->next != end){
            fast = fast->next->next;
            mid = mid->next;
        }
        TreeNode *node = new TreeNode(mid->val);
        node->left = build(begin,mid);
        node->right = build(mid->next,end);
        return node;
    }
};
```

A different style, while I think above solution is better.

```cpp
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) return nullptr;
        if (!head->next) return new TreeNode(head->val);
        
        ListNode *slow(head), *fast(head), *pre_slow(nullptr);
        
        while (fast && fast->next && fast->next->next) {
            fast = fast->next->next;
            pre_slow = slow;
            slow = slow->next;
        }
        
        TreeNode *root = new TreeNode(slow->val);
        
        root->right = sortedListToBST(slow->next);
        
        if (pre_slow) {
            pre_slow->next = nullptr;
            root->left = sortedListToBST(head);
            pre_slow->next = slow; // revert back
        } else {
            root->left = nullptr;
        }
        
        return root;
    }
    
};
```
