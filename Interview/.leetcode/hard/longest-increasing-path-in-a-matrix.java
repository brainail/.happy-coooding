/**
 * Given an integer matrix, find the length of the longest increasing path.
 * 
 * From each cell, you can either move to four directions: left, right, up or
 * down. You may NOT move diagonally or move outside of the boundary (i.e.
 * wrap-around is not allowed).
 * 
 * Example 1:
 * 
 * Input: nums = [ [9,9,4], [6,6,8], [2,1,1] ] Output: 4 Explanation: The
 * longest increasing path is [1, 2, 6, 9]. Example 2:
 * 
 * Input: nums = [ [3,4,5], [3,2,6], [2,2,1] ] Output: 4 Explanation: The
 * longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
 */

// topological sort 
class Solution {
    private static final int[] vx = new int[] { +1, -1, 0, 0 };
    private static final int[] vy = new int[] { 0, 0, +1, -1 };

    boolean[][] used;
    int[][] dp;
    int[][] board;
    int n, m;
    List<int[]> cells;

    private boolean isInsideBoard(int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    }

    private void dfs(int x, int y) {
        if (used[x][y])
            return;
        used[x][y] = true;
        for (int i = 0; i < 4; ++i) {
            int nextX = x + vx[i], nextY = y + vy[i];
            if (isInsideBoard(nextX, nextY) && board[nextX][nextY] > board[x][y]) {
                dfs(nextX, nextY);
            }
        }
        cells.add(new int[] { x, y });
    }

    public int longestIncreasingPath(int[][] matrix) {
        board = matrix;
        n = matrix.length;
        if (n < 1)
            return 0;
        m = matrix[0].length;
        used = new boolean[n][m];
        cells = new ArrayList<>(n * m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                dfs(i, j);
            }
        }
        dp = new int[n][m];
        int result = 0;
        for (int cellIndex = 0; cellIndex < n * m; ++cellIndex) {
            int x = cells.get(cellIndex)[0], y = cells.get(cellIndex)[1];
            for (int i = 0; i < 4; ++i) {
                int nextX = x + vx[i], nextY = y + vy[i];
                if (isInsideBoard(nextX, nextY) && board[nextX][nextY] > board[x][y]) {
                    dp[x][y] = Math.max(dp[x][y], dp[nextX][nextY] + 1);
                    result = Math.max(result, dp[x][y]);
                }
            }
        }
        return result + 1;
    }
}

// memo
class Solution {
    public static final int[][] dirs = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

    public int longestIncreasingPath(int[][] matrix) {
        if (matrix.length == 0) return 0;
        int m = matrix.length, n = matrix[0].length;
        int[][] cache = new int[m][n];
        int max = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int len = dfs(matrix, i, j, m, n, cache);
                max = Math.max(max, len);
            }
        }
        return max;
    }

    public int dfs(int[][] matrix, int i, int j, int m, int n, int[][] cache) {
        if (cache[i][j] != 0) return cache[i][j];
        int max = 1;
        for (int[] dir : dirs) {
            int x = i + dir[0], y = j + dir[1];
            if (x < 0 || x >= m || y < 0 || y >= n || matrix[x][y] <= matrix[i][j]) continue;
            int len = 1 + dfs(matrix, x, y, m, n, cache);
            max = Math.max(max, len);
        }
        cache[i][j] = max;
        return max;
    }
}
