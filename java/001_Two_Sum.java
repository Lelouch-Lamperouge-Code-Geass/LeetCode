public class Solution {
    public int[] twoSum(int[] nums, int target) {
        int[] reval = new int[2];
        HashMap<Integer,Integer> mapper = new HashMap<Integer,Integer>();
        for (int i = 0; i < nums.length; ++ i) {
            if ( mapper.containsKey(target - nums[i]) ) {
                reval[0] = mapper.get(target-nums[i]);
                reval[1] = i;
                return reval;
            } else {
                mapper.put(nums[i], i);
            }
        }
        return reval;
    }
}
