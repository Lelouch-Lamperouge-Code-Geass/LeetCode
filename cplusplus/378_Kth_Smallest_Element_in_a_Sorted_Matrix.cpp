/***
 Using heap
 ***/

class Solution {
public:
  struct Item {
    Item(int val,std::size_t row,std::size_t col)
      : m_val(val),m_row(row), m_col(col) {}
    int m_val;
    std::size_t m_row;
    std::size_t m_col;
  };

  struct ItemCompare {
    bool operator()(const Item & left, const Item & right){
      return left.m_val>right.m_val;
    }
  };

  int kthSmallest(vector<vector<int>>& matrix, int k) {
    const std::size_t row_size(matrix.size()), col_size(matrix[0].size());
    std::priority_queue<Item,std::vector<Item>, ItemCompare > min_heap;
    for (std::size_t i=0;i<col_size;++i) {
      min_heap.push(Item(matrix[0][i],0,i));
    }

    for (int i=1;i<k;++i) {
      const std::size_t cur_row = min_heap.top().m_row,
        cur_col = min_heap.top().m_col;
      min_heap.pop();
      if (cur_row+1 == row_size) continue;
      min_heap.push(Item(matrix[cur_row+1][cur_col],cur_row+1,cur_col));
    }
    return min_heap.top().m_val;
  }
};

/***
这个题目还可以用二分查找来解决,思路是:

二维数组中左上角的肯定是最小值,右下角的肯定是最大值,我们取他们的平均值,
然后计算小于等于平均值的数字的个数,如果个数是小于题目要求的,那么说明要求的值是要大于平均值的,
此时我们更新start的值;如果个数是不小于题目要求的,那么说明要求的值就在start和mid之间,此时更新end的值。
The time complexity is O(n * log(n) * log(N)), where n is the number of rows and  N is the search space that ranges from the smallest element to the biggest element.
You can argue that int implies N = 2^32, so log(N) is constant. I guess this is where O(n * log(n)) comes from.
 ***/

class Solution {
public:
  int kthSmallest(vector<vector<int>>& matrix, int k) {
    std::size_t n = matrix.size();
    int low(matrix[0][0]), high(matrix[n-1][n-1]);
    while (low < high) {
      int mid = low + ((high - low) >> 1) ;
      int num = 0;
      for (std::size_t row=0; row < n; ++row) {
        std::size_t pos = std::upper_bound(matrix[row].begin(),
                                           matrix[row].end(), mid) - matrix[row].begin();
        num += pos;
      }

      if (num < k) {
        low = mid + 1;
      } else {
        high = mid;
      }
    }
    return low;
  }
};
