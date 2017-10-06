Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a __binary search tree__. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary search tree can be serialized to a string and this string can be deserialized to the original tree structure.

__The encoded string should be as compact as possible.__

__Note__: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.


# Solution

### Solution 1

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
        ostringstream oss;
        serialize(root, oss);
        return oss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream iss(data);
        return deserialize(iss);
    }
    
private:
    void serialize(TreeNode* root, ostringstream &oss) {
        if (!root) {
            oss << '#' << ' ';
        } else {
            oss << root->val << ' ';
            serialize(root->left, oss);
            serialize(root->right, oss);
        }
    }
    
    TreeNode* deserialize(istringstream &iss) {
        string val("");
        iss >> val;
        if (val == "#") {
            return nullptr;
        } else {
            TreeNode* cur = new TreeNode(std::stoi(val));
            cur->left = deserialize(iss);
            cur->right = deserialize(iss);
            return cur;
        }
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
```

### Solution 2

What's the difference between this and #297 ?

The difference is the bold "The encoded string should be as compact as possible" here. The special property of binary search trees compared to general binary trees allows a more compact encoding. So while the solutions to problem #297 still work here as well, they're not as good as they should be.

For Binary tree solution, we need to have "#" or "null" to indicate null node in the serialized string.
However, for BST, we don't need such "#" which make it more compact.

The reason is that we can reconstruct BST by only using preorder(/postorder/levelorder) traversal.
However, in the binary tree situation, we need to use preorder(/postorder/levelorder) + inorder to reconstruct the tree. If we want to directly construct BT, we have to use "#" or "null".

Sharing my solution which doesn't have to parse string for comma at all!

The encoding schema is preorder of BST, and to decode this we can use the same preorder traversal to do it in one pass with recursion in O(n) time.

To minimize the memory, I used binary format instead of ascii format for each integer, just burn those int into 4 chars will save you a lot!!!

Really if using ASCII numbers you are paying a lot of penalty memory for integers over 4 digit long and parsing comma is just as painful.

```cpp
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string order;
        inorderDFS(root, order);
        return order;
    }
    
    inline void inorderDFS(TreeNode* root, string& order) {
        if (!root) return;
        char buf[4];
        memcpy(buf, &(root->val), sizeof(int)); //burn the int into 4 chars
        for (int i=0; i<4; i++) order.push_back(buf[i]);
        inorderDFS(root->left, order);
        inorderDFS(root->right, order);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int pos = 0;
        return reconstruct(data, pos, INT_MIN, INT_MAX);
    }
    
    inline TreeNode* reconstruct(const string& buffer, int& pos, int minValue, int maxValue) {
        if (pos >= buffer.size()) return NULL; //using pos to check whether buffer ends is better than using char* directly.
        
        int value;
        memcpy(&value, &buffer[pos], sizeof(int));
        if (value < minValue || value > maxValue) return NULL;
        
        TreeNode* node = new TreeNode(value);
        pos += sizeof(int);
        node->left = reconstruct(buffer, pos, minValue, value);
        node->right = reconstruct(buffer, pos, value, maxValue);
        return node;
    }
};
```
