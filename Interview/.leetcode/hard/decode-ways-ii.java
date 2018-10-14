/**
 * A message containing letters from A-Z is being encoded to numbers using the
 * following mapping way:
 * 
 * 'A' -> 1 'B' -> 2 ... 'Z' -> 26 Beyond that, now the encoded string can also
 * contain the character '*', which can be treated as one of the numbers from 1
 * to 9.
 * 
 * Given the encoded message containing digits and the character '*', return the
 * total number of ways to decode it.
 * 
 * Also, since the answer may be very large, you should return the output mod
 * 109 + 7.
 * 
 * Example 1: Input: "*" Output: 9 Explanation: The encoded message can be
 * decoded to the string: "A", "B", "C", "D", "E", "F", "G", "H", "I". Example
 * 2: Input: "1*" Output: 9 + 9 = 18 Note: The length of the input string will
 * fit in range [1, 105]. The input string will only contain the character '*'
 * and digits '0' - '9'.
 */
class Solution {
    public int numDecodings(String s) {
        int n = s.length();
        int MODULO = (int) 1e9 + 7;
        long[] dp = new long[n + 1];
        dp[0] = 1;
        for (int i = 0; i < n; ++i)
            if (dp[i] > 0 && s.charAt(i) != '0') {
                dp[i + 1] = (dp[i + 1] + dp[i] * (s.charAt(i) == '*' ? 9 : 1)) % MODULO;
                if (i + 1 >= n)
                    continue;
                for (int c = 1; c <= 1 + (s.charAt(i) == '*' ? 1 : 0); ++c) {
                    char ch = s.charAt(i) != '*' ? s.charAt(i) : (char) (c + '0');
                    if (s.charAt(i + 1) != '*') {
                        int x = (ch - '0') * 10 + (s.charAt(i + 1) - '0');
                        if (x <= 26)
                            dp[i + 2] = (dp[i + 2] + dp[i]) % MODULO;
                    } else if (ch <= '2') {
                        dp[i + 2] = (dp[i + 2] + dp[i] * (ch == '1' ? 9 : 6)) % MODULO;
                    }
                }
            }
        return (int) dp[n];
    }
}
