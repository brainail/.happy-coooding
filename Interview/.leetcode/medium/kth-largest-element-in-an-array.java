/**
 * Find the kth largest element in an unsorted array. Note that it is the kth
 * largest element in the sorted order, not the kth distinct element.
 * 
 * Example 1:
 * 
 * Input: [3,2,1,5,6,4] and k = 2 Output: 5 Example 2:
 * 
 * Input: [3,2,3,1,2,4,5,5,6] and k = 4 Output: 4 Note: You may assume k is
 * always valid, 1 ≤ k ≤ array's length.
 */
class Solution {
    private static final Random RANDOM = new Random();

    void swap(final int[] nums, final int x, final int y) {
        final int buff = nums[x];
        nums[x] = nums[y];
        nums[y] = buff;
    }

    int kthElement(int[] nums, int lo, int hi, int k) {
        if (k > hi - lo + 1)
            return Integer.MIN_VALUE;
        final int pi = partition(nums, lo, hi, lo + RANDOM.nextInt(hi - lo + 1));
        if (pi - lo + 1 == k)
            return nums[pi];
        if (k < pi - lo + 1)
            return kthElement(nums, lo, pi - 1, k);
        return kthElement(nums, pi + 1, hi, k - (pi - lo + 1));
    }

    int partition(final int[] nums, final int lo, final int hi, final int tpi) {
        swap(nums, tpi, hi);
        int pi = lo;
        for (int i = lo; i < hi; ++i)
            if (nums[i] >= nums[hi])
                swap(nums, i, pi++);
        swap(nums, pi, hi);
        return pi;
    }

    int findKthLargest(int[] nums, int k) {
        return kthElement(nums, 0, nums.length - 1, k);
    }
}
