public class Solution {
    public List<List<Integer>> fourSum(int[] nums, int target) {
        List<List<Integer>> reval = new ArrayList<List<Integer>>();
        Arrays.sort(nums);
        for (int i = 0; i < nums.length - 3; ++ i) {
            for (int j = i + 1; j < nums.length - 2; ++ j) {
                int low = j + 1, high = nums.length - 1;
                while (low < high) {
                    int cur_sum = nums[i] + nums[j] + nums[low] + nums[high];
                    if (cur_sum == target) {
                        reval.add(Arrays.asList(nums[i], nums[j], nums[low], nums[high]));
                        int cur_low = nums[low], cur_high = nums[high];
                        while (low < high && nums[low] == cur_low) ++ low;
                        while (low < high && nums[high] == cur_high) -- high;
                    } else if (cur_sum > target) {
                        -- high;
                    } else {
                        ++ low;
                    }
                }
                
                while (j + 1 < nums.length && nums[j + 1] == nums[j]) ++ j;
            }
            
            while (i + 1 < nums.length && nums[i + 1] == nums[i]) ++ i;
        }
        
        return reval;
    }
}
