Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.
Example:
```
Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
```
Note:
The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.

# Solution
  
Range sum with _mutable_ elements, which means we need use either segment tree or binary indexed tree.  
  
### Solution with segment tree

Maintain a balanced binary tree. Each node of the binary tree corresponds to some consecutive range. In particular, the root corresponds to the entire [1,n] range. Its left child corresponds to [1,n/2] range and the right child corresponds to [n/2+1,n] range and so on. More formally, if a node corresponds to a consecutive range [l,r], its left child corresponds to the range [l,l+(r-l)/2] and its right child corresponds to [l+(l-r)/2+1,r].

For each segment tree node, we store _m_start_, _m_end_, and the sum of range [m\_start, m\_end]. Every leaf node's ```m_start == m_end```, and its value is the value of original element in the input array.
  
```cpp
class NumArray {
public:
  NumArray(vector<int> &nums) {
    m_root = BuildSegmentTree(nums,0,nums.size()-1);
  }

  void update(int i, int val) {
    Update(m_root,i,val);
  }

  int sumRange(int i, int j) {
    return SumRange(m_root,i,j);
  }
private:
  class SegmentTreeNode {
  public:
    SegmentTreeNode(int start, int end)
      : m_start(start),m_end(end),m_left(nullptr),m_right(nullptr),m_sum(0) {
    }
    int m_start, m_end;
    SegmentTreeNode *m_left, *m_right;
    int m_sum;
  };
  SegmentTreeNode* BuildSegmentTree(const vector<int> & input,int start, int end) {
    if (start>end) {
      return nullptr;
    } else {
      SegmentTreeNode* root = new SegmentTreeNode(start,end);
      if (start==end) {
        root->m_sum = input[start];
      } else {
        int mid = start + (end-start) / 2;
        root->m_left = BuildSegmentTree(input,start,mid);
        root->m_right = BuildSegmentTree(input,mid+1,end);
        root->m_sum = root->m_left->m_sum + root->m_right->m_sum;
      }
      return root;
    }

  }
  int SumRange(SegmentTreeNode* root, int start, int end) {
    if (root->m_start==start && root->m_end==end) {
      return root->m_sum;
    } else {
      int mid = root->m_start + (root->m_end-root->m_start) / 2;
      if (end<=mid) {
        return SumRange(root->m_left,start,end);
      } else if (start>=mid+1) {
        return SumRange(root->m_right,start,end);
      } else {
        return SumRange(root->m_left,start,mid) + SumRange(root->m_right,mid+1,end);
      }
    }
  }
  void Update(SegmentTreeNode* root,int pos,int val) {
    if (root->m_start==root->m_end) {
      root->m_sum = val;
    } else {
      int mid = root->m_start + (root->m_end-root->m_start) / 2;
      if (pos<=mid) {
        Update(root->m_left,pos,val);
      } else {
        Update(root->m_right,pos,val);
      }
      root->m_sum = root->m_left->m_sum + root->m_right->m_sum;
    }
  }
  SegmentTreeNode* m_root;
};
```


### Solution with binary indexed tree

For every binary indexed tree node, it's value includes it's owne value and the total sum of left children's value.

When updating value, we keep adding __last set bit__ to index in order to go upward to root node.

When getting range sum, we keep minus __last set bit__ to index in order to go upward to root node.



```cpp
class NumArray {
public:
    NumArray(vector<int> nums) : m_nums(nums.size(),0), m_tree(nums.size() + 1,0) {
        const std::size_t nums_size(nums.size());
        for (std::size_t i = 0;i < nums_size; ++ i) {
            update(i,nums[i]);
        }
    }
    
    void update(int i, int val) {
        int diff = val - m_nums[i];
        m_nums[i] = val;
        
        ++ i;
        while (i < m_tree.size()) {
            m_tree[i] += diff;
            int last_set_bit = i & (-i);
            i += last_set_bit;
        }
    }
    
    int GetSum(int i) {
        int sum(0);
        ++ i;
        while (i>0) {
            sum += m_tree[i];
            int last_set_bit = i & (-i);
            i -= last_set_bit;
        }
        return sum;
    }
    
    int sumRange(int i, int j) {
        return GetSum(j) - GetSum(i-1);
    }
    
private:
    std::vector<int> m_nums;
    std::vector<int> m_tree; // binary indexed tree
    
};
```

# Segment tree vs Fenwick tree(BIT)

Here are the things to keep in mind while deciding whether to use segment tree or binary indexed tree:

* Anything that can be done using a BIT can also be done using a segment tree : BIT stores cumulative quantities for certain intervals. Segment tree stores cumulative quantities for those intervals and more. In particular, if we are creating a data structure to deal with an array of size N=2^K, the BIT will have cumulative quantities for N intervals whereas the segment tree will have cumulative values for 2N-1 intervals
* There are things that a segment tree can do but a BIT cannot : A BIT essentially works with cumulative quantities. When the cumulative quantity for interval [i..j] is required, it is found as the difference between cumulative quantities for [1...j] and [1...i-1]. This works only because addition has an inverse operation. You cannot do this if the operation is non-invertible (such as max). On the other hand, every interval on a segment tree can be found as union of disjoint intervals and no inverse operation is required
* A BIT requires only half as much memory as a segment tree : In cases where you have masochistic memory constraints, you are almost stuck with using a BIT
* Though BIT and segment tree operations are both O(log(n)), the segment tree operations have a larger constant factor : This should not matter for most cases. But once again, if you have masochistic time constraints, you might want to switch from a segment tree to a BIT. The constant factor might become more of a problem if the BIT/Segment tree is multidimensional.
* With practice, coding either will be very fast : If you have coded a segment tree 100 times, you will get it very fast the next time you do it. So no need to worry about code being long.
