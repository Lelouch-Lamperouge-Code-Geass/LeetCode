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
