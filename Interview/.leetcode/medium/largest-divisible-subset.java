/**
 * Given a set of distinct positive integers, find the largest subset such that
 * every pair (Si, Sj) of elements in this subset satisfies:
 * 
 * Si % Sj = 0 or Sj % Si = 0.
 * 
 * If there are multiple solutions, return any subset is fine.
 * 
 * Example 1:
 * 
 * Input: [1,2,3] Output: [1,2] (of course, [1,3] will also be ok) Example 2:
 * 
 * Input: [1,2,4,8] Output: [1,2,4,8]
 */
class Solution {
    public List<Integer> largestDivisibleSubset(int[] nums) {
        Arrays.sort(nums);
        int n = nums.length;
        int[] count = new int[n];
        int[] prev = new int[n];
        int retCount = 0, retIndex = -1;
        Arrays.fill(prev, -1);
        for (int i = 0; i < n; ++i) {
            count[i] = 1; // self
            for (int j = 0; j < i; ++j) {
                if ((nums[i] % nums[j]) == 0 && count[j] + 1 > count[i]) {
                    count[i] = count[j] + 1;
                    prev[i] = j;
                }
            }
            if (count[i] > retCount) {
                retCount = count[i];
                retIndex = i;
            }
        }
        List<Integer> retSub = new ArrayList<>();
        while (retIndex >= 0) {
            retSub.add(nums[retIndex]);
            retIndex = prev[retIndex];
        }
        Collections.reverse(retSub);
        return retSub;
    }
}