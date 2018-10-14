/**
 * Given an array nums, we call (i, j) an important reverse pair if i < j and
 * nums[i] > 2*nums[j].
 * 
 * You need to return the number of important reverse pairs in the given array.
 * 
 * Example1:
 * 
 * Input: [1,3,2,3,1] Output: 2
 */
class Solution {
    int n;
    int[] inv;

    int sum(int r) {
        int result = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            result += inv[r];
        return result;
    }

    void inc(int i) {
        for (; i < n; i = (i | (i + 1)))
            ++inv[i];
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    public int reversePairs(int[] nums) {
        n = nums.length;
        inv = new int[n];
        Integer[] ids = new Integer[n];
        int[] greater = new int[n];
        int[] shortNums = new int[n];

        for (int i = 0; i < n; ++i)
            ids[i] = i;
        Arrays.sort(ids, (a, b) -> Integer.valueOf(nums[a]).compareTo(nums[b]));

        int zip = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0)
                zip += nums[ids[i]] != nums[ids[i - 1]] ? 1 : 0;
            shortNums[ids[i]] = zip;
        }

        int j = 0;
        for (int i = 0; i < n; ++i) {
            while (j < n && nums[ids[i]] * 2L >= (long) nums[ids[j]])
                ++j;
            greater[ids[i]] = j < n ? shortNums[ids[j]] : n;
        }

        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += sum(greater[i], n - 1);
            inc(shortNums[i]);
        }

        return result;
    }
}