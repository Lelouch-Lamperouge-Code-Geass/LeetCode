/*
What's the real difference between this question and add coins to a target, whose result' order doesn't matter.

I find that this question is actually a tree. We only care about the combinations of those values 
to a specific target, so there could be many ways to get to that target, as any value can be the parent node.

Well, these two problems real difference is that:

In this problem, we add a value with no order, just enumerate; 
in coin problem, we can add in a specific order, from small to big, and always add to the end of the result array.

So we can see a slightly difference between the implementation of these two problems, 
but that small difference actually really matters.

         1 - 1 - 0
       /
     1 - 2 - 0
   ／ 
 1 － 2 - 1 - 0
   \
    3 - 0              ==> total ways = 7
 
     1 - 1 - 0
   /
 2 - 2 - 0
 
 3 - 1 - 0
 */
class Solution {
public:
  int combinationSum4(vector<int>& nums, int target) {
    std::vector<int> dp_mapper(target + 1, 0);
    dp_mapper[0] = 1;
    for (std::size_t i = 1; i < dp_mapper.size(); ++i) {
      for (std::size_t j = 0; j < nums.size(); ++j) {
        if (i >= nums[j]) {
          dp_mapper[i] += dp_mapper[i - nums[j]];
        }
      }
    }

    return dp_mapper[target];
  }
};
