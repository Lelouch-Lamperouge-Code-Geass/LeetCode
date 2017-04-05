public class Solution {
    void reverseArray(int[] nums, int from) {
        int begin = from, end = nums.length - 1;
        while (begin < end) {
            int temp = nums[end];
            nums[end] = nums[begin];
            nums[begin] = temp;
            
            ++ begin;
            -- end;
        }
    }
    
    void swap(int[] nums, int left, int right) {
        int temp = nums[right];
        nums[right] = nums[left];
        nums[left] = temp;
    }
    
    public void nextPermutation(int[] nums) {
        if (nums == null || nums.length == 0) return;
        int index = nums.length - 1;
        while (index >= 1 && nums[index-1] >= nums[index]) {
            -- index;
        }
        -- index;
        reverseArray(nums, index + 1);
        if (index == -1) return;
        
        final int value = nums[index];
        for (int i = index + 1; i < nums.length; ++i) {
            if (nums[i] > value) {
                swap(nums, index, i);
                break;
            }
        }
    }
}
