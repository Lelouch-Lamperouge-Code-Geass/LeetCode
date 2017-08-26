You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:

```
Given nums = [5, 2, 6, 1]

To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Return the array [2, 1, 1, 0].
```    

# Solution

### Solution one

```cpp
class Solution {
private:
    struct TreeNode;
    typedef std::shared_ptr<TreeNode> TreeNodePtr;
    
    struct TreeNode {
        TreeNode(int value) : m_value(value), m_left_children(0),
                                           m_count(1), m_left(nullptr), m_right(nullptr) {}
        int m_value;
        int m_left_children; // recording the amount of left children
        int m_count; // recording the amount of duplicate numbers
        TreeNodePtr m_left, m_right;
    };
    
    // return the amount of previous smaller nodesm
    int Insert(TreeNodePtr & root, const int number) {
        if (!root) { 
            root = std::make_shared<TreeNode>(number);
            return 0;
        } else {
            if (number > root->m_value) {
                return root->m_left_children + root->m_count + Insert(root->m_right, number);
            }  else if (number < root->m_value){
                ++ root->m_left_children;
                return Insert(root->m_left, number);
            }  else { // equal
                ++ root->m_count;
                return root->m_left_children;
            }
        }
    }
    
public:
    vector<int> countSmaller(vector<int>& nums) {
            const std::size_t nums_size(nums.size());
            if (nums_size == 0) return vector<int>();
            vector<int> reval(nums_size, 0);
            TreeNodePtr root(nullptr);
            for (int i = nums_size - 1; i < nums_size; --i) {
                reval[i] = Insert(root, nums[i]);
            }
            return reval;
    }
};
```


### Solution Two

```cpp
struct Node;
typedef std::shared_ptr<Node> NodePtr;
struct Node {
    Node(int val) : m_value(val), m_count(1), m_left_children(0), m_left(nullptr), m_right(nullptr) {
        
    }
    int m_value;
    int m_left_children;
    int m_count;
    NodePtr m_left;
    NodePtr m_right;
};


class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        std::vector<int> reval(nums.size(), 0);
        NodePtr root(nullptr);
        for (std::size_t nums_size = nums.size(), i = nums_size; i-- > 0; ) {
            reval[i] = addToTree(nums[i], 0, root);
        }
        
        return reval;
    }
    
private:
    // Return the smaller number count after itself
    int addToTree(const int val, const int smaller_count, NodePtr & root) {
        if (!root) {
            root = std::make_shared<Node>(val);
            return smaller_count;
        } else {
            if (val > root->m_value) {
                return addToTree(val, smaller_count + root->m_count + root->m_left_children, root->m_right);
            } else if (val < root->m_value){
                ++ root->m_left_children;
                return addToTree(val, smaller_count, root->m_left);
            } else { // val == root->m_value;
                ++ root->m_count;
                return smaller_count + root->m_left_children;
            }
        }
    }
};
```
