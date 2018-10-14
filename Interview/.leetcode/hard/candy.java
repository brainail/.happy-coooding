/**
 * There are N children standing in a line. Each child is assigned a rating
 * value.
 * 
 * You are giving candies to these children subjected to the following
 * requirements:
 * 
 * Each child must have at least one candy. Children with a higher rating get
 * more candies than their neighbors. What is the minimum candies you must give?
 * 
 * Example 1:
 * 
 * Input: [1,0,2] Output: 5 Explanation: You can allocate to the first, second
 * and third child with 2, 1, 2 candies respectively. Example 2:
 * 
 * Input: [1,2,2] Output: 4 Explanation: You can allocate to the first, second
 * and third child with 1, 2, 1 candies respectively. The third child gets 1
 * candy because it satisfies the above two conditions.
 */
class Solution {
    public int candy(int[] ratings) {
        if (ratings == null || ratings.length == 0) return 0;
        int start = 0, sum = 0, len = ratings.length;
        while (start < len) {
            if (start + 1 < len && ratings[start] == ratings[start + 1]) {
                ++sum;
                ++start;
                continue;
            }

            int left = 0, right = 0;
            while (start + 1 < len && ratings[start] < ratings[start + 1]) {
                ++start;
                ++left;
            }
            while (start + 1 < len && ratings[start] > ratings[start + 1]) {
                ++start;
                ++right;
            }

            if (left + right == 0) {
                ++sum;
                break;
            }
            sum += (Math.max(left, right) + 1 /* peak */) 
                    + ((1 + left) * left / 2)
                    + ((1 + right) * right / 2 - 1 /* exclude last */);
        }
        return sum;
    }
}
