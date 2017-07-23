# 303. Range Sum Query - Immutable

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

##### Example:
```
Given nums = [-2, 0, 3, -5, 2, -1]  

sumRange(0, 2) -> 1  
sumRange(2, 5) -> -1  
sumRange(0, 5) -> -3  
```
##### Note:  
* You may assume that the array does not change.  
* There are many calls to sumRange function.  


### Solution

```cpp
class NumArray {
public:
    NumArray(vector<int> &nums) : m_nums(nums.size(),0) {
        const std::size_t nums_size(nums.size());
        for (std::size_t i = 0;i < nums_size; ++i) {
            m_nums[i] = (i==0? nums[i] : m_nums[i-1] + nums[i]); 
        }
    }

    int sumRange(int i, int j) {
        return (i==0? m_nums[j] : m_nums[j] - m_nums[i - 1]);
    }
private:
    vector<int> m_nums;
};
```

# 307. Range Sum Query - Mutable

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val. 

##### Example:
```
Given nums = [1, 3, 5]  

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
```

##### Note:
* The array is only modifiable by the update function.  
* You may assume the number of calls to update and sumRange function is distributed evenly.  

### Solution

In computer science, a segment tree is a tree data structure for storing intervals, or segments. It allows querying which of the stored segments contain a given point. It is, in principle, a static structure; that is, it's a structure that cannot be modified once it's built. A similar data structure is the interval tree.

A segment tree for a set I of n intervals uses O(n log n) storage and can be built in O(n log n) time. Segment trees support searching for all the intervals that contain a query point in O(log n + k), k being the number of retrieved intervals or segments.

##### Representation of Segment trees

1. Leaf Nodes are the elements of the input array.  
2. Each internal node represents some merging of the leaf nodes. The merging may be different for different problems. For this problem, merging is sum of leaves under a node.  

An array representation of tree is used to represent Segment Trees. For each node at index i, the left child is at index ```2*i+1```, right child at ```2*i+2``` and the parent is at ```lower_bound(i-1/2)```.

![alt](http://www.geeksforgeeks.org/wp-content/uploads/segment-tree1.png)

```cpp
struct SegmentTreeNode;
typedef std::shared_ptr<SegmentTreeNode> SegmentTreeNodePtr;
struct SegmentTreeNode {
  SegmentTreeNode(int value, std::size_t start, std::size_t end)
    : m_value(value), m_start(start), m_end(end), m_left(nullptr), m_right(nullptr) {

  }

  int m_value;
  SegmentTreeNodePtr m_left, m_right;
  std::size_t m_start, m_end;

};

SegmentTreeNodePtr BuildSegmentTree(const std::vector<int> &nums,
                                    std::size_t start,
                                    std::size_t end) {
  if (start == end) { // Leaf node, it is an element of input vector
    return std::make_shared<SegmentTreeNode>(nums[start], start, end);
  } else { // Non-leaf, it's m_value should be the sum of both children
    std::size_t mid = start + (end - start) / 2;
    SegmentTreeNodePtr left = BuildSegmentTree(nums, start, mid);
    SegmentTreeNodePtr right = BuildSegmentTree(nums, mid + 1, end);
    SegmentTreeNodePtr cur_node = std::make_shared<SegmentTreeNode>(left->m_value + right->m_value, start, end);
    cur_node->m_left = left;
    cur_node->m_right = right;
    return cur_node;
  }
}

int GetSumRange(SegmentTreeNodePtr &root, std::size_t start, std::size_t end) {
  if (root->m_start == start && root->m_end == end) {  // Leaf node
      return root->m_value;
  } else { // Non-leaf node
    std::size_t root_mid = root->m_start + (root->m_end - root->m_start) / 2;
    if (end <= root_mid) {
      return GetSumRange(root->m_left, start, end);
    } else if (start > root_mid){
      return GetSumRange(root->m_right, start, end);
    } else {
      return GetSumRange(root->m_left, start, root_mid) + GetSumRange(root->m_right, root_mid + 1, end);
    }
  }
}


void UpdateSegmentTree(SegmentTreeNodePtr &root, std::size_t position, int value) {
  if (root->m_start == position && root->m_end == position) {
    // Leaf node
    root->m_value = value;
  } else {
    std::size_t mid = root->m_start + (root->m_end - root->m_start) / 2;
    if (position <= mid) {
      UpdateSegmentTree(root->m_left, position, value);
    } else {
      UpdateSegmentTree(root->m_right, position, value);
    }
    // Don't forget to update current node's sum.
    // And we know every non-leaf node have two children
    // so no need to perform null check for m_left and m_right
    root->m_value = root->m_left->m_value + root->m_right->m_value;
  }
}

class NumArray {
public:
  NumArray(vector<int> nums) {
    if (!nums.empty()) {
      m_root = BuildSegmentTree(nums, 0, nums.size() - 1);
    }
  }

  void update(int i, int val) {
    UpdateSegmentTree(m_root, i, val);
  }

  int sumRange(int i, int j) {
    return (i <= j ? GetSumRange(m_root, i, j) : 0);
  }
private:
  SegmentTreeNodePtr m_root;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */
 ```
 
 
