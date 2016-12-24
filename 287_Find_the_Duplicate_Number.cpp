class Solution {
public:
  // If we graph the array out,treated it as a graph representation,
  // then the duplciate value should have indegree >=2
  // since there are at least two values point to it.Since there is only one
  // duplicate number, very other node's indegree is 1. Therefore, the duplicate value
  // is the entry point. Notice that index=0 is a special case.
  int findDuplicate(vector<int>& nums) {
    // The keypoint is to ensure fast travels twice the distance then slow.
    // If we set slow=0 here, it won't work.
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


class Solution {
public:
  int findDuplicate(vector<int>& nums) {
    int slow(0),fast(0);
    while(true) {
      slow = nums[slow];
      fast = nums[nums[fast]];
      if (slow==fast) break;
    }
    slow = 0;
    while (fast!=slow) {
      slow = nums[slow];
      fast = nums[fast];
    }
    return slow;
  }
};
