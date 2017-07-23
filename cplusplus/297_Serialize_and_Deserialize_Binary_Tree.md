Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

```
 1
   / \
  2   3
     / \
    4   5  
```

as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

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
class Codec {
public:

  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    std::ostringstream oss;
    serialize_preorder(root,oss);
    return oss.str();
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    istringstream in(data);
    return deserialize(in);
  }
private:
  void serialize_preorder(TreeNode* root, std::ostringstream & oss) {
    if (root) {
      oss << root->val << ' ';
      serialize_preorder(root->left,oss);
      serialize_preorder(root->right,oss);
    } else {
      oss <<'#'<<' ';
    }
  }
  TreeNode* deserialize(istringstream & iss) {
    string cur_val;
    iss >> cur_val;
    if (cur_val == "#") {
      return nullptr;
    } else {
      TreeNode* reval = new TreeNode( std::stoi(cur_val) );
      reval->left = deserialize(iss);
      reval->right = deserialize(iss);
      return reval;
    }
  }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
```
