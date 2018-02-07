Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.

##### Example 1:

Given tree s:

```
     3
    / \
   4   5
  / \
 1   2
```
 
Given tree t:

```
   4 
  / \
 1   2
```

Return true, because t has the same structure and node values with a subtree of s.

##### Example 2:

Given tree s:

```
     3
    / \
   4   5
  / \
 1   2
    /
   0
```

Given tree t:

```
   4
  / \
 1   2
```

Return false.

# Solution

### Solution one

For each node during pre-order traversal of s, use a recursive function isSame to validate if sub-tree started with this node is the same with t.

The isSameTree function costs ```O(num_of_t)```, and we are basically calling it on each node in Tree s.
So the time complexity is ```O(num_of_s * num_of_t)```.

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
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (s) {
            if (isSameTree(s, t)) {
                return true;
            }
            return isSubtree(s->left, t) || (isSubtree(s->right, t));
        } else {
            return s == t;
        }
    }
private:
    bool isSameTree(TreeNode *root1, TreeNode *root2) {
        if (!root1 || !root2) {
            return root1 == root2;
        } else {
            if (root1->val != root2->val) {
                return false;
            }
            
            return isSameTree(root1->left, root2->left) && isSameTree(root1->right, root2->right);
        }
    }
};
```

### Solution two

If we encode the tree into a unique string, and check whether the encoded string for s has a substring for encoded string for t. This may bring better performance. However, you need to use KMP algorithm to implement the substring-searching function in order to get ```O(length_of_encoded_s + length_of_encoded_t)```. Here I just use C++ string::find which has much worse efficiency, just to make the point.

Another thing you need to be careful about is how to generate the encoded string.

```
[12]
[2]
```

If we put comma after the tree node value, the encoded string will be 

```
12,
2,
```

respectively, which will mistakenly judge that t is a subtree of s.

Instead, we should encode them like this

```
,12
,2
```


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
private:
    void preOrderEncode(TreeNode *node, ostringstream &oss) {
        if (node) {
            oss << ',' << node->val;
            preOrderEncode(node->left, oss);
            preOrderEncode(node->right, oss);
        } else {
             oss << ',' << '#';
        }
    }
    string preOrderEncode(TreeNode *node){
        ostringstream oss;
        preOrderEncode(node, oss);
        return oss.str();
    }
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        string encoded_s = preOrderEncode(s);
        string encoded_t = preOrderEncode(t);
        return encoded_s.find(encoded_t) != std::string::npos;
    }
};
```
