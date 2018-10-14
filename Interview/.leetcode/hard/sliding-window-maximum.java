/**
 * Given an array nums, there is a sliding window of size k which is 
 * moving from the very left of the array to the very right. You can only see the k 
 * numbers in the window. Each time the sliding window moves right by one position. 
 * Return the max sliding window.

Example:

Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7] 
Explanation: 

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
 */
class Solution {
    public int[] maxSlidingWindow(int[] nums, int k) {
        if (nums.length == 0)
            return new int[] {};
        LinkedList<Integer> window = new LinkedList<Integer>();
        int size = nums.length;
        int[] result = new int[size - k + 1];
        for (int i = 0; i < size; ++i) {
            while (!window.isEmpty() && window.getFirst() <= i - k)
                window.removeFirst();
            while (!window.isEmpty() && nums[i] >= nums[window.getLast()])
                window.removeLast();
            window.addLast(i);
            if (i - k + 1 >= 0)
                result[i - k + 1] = nums[window.getFirst()];
        }
        return result;
    }
}
