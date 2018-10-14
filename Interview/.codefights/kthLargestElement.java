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

    int kthLargestElement(int[] nums, int k) {
        return kthElement(nums, 0, nums.length - 1, k);
    }
}
