class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        std::size_t num_size(nums.size());
        if (num_size==1) return nums[0];
        return std::max( max_rob(nums,0,num_size-2) , max_rob(nums,1,num_size-1) );
    }
private:
    int max_rob(const vector<int> & nums,size_t start, size_t end) {
        int pre2(0),pre1(0);
        for (size_t i=start;i<=end;++i) {
            int cur_max = std::max(pre2+nums[i],pre1);
            pre2 = pre1;
            pre1 = cur_max; 
        }
        return pre1;
    }
};
