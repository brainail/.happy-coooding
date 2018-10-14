/**
 * Given an integer array nums, find the sum of the elements between indices i
 * and j (i ≤ j), inclusive.
 * 
 * The update(i, val) function modifies nums by updating the element at index i
 * to val.
 * 
 * Example:
 * 
 * Given nums = [1, 3, 5]
 * 
 * sumRange(0, 2) -> 9 update(1, 2) sumRange(0, 2) -> 8 Note:
 * 
 * The array is only modifiable by the update function. You may assume the
 * number of calls to update and sumRange function is distributed evenly.
 */
class NumArray {
    int[] arr;
    int n;

    public NumArray(int[] nums) {
        n = nums.length;StringBuilder
        arr = new int[n];
        for (int i = 0; i < n; ++i) {
            update(i, nums[i]);
        }
    }

    public void update(int i, int val) {
        int curVal = sumRange(i, i);
        inc(i, val - curVal);
    }

    public int sumRange(int i, int j) {
        return sum(j) - sum(i - 1);
    }

    private int sum(int index) {
        int res = 0;
        for (int j = index; j >= 0; j = (j & (j + 1)) - 1) {
            res += arr[j];
        }
        return res;
    }

    private void inc(int index, int val) {
        for (int j = index; j < n; j = j | (j + 1)) {
            arr[j] += val;
        }
    }
}
