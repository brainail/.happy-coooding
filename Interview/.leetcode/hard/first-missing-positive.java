/**
 * Given an unsorted integer array, find the smallest missing positive integer.
 * 
 * Example 1:
 * 
 * Input: [1,2,0] Output: 3 Example 2:
 * 
 * Input: [3,4,-1,1] Output: 2 Example 3:
 * 
 * Input: [7,8,9,11,12] Output: 1 Note:
 * 
 * Your algorithm should run in O(n) time and uses constant extra space.
 * 
 * 
 */
class Solution {
    public int firstMissingPositive(int[] nums) {
        final int n = nums.length;
        for (int i = 0; i < n; ++i) {
            while (nums[i] > 0 && nums[i] <= n && i + 1 != nums[i]) {
                int px = nums[nums[i] - 1];
                nums[nums[i] - 1] = nums[i];
                if (nums[i] == px)
                    break;
                nums[i] = px;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }
}
