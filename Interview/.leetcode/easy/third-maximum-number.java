/**
 * Given a non-empty array of integers, return the third maximum number in this
 * array. If it does not exist, return the maximum number. The time complexity
 * must be in O(n).
 * 
 * Example 1: Input: [3, 2, 1]
 * 
 * Output: 1
 * 
 * Explanation: The third maximum is 1. Example 2: Input: [1, 2]
 * 
 * Output: 2
 * 
 * Explanation: The third maximum does not exist, so the maximum (2) is returned
 * instead. Example 3: Input: [2, 2, 3, 1]
 * 
 * Output: 1
 * 
 * Explanation: Note that the third maximum here means the third maximum
 * distinct number. Both numbers with value 2 are both considered as second
 * maximum.
 */
class Solution {
    public int thirdMax(int[] nums) {
        Integer[] max = new Integer[3];
        for (final int val : nums) {
            Integer x = val;
            if (x.equals(max[0]) || x.equals(max[1]) || x.equals(max[2])) {
                continue;
            }
            if (null == max[0] || x > max[0]) {
                max[2] = max[1];
                max[1] = max[0];
                max[0] = x;
            } else if (null == max[1] || x > max[1]) {
                max[2] = max[1];
                max[1] = x;
            } else if (null == max[2] || x > max[2]) {
                max[2] = x;
            }
        }
        return null == max[2] ? max[0] : max[2];
    }
}