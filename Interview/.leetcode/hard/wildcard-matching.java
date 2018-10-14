/**
 * Given an input string (s) and a pattern (p), implement wildcard pattern
 * matching with support for '?' and '*'.
 * 
 * '?' Matches any single character. '*' Matches any sequence of characters
 * (including the empty sequence). The matching should cover the entire input
 * string (not partial).
 * 
 * Note:
 * 
 * s could be empty and contains only lowercase letters a-z. p could be empty
 * and contains only lowercase letters a-z, and characters like ? or *. Example
 * 1:
 * 
 * Input: s = "aa" p = "a" Output: false Explanation: "a" does not match the
 * entire string "aa".
 */
class Solution {
    public boolean isMatch(String s, String p) {
        final int n = s.length();
        final int m = p.length();
        final boolean[][] isMatch = new boolean[n + 1][m + 1];
        isMatch[0][0] = true; // empty matches empty
        for (int j = 1; j <= m; ++j)
            isMatch[0][j] = isMatch[0][j - 1] && '*' == p.charAt(j - 1);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s.charAt(i - 1) == p.charAt(j - 1) || '?' == p.charAt(j - 1)) {
                    isMatch[i][j] = isMatch[i - 1][j - 1];
                } else if ('*' == p.charAt(j - 1)) {
                    isMatch[i][j] = isMatch[i - 1][j - 1] || isMatch[i][j - 1] || isMatch[i - 1][j];
                }
            }
        }
        return isMatch[n][m];
    }
}
