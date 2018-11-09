/**
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand.
 * 
 * (i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).
 * 
 * You are given a target value to search. If found in the array return true,
 * otherwise return false.
 * 
 * Example 1:
 * 
 * Input: nums = [2,5,6,0,0,1,2], target = 0 Output: true Example 2:
 * 
 * Input: nums = [2,5,6,0,0,1,2], target = 3 Output: false Follow up:
 * 
 * This is a follow up problem to Search in Rotated Sorted Array, where nums may
 * contain duplicates. Would this affect the run-time complexity? How and why?
 */
class Solution {
    public boolean search(int[] nums, int target) {
        if (nums == null || nums.length == 0)
            return false;
        int lo = 0, hi = nums.length - 1;
        while (hi - lo > 1) {
            int mi = lo + ((hi - lo) >> 1);
            if (nums[mi] == target) {
                return true;
            } else if (nums[mi] > nums[lo]) {
                if (isNumIn(target, nums[lo], nums[mi])) {
                    hi = mi - 1;
                } else {
                    lo = mi + 1;
                }
            } else if (nums[mi] < nums[lo]) {
                if (isNumIn(target, nums[mi], nums[hi])) {
                    lo = mi + 1;
                } else {
                    hi = mi - 1;
                }
            } else {
                ++lo; // we can't do better because we have no extra information
            }
        }
        return nums[lo] == target ? true : (nums[hi] == target ? true : false);
    }

    private boolean isNumIn(int num, int lo, int hi) {
        return num >= lo && num <= hi;
    }
}
