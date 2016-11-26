/* Solution 1*/
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int begin(0), end(nums.size()-1);
        while (begin<=end) {
            int i = partition(nums,begin,end);// number within [0,i] >= number within [i+1,nums.size()-1]
            if (k==i+1) return nums[i];
            else if (k>i+1) begin = i+1;
            else end = i - 1;
        }
        return -1;
    }
private:
    // choose a random number within range to partion that range.
    // Larger elements predecede smaller elements.
    // Return the index of the pivot number eventually.
    int partition(vector<int>& nums,int start, int end) {
        int random_index = start + rand() % (end-start+1);
        std::swap(nums[random_index],nums[end]);
        const int pivot = nums[end];
        int sb(start-1),se(start);
        while (se<end) {
            if(nums[se] > pivot) std::swap (nums[++sb],nums[se]);
            ++ se;
        }
        ++ sb;
        std::swap(nums[sb],nums[end]);
        return sb;
    }
};

/* Solution 2*/
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(), nums.end());
        for (int i = 0; i < k - 1; i++)
            pq.pop(); 
        return pq.top();
    }

};
