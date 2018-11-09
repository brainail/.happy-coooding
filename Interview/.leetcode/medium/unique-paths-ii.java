/**
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in
 * the diagram below).
 * 
 * The robot can only move either down or right at any point in time. The robot
 * is trying to reach the bottom-right corner of the grid (marked 'Finish' in
 * the diagram below).
 * 
 * Now consider if some obstacles are added to the grids. How many unique paths
 * would there be?
 * 
 * 
 * 
 * An obstacle and empty space is marked as 1 and 0 respectively in the grid.
 * 
 * Note: m and n will be at most 100.
 * 
 * Example 1:
 * 
 * Input: [ 
 * [0,0,0], 
 * [0,1,0], 
 * [0,0,0] ] Output: 2 Explanation: There is one
 * obstacle in the middle of the 3x3 grid above. There are two ways to reach the
 * bottom-right corner: 1. Right -> Right -> Down -> Down 2. Down -> Down ->
 * Right -> Right
 */

class Solution {
    public int uniquePathsWithObstacles(int[][] board) {
        if (null == board || board.length == 0 || board[0].length == 0)
            return 0;
        int n = board.length;
        int m = board[0].length;
        int[][] dp = new int[n][m];
        dp[0][0] = 1 - board[0][0];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (board[i][j] == 1)
                    continue;
                if (j > 0)
                    dp[i][j] += dp[i][j - 1];
                if (i > 0)
                    dp[i][j] += dp[i - 1][j];
            }
        return dp[n - 1][m - 1];
    }
}
