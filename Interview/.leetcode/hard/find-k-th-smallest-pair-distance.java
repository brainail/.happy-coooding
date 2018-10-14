/**
 * Given an integer array, return the k-th smallest distance among all the
 * pairs. The distance of a pair (A, B) is defined as the absolute difference
 * between A and B.
 * 
 * Example 1: Input: nums = [1,3,1] k = 1 Output: 0 Explanation: Here are all
 * the pairs: (1,3) -> 2 (1,1) -> 0 (3,1) -> 2 Then the 1st smallest distance
 * pair is (1,1), and its distance is 0. Note: 2 <= len(nums) <= 10000. 0 <=
 * nums[i] < 1000000. 1 <= k <= len(nums) * (len(nums) - 1) / 2.
 */
class Solution {
    public int smallestDistancePair(int[] nums, int k) {
        Arrays.sort(nums);
        int n = nums.length, lo = 0, hi = nums[n - 1] - nums[0];
        while (lo < hi) {
            int diff = lo + ((hi - lo) >> 1);
            int curK = 0;
            for (int i = 0, j = 0; i < n; ++i) {
                while (j < n && nums[j] - nums[i] <= diff) ++j;
                curK += j - i - 1;
            }
            if (curK < k) lo = diff + 1;
            if (curK >= k) hi = diff;
        }
        return lo;
    }
}
