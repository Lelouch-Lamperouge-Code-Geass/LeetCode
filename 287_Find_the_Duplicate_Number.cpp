class Solution {
public:
  // If we graph the array out,treated it as a graph representation,
  // then the duplciate value should have indegree >=2
  // since there are at least two values point to it.Since there is only one
  // duplicate number, very other node's indegree is 1. Therefore, the duplicate value
  // is the entry point. Notice that index=0 is a special case.
  int findDuplicate(vector<int>& nums) {
    //The entry point has to be nums[0],
    // since nums[0] is the only element that should not equal to its index.
    // num[0] != 0. If you end up choose num[i] = i, then that's an infinite loop.
    int slow(nums[0]),fast(nums[nums[0]]);
    while(slow!=fast){
      slow = nums[slow];
      fast = nums[nums[fast]];
    }
    // now slow == fast
    slow = 0;
    while(slow!=fast){
      slow = nums[slow];
      fast = nums[fast];
    }
    // now slow and fast meets at the duplicate
    return slow;
  }
};
