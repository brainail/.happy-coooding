/**
 * Given an unsorted array of integers, find the number of longest increasing
 * subsequence.
 * 
 * Example 1: Input: [1,3,5,4,7] Output: 2 Explanation: The two longest
 * increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7]. Example 2: Input:
 * [2,2,2,2,2] Output: 5 Explanation: The length of longest continuous
 * increasing subsequence is 1, and there are 5 subsequences' length is 1, so
 * output 5. Note: Length of the given array will be not exceed 2000 and the
 * answer is guaranteed to be fit in 32-bit signed int.
 */
class Solution {
    public int findNumberOfLIS(int[] nums) {
        if (null == nums || nums.length == 0) return 0;
        int n = nums.length, len = 0;
        ArrayList<int[]>[] seq = new ArrayList[n];
        for (int i = 0; i < n; ++i) seq[i] = new ArrayList<>();
        for (int x : nums) {
            int lo = 0;
            int hi = len; // include end to allow choose next after last
            while (lo < hi) {
                int mi = lo + ((hi - lo) >> 1);
                if (x > seq[mi].get(seq[mi].size() - 1)[0]) lo = mi + 1; else hi = mi;
            }
            int count = 1;
            int index = lo - 1; // dp[len] += sum(dp[len - 1] where y < x)
            if (index >= 0) { // inner local search
                int llo = 0;
                int lhi = seq[index].size(); // include end to allow choose next after last
                while (llo < lhi) {
                    int lmi = llo + ((lhi - llo) >> 1);
                    if (seq[index].get(lmi)[0] >= x) llo = lmi + 1; else lhi = lmi;
                }
                count = seq[index].get(seq[index].size() - 1)[1];
                count -= llo == 0 ? 0 : seq[index].get(llo - 1)[1]; // exclude all bigger
            }
            count += seq[lo].isEmpty() ? 0 : seq[lo].get(seq[lo].size() - 1)[1]; // sum with previous
            seq[lo].add(new int[] { x, count });
            len = Math.max(len, lo + 1); // extend the maximum length if needed
        }
        return seq[len - 1].get(seq[len - 1].size() - 1)[1];
    }
}
