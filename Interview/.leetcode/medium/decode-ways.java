/**
 * A message containing letters from A-Z is being encoded to numbers using the
 * following mapping:
 * 
 * 'A' -> 1 'B' -> 2 ... 'Z' -> 26 Given a non-empty string containing only
 * digits, determine the total number of ways to decode it.
 * 
 * Example 1:
 * 
 * Input: "12" Output: 2 Explanation: It could be decoded as "AB" (1 2) or "L"
 * (12). Example 2:
 * 
 * Input: "226" Output: 3 Explanation: It could be decoded as "BZ" (2 26), "VF"
 * (22 6), or "BBF" (2 2 6).
 */
class Solution {
    public int numDecodings(String s) {
        int n = s.length();
        int[] dp = new int[n + 1];
        dp[0] = 1;
        for (int i = 0; i < n; ++i)
            if (dp[i] > 0) {
                if (s.charAt(i) != '0' && Character.isDigit(s.charAt(i))) {
                    dp[i + 1] += dp[i];
                    if (i + 1 < n && Character.isDigit(s.charAt(i + 1))) {
                        int x = (s.charAt(i) - '0') * 10 + (s.charAt(i + 1) - '0');
                        if (x <= 26)
                            dp[i + 2] += dp[i];
                    }
                }
            }
        return dp[n];
    }
}
