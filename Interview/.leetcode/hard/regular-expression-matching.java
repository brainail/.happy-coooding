/**
 * Given an input string (s) and a pattern (p), implement regular expression
 * matching with support for '.' and '*'.
 * 
 * '.' Matches any single character. '*' Matches zero or more of the preceding
 * element. The matching should cover the entire input string (not partial).
 * 
 * Note:
 * 
 * s could be empty and contains only lowercase letters a-z. p could be empty
 * and contains only lowercase letters a-z, and characters like . or *. Example
 * 1:
 * 
 * Input: s = "aa" p = "a" Output: false Explanation: "a" does not match the
 * entire string "aa". Example 2:
 * 
 * Input: s = "aa" p = "a*" Output: true Explanation: '*' means zero or more of
 * the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes
 * "aa".
 */
class Solution {
    public boolean isMatch(String s, String p) {
        final ArrayList<String> pp = new ArrayList<>(p.length());
        for (int j = 0, size = p.length(); j < size; ++j) {
            if (p.charAt(j) == '*') {
                pp.add("*" + p.charAt(j - 1));
            } else if (j + 1 == size || p.charAt(j + 1) != '*') {
                pp.add("" + p.charAt(j));
            }
        }

        final int n = s.length();
        final int m = pp.size();
        final boolean[][] isMatch = new boolean[n + 1][m + 1];
        isMatch[0][0] = true; // empty matches empty
        for (int j = 1; j <= m; ++j)
            isMatch[0][j] = isMatch[0][j - 1] && '*' == pp.get(j - 1).charAt(0);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                p = pp.get(j - 1);
                if (s.charAt(i - 1) == p.charAt(0) || '.' == p.charAt(0)) {
                    isMatch[i][j] = isMatch[i - 1][j - 1];
                } else if ('*' == p.charAt(0)) {
                    isMatch[i][j] = isMatch[i][j - 1];
                    if (p.charAt(1) == s.charAt(i - 1) || p.charAt(1) == '.') {
                        isMatch[i][j] |= isMatch[i - 1][j - 1] || isMatch[i - 1][j];
                    }
                }
            }
        }
        return isMatch[n][m];
    }
}
