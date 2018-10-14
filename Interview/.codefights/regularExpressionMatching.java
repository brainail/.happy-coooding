public class Solution {
    public int isMatch(final String str, final String rawPattern) {
        final int n = str.length();
        final int mRaw = rawPattern.length();
        final char [] wildcard = new char [mRaw + 1];    

        final StringBuilder sbPattern = new StringBuilder(mRaw);
        int q = 0;
        while (q < mRaw) {
            if (q + 1 < mRaw && '*' == rawPattern.charAt(q + 1)) {
                sbPattern.append('*');
                wildcard [sbPattern.length() - 1] = rawPattern.charAt(q);
                q += 2;
                continue;
            }

            sbPattern.append(rawPattern.charAt(q));
            ++ q;
        }

        final String pattern = sbPattern.toString();
        final int m = pattern.length();
        
        if (0 == m) {
            return 0 == n ? 1 : 0;
        }
        
        final boolean [][] match = new boolean [n + 1][m + 1];
        match [0][0] = true;
    
        for (int j = 1; j <= m; ++ j) {
            if ('*' == pattern.charAt(j - 1)) {
                match [0][j] = match [0][j - 1];
            }
        }
 
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= m; ++ j) {
                final char ch = pattern.charAt(j - 1);
                if ('*' == ch) {
                    match [i][j] |= match [i][j - 1];
                    if ('.' == wildcard [j - 1] || wildcard [j - 1] == str.charAt(i - 1)) {
                        match [i][j] |= match [i - 1][j];
                    }
                } else if ('.' == ch || str.charAt(i - 1) == ch) {
                    match [i][j] = match [i - 1][j - 1];
                }
            }
        }
 
        return match [n][m] ? 1 : 0;
    }
}


boolean regularExpressionMatching(String s, String p) {
    return new Solution().isMatch(s, p) == 1;
}
