You need to construct a binary tree from a string consisting of parenthesis and integers.

The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis. The integer represents the root's value and a pair of parenthesis contains a child binary tree with the same structure.

You always start to construct the left child node of the parent first if it exists.

##### Example:

```
Input: "4(2(3)(1))(6(5))"
Output: return the tree root node representing the following tree:

       4
     /   \
    2     6
   / \   / 
  3   1 5   
```

##### Note:

1. There will only be '(', ')', '-' and '0' ~ '9' in the input string.
2. An empty tree is represented by "" instead of "()".


# Solution

__Note that here the number can be negative since the input has '-'. But it has no '+'.__

### Iterative solution

Here we use a stack to store nodes. Whenever we find a number, we create a new node. And if the stack is not empty, then add current node as previous node's left/right child. Whenever we meet ')', pop one node out of the stack.

```cpp
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
    TreeNode* str2tree(string s) {
        std::stack<TreeNode*> nodes;
        for (std::size_t i = 0, n = s.size(); i < n; ) {
            if (s[i] == ')') {
                nodes.pop();
                ++ i;
            } else if (s[i] == '(') {
                ++ i;
            } else { // is number
                std::size_t j(i);

                if (s[j] == '-') ++ j;
                while (j < n && std::isdigit(s[j])) ++ j;

                int number = std::stoi(s.substr(i, j - i));

                TreeNode *curr = new TreeNode(number);

                if (!nodes.empty()) {
                    TreeNode *pre = nodes.top(); // Note that STL stack top return reference
                    if (!pre->left) pre->left = curr;
                    else pre->right = curr;
                }

                nodes.push(curr);
                
                i = j;
            }
        }
        
        return nodes.empty() ? nullptr : nodes.top();
    }
};
```

### Recursive solution 


```cpp
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
    TreeNode* str2tree(string s) {
        std::size_t pos(0);
        return preorder(s, pos);
    }
private:
    TreeNode* preorder(const std::string &s, std::size_t &pos) {
        if (pos == s.size()) {
            return nullptr;
        } else {
            std::size_t i(pos);
            
            if (s[i] == '-') ++i; // Could be a negative number
            
            while (i < s.size() && std::isdigit(s[i])) ++ i;
            

            int number = std::stoi(s.substr(pos, i - pos));
            
            TreeNode *curr = new TreeNode(number);
            pos = i;

            if (s[pos] == '(') { // Left branch
                curr->left = preorder(s, ++ pos);
                ++ pos; // ')'
            } 

            if (s[pos] == '(') { // Right branch
                curr->right = preorder(s, ++ pos);
                ++ pos; // ')'
            } 
            
            return curr;
        }
    }
};
```

A different style.

```cpp
class Solution {
private:
    TreeNode* deserialize(const string &s, size_t &pos) {
        if (pos == s.size()) {
            return nullptr;
        } else {
            size_t next_pos = s.find_first_not_of("-1234567890", pos);
            
            int num = stoi(s.substr(pos, next_pos - pos));
            
            TreeNode *cur_node = new TreeNode(num);
            
            pos = next_pos;
            
            if (pos < s.size() && s[pos] == '(') {
                cur_node->left = deserialize(s, ++pos);
                ++ pos;
            }
            
            if (pos < s.size() && s[pos] == '(') {
                cur_node->right = deserialize(s, ++pos);
                ++ pos;
            }
            
            return cur_node;
        }
    }
public:
    TreeNode* str2tree(string s) {
        size_t pos(0);
        return deserialize(s, pos);
    }
};
```

