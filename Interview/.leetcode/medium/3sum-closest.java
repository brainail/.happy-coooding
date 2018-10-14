/**
 * Given an array nums of n integers and an integer target, find three integers
 * in nums such that the sum is closest to target. Return the sum of the three
 * integers. You may assume that each input would have exactly one solution.
 * 
 * Example:
 * 
 * Given array nums = [-1, 2, 1, -4], and target = 1.
 * 
 * The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */
public class Solution {
    public int threeSumClosest(int[] a, int target) {
        Arrays.sort(a);
        int bestDiff = Integer.MAX_VALUE;
        final int size = a.length;
        for (int prev = 0; prev < size - 2; ++prev) {
            int left = prev + 1, right = size - 1;
            while (left < right) {
                final int currentSum = a[prev] + a[left] + a[right];
                final int diff = currentSum - target;
                if (Math.abs(diff) < Math.abs(bestDiff)) {
                    bestDiff = diff;
                }
                if (currentSum > target) {
                    --right;
                } else {
                    ++left;
                }
            }
        }
        return target + bestDiff;
    }
}
