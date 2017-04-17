public class Solution {
    public int[] searchRange(int[] nums, int target) {
        int[] reval = new int[]{-1,-1};

        int low = 0, high = nums.length - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        if (high + 1 >= nums.length || nums[high + 1] != target) return reval;

        reval[0] = high + 1;
        high = nums.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        reval[1] = low - 1;

        return reval;
    }
}
