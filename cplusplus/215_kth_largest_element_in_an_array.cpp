/* Solution 1*/
class Solution {
public:
  int findKthLargest(vector<int>& nums, int k) {
    int start(0), end(nums.size()-1);
    while (start<=end) {
      int i = RandomPartition(nums,start,end);
      if (i==k-1) {
        return nums[i];
      } else if (i>k-1) {
        end = i - 1;
      } else {
        start = i + 1;
      }
    }
    return -1;
  }
private:
  // Partition the vector and return an index.
  // [start,index-1] > nums[index] , [index+1,end] < nums[index]
  int RandomPartition(vector<int>& nums, int start, int end) {
    int random_index = start + rand() % (end-start+1);
    std::swap(nums[random_index],nums[end]);
    int k(start-1);
    const int pivot_val(nums[end]);
    for (int i=start;i<end;++i) {
      if (nums[i]>pivot_val) {
        std::swap(nums[++k],nums[i]);
      }
    }
    std::swap(nums[++k],nums[end]);
    return k;
  }
};

/* Solution 2 */
class Solution {
public:
  int findKthLargest(vector<int>& nums, int k) {
    std::nth_element(nums.begin(),nums.begin()+k-1,nums.end(),std::greater<int>());
    return nums[k-1];
  }
};
/* Solution 3 */
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(), nums.end());
        for (int i = 0; i < k - 1; i++)
            pq.pop(); 
        return pq.top();
    }

};
