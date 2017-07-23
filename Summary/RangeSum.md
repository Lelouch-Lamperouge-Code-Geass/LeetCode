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
# 304. Range Sum Query 2D - Immutable

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

![alt](https://leetcode.com/static/images/courses/range_sum_query_2d.png?_=5300458)

The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:
```
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
```

Note:  
* You may assume that the matrix does not change.  
* There are many calls to sumRegion function.  
* You may assume that row1 ≤ row2 and col1 ≤ col2.  

### Solution

Construct a 2D array sums[row+1][col+1]

(notice: we add additional blank row sums[0][col+1]={0} and blank column sums[row+1][0]={0} to remove the edge case checking), so, we can have the following definition

sums[i+1][j+1] represents the sum of area from matrix[0][0] to matrix[i][j]

To calculate sums, the ideas as below
```
+-----+-+-------+     +--------+-----+     +-----+---------+     +-----+--------+
|     | |       |     |        |     |     |     |         |     |     |        |
|     | |       |     |        |     |     |     |         |     |     |        |
+-----+-+       |     +--------+     |     |     |         |     +-----+        |
|     | |       |  =  |              |  +  |     |         |  -  |              |
+-----+-+       |     |              |     +-----+         |     |              |
|               |     |              |     |               |     |              |
|               |     |              |     |               |     |              |
+---------------+     +--------------+     +---------------+     +--------------+

   sums[i][j]      =    sums[i-1][j]    +     sums[i][j-1]    -   sums[i-1][j-1]   +  

                        matrix[i-1][j-1]

```

So, we use the same idea to find the specific area's sum

```
+---------------+   +--------------+   +---------------+   +--------------+   +--------------+
|               |   |         |    |   |   |           |   |         |    |   |   |          |
|   (r1,c1)     |   |         |    |   |   |           |   |         |    |   |   |          |
|   +------+    |   |         |    |   |   |           |   +---------+    |   +---+          |
|   |      |    | = |         |    | - |   |           | - |      (r1,c2) | + |   (r1,c1)    |
|   |      |    |   |         |    |   |   |           |   |              |   |              |
|   +------+    |   +---------+    |   +---+           |   |              |   |              |
|        (r2,c2)|   |       (r2,c2)|   |   (r2,c1)     |   |              |   |              |
+---------------+   +--------------+   +---------------+   +--------------+   +--------------+
```

```cpp
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> &matrix) : m_matrix(matrix){
        if (!matrix.empty()) {
            const std::size_t row_size(matrix.size()),col_size(matrix[0].size());
            for (std::size_t i = 0;i < col_size;++i) {
                m_matrix[0][i] = i==0? matrix[0][0] : matrix[0][i] + m_matrix[0][i-1];
            }
            for (std::size_t i=1;i<row_size;++i) {
                m_matrix[i][0] = matrix[i][0] + m_matrix[i-1][0];
            }
            for (std::size_t i=1;i<row_size;++i) {
                for (std::size_t j=1;j<col_size;++j) {
                    m_matrix[i][j] = m_matrix[i][j-1] + m_matrix[i-1][j] - m_matrix[i-1][j-1] 
                    + matrix[i][j];
                }
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        if (m_matrix.empty()) return 0;
        int left_margin = col1-1>=0? m_matrix[row2][col1-1] : 0;
        int top_margin = row1-1>=0? m_matrix[row1-1][col2] : 0;
        int overlap = row1-1>=0 && col1-1>=0? m_matrix[row1-1][col1-1] : 0;
        
        return m_matrix[row2][col2] - left_margin - top_margin + overlap;
    }
private:
    vector<vector<int>> m_matrix;
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
 
 # 308	Range Sum Query 2D - Mutable 

 Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
 
 ![alt](https://leetcode.com/static/images/courses/range_sum_query_2d.png?_=5300458)
 
 The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.
 
 ### Example:
 ```
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10
```

### Note:
* The matrix is only modifiable by the update function.
* You may assume the number of calls to update and sumRegion function is distributed evenly.
* You may assume that row1 ≤ row2 and col1 ≤ col2.

```cpp
class SegtreeNode{
    public:
    int x1, x2, y1, y2;
    SegtreeNode * ltChild, * rtChild, * lbChild, *rbChild;
    int val;
    SegtreeNode(int x1, int y1, int x2, int y2):x1(x1), x2(x2), y1(y1), y2(y2), ltChild(nullptr),lbChild(nullptr), rtChild(nullptr),rbChild(nullptr),val(0){} 
};
class NumMatrix {
public:
    SegtreeNode * root;
    NumMatrix(vector<vector<int>> &matrix) {
        if(matrix.empty() || matrix[0].empty()) return ;
        root = build(matrix, 0, 0, matrix.size() - 1, matrix[0].size() - 1);
    }
    SegtreeNode * build(vector<vector<int>>& matrix, int x1, int y1, int x2, int y2){
        if(x1 > x2 || y1 > y2) return nullptr;
        SegtreeNode * node = new SegtreeNode(x1, y1, x2, y2);
        if(x1 == x2 && y1 == y2){
            node->val = matrix[x1][y1];
        }
        else{
            int xmid = (x1 + x2) / 2;
            int ymid = (y1 + y2) / 2;
            node->ltChild = build(matrix, x1, y1, xmid, ymid);
            node->rtChild = build(matrix, xmid + 1, y1, x2, ymid);
            node->lbChild = build(matrix, x1, ymid + 1, xmid, y2);
            node->rbChild = build(matrix, xmid + 1, ymid + 1, x2, y2);
            node->val = 0;
            node->val += node->ltChild? node->ltChild->val: 0;
            node->val += node->rtChild? node->rtChild->val: 0;
            node->val += node->lbChild? node->lbChild->val: 0;
            node->val += node->rbChild? node->rbChild->val: 0;
        }
        return node;
    }
 
    void update(int row, int col, int val) {
        _update(root, row, col, val);
    }
    void _update(SegtreeNode * p, int row, int col, int val){
        if(p == nullptr) return ;
        if(p->x1 == p->x2 && p->y1 == p->y2){
            p->val = val;
        }
        else{
            int xmid = (p->x1 + p->x2) / 2;
            int ymid = (p->y1 + p->y2) / 2;
            if(row <= xmid){
                if(col <= ymid){
                    _update(p->ltChild, row, col, val);
                }else{
                    _update(p->lbChild, row, col, val);
                }
            }else{
                if(col <= ymid){
                    _update(p->rtChild, row, col, val);
                }else{
                    _update(p->rbChild, row, col, val);
                }
            }
            p->val = 0;
            p->val += p->ltChild? p->ltChild->val: 0;
            p->val += p->rtChild? p->rtChild->val: 0;
            p->val += p->lbChild? p->lbChild->val: 0;
            p->val += p->rbChild? p->rbChild->val: 0;
        }
    }
 
    int sumRegion(int row1, int col1, int row2, int col2) {
        return _sum(root, row1, col1, row2, col2);
    }
    int _sum(SegtreeNode * p, int x1, int y1, int x2, int y2){
        if(p == nullptr) return 0;
        if(p->x1 >= x1 && p->x2 <= x2 && p->y1 >= y1 && p->y2 <= y2){
            return p->val;
        }else if(p->x1 > x2 || p->x2 < x1 || p->y1 > y2 || p->y2 < y1){
            return 0;
        }else{
            int sum = 0;
            sum += _sum(p->ltChild, x1, y1, x2, y2);
            sum += _sum(p->lbChild, x1, y1, x2, y2);
            sum += _sum(p->rtChild, x1, y1, x2, y2);
            sum += _sum(p->rbChild, x1, y1, x2, y2);
            return sum;
        }
        
    }
};
 
 
// Your NumMatrix object will be instantiated and called as such:
// NumMatrix numMatrix(matrix);
// numMatrix.sumRegion(0, 1, 2, 3);
// numMatrix.update(1, 1, 10);
// numMatrix.sumRegion(1, 2, 3, 4);
```




# Summary

### Segment Tree
In computer science, a segment tree is a tree data structure for storing intervals, or segments. It allows querying which of the stored segments contain a given point. It is, in principle, a static structure; that is, it's a structure that cannot be modified once it's built. A similar data structure is the interval tree.

A segment tree for a set I of n intervals uses O(n log n) storage and can be built in O(n log n) time. Segment trees support searching for all the intervals that contain a query point in O(log n + k), k being the number of retrieved intervals or segments.

##### Representation of Segment trees

1. Leaf Nodes are the elements of the input array.  
2. Each internal node represents some merging of the leaf nodes. The merging may be different for different problems. For this problem, merging is sum of leaves under a node.  

An array representation of tree is used to represent Segment Trees. For each node at index i, the left child is at index ```2*i+1```, right child at ```2*i+2``` and the parent is at ```lower_bound(i-1/2)```.

![alt](http://www.geeksforgeeks.org/wp-content/uploads/segment-tree1.png)

### Fenwick tree(binary indexed tree)

A Fenwick tree or binary indexed tree is a data structure that can efficiently update elements and calculate prefix sums in a table of numbers. This structure was proposed by Peter Fenwick in 1994 to improve the efficiency of arithmetic coding compression algorithms.

When compared with a flat array of numbers, the Fenwick tree achieves a much better balance between two operations: element update and prefix sum calculation. In a flat array of  n numbers, you can either store the elements, or the prefix sums. In the first case, computing prefix sums requires linear time; in the second case, updating the array elements requires linear time (in both cases, the other operation can be performed in constant time). Fenwick trees allow both operations to be performed in  O(log n) time. This is achieved by representing the numbers as a tree, where the value of each node is the sum of the numbers in that subtree. The tree structure allows operations to be performed using only O(log n) node accesses.

![alt](http://www.geeksforgeeks.org/wp-content/uploads/BITSum.png)

### Segment tree vs Fenwick tree(BIT)

Here are the things to keep in mind while deciding whether to use segment tree or binary indexed tree:
* Anything that can be done using a BIT can also be done using a segment tree : BIT stores cumulative quantities for certain intervals. Segment tree stores cumulative quantities for those intervals and more. In particular, if we are creating a data structure to deal with an array of size N=2^K, the BIT will have cumulative quantities for N intervals whereas the segment tree will have cumulative values for 2N-1 intervals
* There are things that a segment tree can do but a BIT cannot : A BIT essentially works with cumulative quantities. When the cumulative quantity for interval [i..j] is required, it is found as the difference between cumulative quantities for [1...j] and [1...i-1]. This works only because addition has an inverse operation. You cannot do this if the operation is non-invertible (such as max). On the other hand, every interval on a segment tree can be found as union of disjoint intervals and no inverse operation is required
* A BIT requires only half as much memory as a segment tree : In cases where you have masochistic memory constraints, you are almost stuck with using a BIT
* Though BIT and segment tree operations are both O(log(n)), the segment tree operations have a larger constant factor : This should not matter for most cases. But once again, if you have masochistic time constraints, you might want to switch from a segment tree to a BIT. The constant factor might become more of a problem if the BIT/Segment tree is multidimensional.
* With practice, coding either will be very fast : If you have coded a segment tree 100 times, you will get it very fast the next time you do it. So no need to worry about code being long.


