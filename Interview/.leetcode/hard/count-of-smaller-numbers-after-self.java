/**
 * You are given an integer array nums and you have to return a new counts
 * array. The counts array has the property where counts[i] is the number of
 * smaller elements to the right of nums[i].
 * 
 * Example:
 * 
 * Input: [5,2,6,1] Output: [2,1,1,0] Explanation: To the right of 5 there are 2
 * smaller elements (2 and 1). To the right of 2 there is only 1 smaller element
 * (1). To the right of 6 there is 1 smaller element (1). To the right of 1
 * there is 0 smaller element.
 */
class Solution {
    public void countSmaller(int[] nums, int[] ind, List<Integer> count, int lo, int hi) {
        if (lo >= hi)
            return;
        int mi = (lo + hi) / 2;
        countSmaller(nums, ind, count, lo, mi);
        countSmaller(nums, ind, count, mi + 1, hi);

        int i = lo, j = mi + 1, kr = 0;
        List<Integer> mrNums = new ArrayList<>(hi - lo + 1);
        List<Integer> mrInd = new ArrayList<>(hi - lo + 1);
        while (i <= mi || j <= hi) {
            if (j > hi || (i <= mi && nums[i] <= nums[j])) {
                mrNums.add(nums[i]);
                mrInd.add(ind[i]);
                count.set(ind[i], count.get(ind[i]) + kr);
                ++i;
            } else {
                mrNums.add(nums[j]);
                mrInd.add(ind[j]);
                ++j;
                ++kr;
            }
        }
        for (i = lo; i <= hi; ++i) {
            nums[i] = mrNums.get(i - lo);
            ind[i] = mrInd.get(i - lo);
        }
    }

    public List<Integer> countSmaller(int[] nums) {
        List<Integer> count = new ArrayList<>(nums.length);
        int[] ind = new int[nums.length];
        for (int i = 0; i < nums.length; ++i) {
            count.add(0);
            ind[i] = i;
        }
        countSmaller(nums, ind, count, 0, nums.length - 1);
        return count;
    }
}
