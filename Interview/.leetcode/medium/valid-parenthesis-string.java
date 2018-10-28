/**
 * Given a string containing only three types of characters: '(', ')' and '*',
 * write a function to check whether this string is valid. We define the
 * validity of a string by these rules:
 * 
 * Any left parenthesis '(' must have a corresponding right parenthesis ')'. Any
 * right parenthesis ')' must have a corresponding left parenthesis '('. Left
 * parenthesis '(' must go before the corresponding right parenthesis ')'. '*'
 * could be treated as a single right parenthesis ')' or a single left
 * parenthesis '(' or an empty string. An empty string is also valid. Example 1:
 * Input: "()" Output: True Example 2: Input: "(*)" Output: True Example 3:
 * Input: "(*))" Output: True Note: The string size will be in the range [1,
 * 100].
 */

// Greedy (linear)
class Solution {
    public boolean checkValidString(String s) {
        int lo = 0, hi = 0;
        for (char c : s.toCharArray()) {
            lo += c == '(' ? 1 : -1;
            hi += c != ')' ? 1 : -1;
            if (hi < 0)
                break;
            lo = Math.max(lo, 0);
        }
        return lo == 0;
    }
}

// Dp (n^2)
class Solution {
    public boolean checkValidString(String s) {
        int n = s.length();
        boolean[][] dp = new boolean[2][n + 1];
        int lev, i;
        dp[0][0] = true;
        for (i = 0, lev = 0; i < n; lev ^= 1, ++i) {
            Arrays.fill(dp[lev ^ 1], false);
            for (int diff = 0; diff < n; ++diff)
                if (dp[lev][diff]) {
                    if (s.charAt(i) == '(' || s.charAt(i) == '*')
                        dp[lev ^ 1][diff + 1] = true;
                    if (s.charAt(i) == ')' || s.charAt(i) == '*')
                        if (diff > 0)
                            dp[lev ^ 1][diff - 1] = true;
                    if (s.charAt(i) == '*')
                        dp[lev ^ 1][diff] = true;
                }
        }
        return dp[lev][0];
    }
}
