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
