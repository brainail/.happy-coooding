/**
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand.
 * 
 * (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
 * 
 * You are given a target value to search. If found in the array return its
 * index, otherwise return -1.
 * 
 * You may assume no duplicate exists in the array.
 * 
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * 
 * Example 1:
 * 
 * Input: nums = [4,5,6,7,0,1,2], target = 0 Output: 4 Example 2:
 * 
 * Input: nums = [4,5,6,7,0,1,2], target = 3 Output: -1
 */

class Solution {
    public int search(int[] nums, int target) {
        if (nums == null || nums.length == 0)
            return -1;
        int lo = 0, hi = nums.length - 1;
        while (hi - lo > 1) {
            int mi = lo + ((hi - lo) >> 1);
            if (nums[mi] == target) {
                return mi;
            } else if (nums[mi] > nums[lo]) {
                if (isNumIn(target, nums[lo], nums[mi])) {
                    hi = mi - 1;
                } else {
                    lo = mi + 1;
                }
            } else {
                if (isNumIn(target, nums[mi], nums[hi])) {
                    lo = mi + 1;
                } else {
                    hi = mi - 1;
                }
            }
        }
        return nums[lo] == target ? lo : (nums[hi] == target ? hi : -1);
    }

    private boolean isNumIn(int num, int lo, int hi) {
        return num >= lo && num <= hi;
    }
}




