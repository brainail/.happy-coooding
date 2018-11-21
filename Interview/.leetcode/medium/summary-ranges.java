/**
 * Given a sorted integer array without duplicates, return the summary of its
 * ranges.
 * 
 * Example 1:
 * 
 * Input: [0,1,2,4,5,7] Output: ["0->2","4->5","7"] Explanation: 0,1,2 form a
 * continuous range; 4,5 form a continuous range. Example 2:
 * 
 * Input: [0,2,3,4,6,8,9] Output: ["0","2->4","6","8->9"] Explanation: 2,3,4
 * form a continuous range; 8,9 form a continuous range.
 */
class Solution {
    public List<String> summaryRanges(int[] nums) {
        int n = nums.length, j;
        List<String> ret = new ArrayList<>();
        for (int i = 0; i < n;) {
            for (j = i + 1; j < n && nums[j - 1] + 1 == nums[j]; ++j)
                ;
            if (j - i > 1)
                ret.add(String.valueOf(nums[i]) + "->" + String.valueOf(nums[j - 1]));
            if (j - i == 1)
                ret.add(String.valueOf(nums[i]));
            i = j;
        }
        return ret;
    }
}