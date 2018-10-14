class Solution {
    public int cherryPickup(int[][] grid) {
        int N = grid.length;
        int[][] dp = new int[N][N];
        for (int[] row : dp)
            Arrays.fill(row, Integer.MIN_VALUE);
        dp[0][0] = grid[0][0];
        for (int t = 1; t <= 2 * N - 2; ++t) {
            int[][] dp2 = new int[N][N];
            for (int[] row : dp2)
                Arrays.fill(row, Integer.MIN_VALUE);
            for (int i = Math.max(0, t - (N - 1)); i <= Math.min(N - 1, t); ++i) {
                for (int j = Math.max(0, t - (N - 1)); j <= Math.min(N - 1, t); ++j) {
                    if (grid[i][t - i] == -1 || grid[j][t - j] == -1)
                        continue;
                    int val = grid[i][t - i];
                    if (i != j)
                        val += grid[j][t - j];
                    for (int pi = i - 1; pi <= i; ++pi)
                        for (int pj = j - 1; pj <= j; ++pj)
                            if (pi >= 0 && pj >= 0)
                                dp2[i][j] = Math.max(dp2[i][j], dp[pi][pj] + val);
                }
            }
            dp = dp2;
        }
        return Math.max(0, dp[N - 1][N - 1]);
    }
}

// All layers (more memo but easier)
/**
 * class Solution {
    int[][][] memo;
    int[][] grid;
    int N;
    public int cherryPickup(int[][] grid) {
        this.grid = grid;
        N = grid.length;
        memo = new int[N][N][N];
        for (int[][] layer: memo)
            for (int[] row: layer)
                Arrays.fill(row, Integer.MIN_VALUE);
        return Math.max(0, dp(0, 0, 0));
    }
    public int dp(int r1, int c1, int c2) {
        int r2 = r1 + c1 - c2;
        if (N == r1 || N == r2 || N == c1 || N == c2 ||
                grid[r1][c1] == -1 || grid[r2][c2] == -1) {
            return -999999;        
        } else if (r1 == N-1 && c1 == N-1) {
            return grid[r1][c1];
        } else if (memo[r1][c1][c2] != Integer.MIN_VALUE) {
            return memo[r1][c1][c2];
        } else {
            int ans = grid[r1][c1];
            if (c1 != c2) ans += grid[r2][c2];
            ans += Math.max(Math.max(dp(r1, c1+1, c2+1), dp(r1+1, c1, c2+1)),
                            Math.max(dp(r1, c1+1, c2), dp(r1+1, c1, c2)));
            memo[r1][c1][c2] = ans;
            return ans;
        }
    }
}
 */