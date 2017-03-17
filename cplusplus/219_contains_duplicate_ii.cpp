class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> found;
        for(int i=0;i<nums.size();++i){
            if(found.size() > k) found.erase(nums[i-k-1]);
            if(found.find(nums[i])!=found.end()) return true;
            found.insert(nums[i]);
        }
        return false;
    }
};
