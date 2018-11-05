/**
 * This time, we place our chess knight on any numbered key of a phone pad
 * (indicated above), and the knight makes N-1 hops. Each hop must be from one
 * key to another numbered key.
 * 
 * Each time it lands on a key (including the initial placement of the knight),
 * it presses the number of that key, pressing N digits total.
 * 
 * How many distinct numbers can you dial in this manner?
 * 
 * Since the answer may be large, output the answer modulo 10^9 + 7.
 * 
 * 
 * 
 * Example 1:
 * 
 * Input: 1 Output: 10 Example 2:
 * 
 * Input: 2 Output: 20 Example 3:
 * 
 * Input: 3 Output: 46
 * 
 * 
 * Note:
 * 
 * 1 <= N <= 5000
 */

class Solution {
    public int knightDialer(int N) {
        int MOD = 1_000_000_007;
        int[][] moves = new int[][] { { 4, 6 }, { 6, 8 }, { 7, 9 }, { 4, 8 }, { 3, 9, 0 }, {}, { 1, 7, 0 }, { 2, 6 },
                { 1, 3 }, { 2, 4 } };

        int[][] dp = new int[2][10];
        Arrays.fill(dp[0], 1);
        for (int hops = 0; hops < N - 1; ++hops) {
            Arrays.fill(dp[~hops & 1], 0);
            for (int node = 0; node < 10; ++node)
                for (int nei : moves[node]) {
                    dp[~hops & 1][nei] += dp[hops & 1][node];
                    dp[~hops & 1][nei] %= MOD;
                }
        }

        long ans = 0;
        for (int x : dp[~N & 1])
            ans += x;
        return (int) (ans % MOD);
    }
}

// #2 - more clear
class Solution {
    private static final int[][] dirs = { { 1, 2 }, { 2, 1 }, { 1, -2 }, { -2, 1 }, { -1, 2 }, { 2, -1 }, { -1, -2 },
            { -2, -1 } };
    private static final int MODULO = (int) 1e9 + 7;

    public int knightDialer(int N) {
        int[][][] dp = new int[2][4][3];
        int lay = 0;
        for (int i = 0; i < 4; ++i)
            Arrays.fill(dp[lay][i], 1);
        dp[lay][3][0] = dp[lay][3][2] = 0;
        for (int step = 1; step < N; ++step, lay ^= 1) {
            for (int i = 0; i < 4; ++i)
                Arrays.fill(dp[lay ^ 1][i], 0);
            dp[lay ^ 1][3][0] = dp[lay ^ 1][3][2] = 0;
            for (int x = 0; x < 4; ++x)
                for (int y = 0; y < 3; ++y) {
                    if (dp[lay][x][y] == 0)
                        continue;
                    for (int[] dir : dirs) {
                        int nx = x + dir[0], ny = y + dir[1];
                        if (nx < 0 || nx >= 4 || ny < 0 || ny >= 3)
                            continue;
                        if (nx == 3 && (ny == 0 || ny == 2))
                            continue;
                        dp[lay ^ 1][nx][ny] = (dp[lay ^ 1][nx][ny] + dp[lay][x][y]) % MODULO;
                    }
                }
        }
        int ret = 0;
        for (int x = 0; x < 4; ++x)
            for (int y = 0; y < 3; ++y)
                ret = (ret + dp[lay][x][y]) % MODULO;
        return ret;
    }
}
