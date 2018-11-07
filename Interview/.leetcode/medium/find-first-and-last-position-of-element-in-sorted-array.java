/**
 * Given an array of integers nums sorted in ascending order, find the starting
 * and ending position of a given target value.
 * 
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * 
 * If the target is not found in the array, return [-1, -1].
 * 
 * Example 1:
 * 
 * Input: nums = [5,7,7,8,8,10], target = 8 Output: [3,4] Example 2:
 * 
 * Input: nums = [5,7,7,8,8,10], target = 6 Output: [-1,-1]
 */

class Solution {
    public int[] searchRange(int[] nums, int target) {
        int[] ret = { -1, -1 };
        if (nums == null || nums.length == 0)
            return ret;
        // left
        int lo = 0;
        int hi = nums.length - 1;
        while (lo < hi) {
            int mi = lo + ((hi - lo) >> 1);
            if (nums[mi] < target)
                lo = mi + 1;
            else
                hi = mi;
        }
        ret[0] = nums[lo] == target ? lo : -1;
        // right
        lo = 0;
        hi = nums.length - 1;
        while (lo < hi) {
            int mi = lo + ((hi - lo + 1) >> 1);
            if (nums[mi] > target)
                hi = mi - 1;
            else
                lo = mi;
        }
        ret[1] = nums[lo] == target ? lo : -1;
        return ret;
    }
}
