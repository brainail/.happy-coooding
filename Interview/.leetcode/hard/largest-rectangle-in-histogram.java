/**
 * Given n non-negative integers representing the histogram's bar height where
 * the width of each bar is 1, find the area of largest rectangle in the
 * histogram.
 * 
 * 
 * Above is a histogram where width of each bar is 1, given height =
 * [2,1,5,6,2,3].
 * 
 * 
 * 
 * 
 * The largest rectangle is shown in the shaded area, which has area = 10 unit.
 * 
 * 
 * 
 * Example:
 * 
 * Input: [2,1,5,6,2,3] Output: 10
 */
class Solution {
    public int largestRectangleArea(int[] heights) {
        Stack<Integer> stack = new Stack<>();
        int result = 0;
        for (int i = 0; i <= heights.length; ++i) {
            int curHeight = i == heights.length ? -1 : heights[i];
            while (!stack.isEmpty() && heights[stack.peek()] >= curHeight) {
                int pivotHeight = heights[stack.pop()];
                int left = stack.isEmpty() ? -1 : stack.peek();
                result = Math.max(result, (i - left - 1) * pivotHeight);
            }
            stack.push(i);
        }
        return result;
    }
}


