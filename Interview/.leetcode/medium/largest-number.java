/**
 * Given a list of non negative integers, arrange them such that they form the
 * largest number.
 * 
 * Example 1:
 * 
 * Input: [10,2] Output: "210" Example 2:
 * 
 * Input: [3,30,34,5,9] Output: "9534330" Note: The result may be very large, so
 * you need to return a string instead of an integer.
 */
class Solution {
    public String largestNumber(int[] _nums) {
        Integer[] nums = new Integer[_nums.length];
        for (int i = 0; i < nums.length; ++i)
            nums[i] = _nums[i];
        Arrays.sort(nums, new Comparator<Integer>() {
            @Override
            public int compare(Integer a, Integer b) {
                String x = String.valueOf(a);
                String y = String.valueOf(b);
                return -(x + y).compareTo(y + x);
            }
        });
        StringBuilder result = new StringBuilder();
        for (int x : nums)
            result.append(x);
        int i = 0;
        while (i < result.length() && result.charAt(i) == '0')
            ++i;
        if (i == result.length())
            return "0";
        return result.substring(i);
    }
}
