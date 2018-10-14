/**
 * Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
 * 
 * Example 1:
 * 
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac" Output: true Example 2:
 * 
 * Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc" Output: false
 */
class Solution {
    public boolean isInterleave(String s1, String s2, String s3) {
        int n = s1.length(), m = s2.length(), k = s3.length();
        if (n + m != k)
            return false;
        boolean[][] dp = new boolean[n + 1][m + 1];
        dp[0][0] = true;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (!dp[i][j])
                    continue;
                if (i < n && s3.charAt(i + j) == s1.charAt(i))
                    dp[i + 1][j] = true;
                if (j < m && s3.charAt(i + j) == s2.charAt(j))
                    dp[i][j + 1] = true;
            }
        }
        return dp[n][m];
    }
}
