/**
 * Given a 2D binary matrix filled with 0's and 1's, find the largest 
 * square containing only 1's and return its area.

Example:

Input: 

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Output: 4
 */

public class Solution {
    public int maximalSquare(char[][] matrix) {
        int rows = matrix.length, cols = rows > 0 ? matrix[0].length : 0;
        int[][] dp = new int[rows + 1][cols + 1];
        int maxsqlen = 0;
        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                if (matrix[i - 1][j - 1] == '1') {
                    dp[i][j] = Math.min(
                        Math.min(dp[i][j - 1], dp[i - 1][j]), 
                        dp[i - 1][j - 1]) + 1; // we can use layers here
                    maxsqlen = Math.max(maxsqlen, dp[i][j]);
                }
            }
        }
        return maxsqlen * maxsqlen;
    }
}

// #2 - stack (n^2)
class Solution {
    public int maximalSquare(char[][] matrix) {
        if (matrix.length == 0 || matrix[0].length == 0)
            return 0;
        int n = matrix.length;
        int m = matrix[0].length;
        int[] heights = new int[m + 1];
        Deque<Integer> columns = new ArrayDeque<Integer>();
        int bestSquare = 0;
        for (int i = 0; i < n; ++i) {
            columns.clear();
            for (int j = 0; j <= m; ++j) {
                heights[j] = j < m && matrix[i][j] == '0' ? 0 : heights[j] + 1;
                int curHeight = j < m ? heights[j] : -1; // -1 to push everything out
                while (!columns.isEmpty() && curHeight < heights[columns.peek()]) {
                    int height = heights[columns.pop()];
                    int width = j - (columns.isEmpty() ? -1 : columns.peek()) - 1;
                    int side = Math.min(height, width);
                    bestSquare = Math.max(bestSquare, side * side);
                }
                columns.push(j);
            }
        }
        return bestSquare;
    }
}
