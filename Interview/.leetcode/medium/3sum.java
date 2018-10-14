/**
 * Given an array nums of n integers, are there elements a, b, c in nums such
 * that a + b + c = 0? Find all unique triplets in the array which gives the sum
 * of zero.
 * 
 * Note:
 * 
 * The solution set must not contain duplicate triplets.
 * 
 * Example:
 * 
 * Given array nums = [-1, 0, 1, 2, -1, -4],
 * 
 * A solution set is: [ [-1, 0, 1], [-1, -1, 2] ]
 */
public class Solution {
    public List<List<Integer>> threeSum(int[] a) {
        HashSet<List<Integer>> result = new HashSet<>();
        Arrays.sort(a);
        final int size = a.length;
        for (int prev = 0; prev < size - 2; ++prev) {
            int left = prev + 1;
            int right = size - 1;
            while (left < right) {
                final int currentSum = a[prev] + a[left] + a[right];
                if (0 == currentSum) {
                    result.add(Arrays.asList(a[prev], a[left], a[right]));
                    ++left;
                } else if (currentSum > 0) {
                    --right;
                } else {
                    ++left;
                }
            }
        }
        return new ArrayList<List<Integer>>(result);
    }
}
