/**
 * Given a string s, partition s such that every substring of the partition is a
 * palindrome.
 * 
 * Return the minimum cuts needed for a palindrome partitioning of s.
 * 
 * Example:
 * 
 * Input: "aab" Output: 1 Explanation: The palindrome partitioning ["aa","b"]
 * could be produced using 1 cut.
 */
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<int> cut(n+1, 0);  // number of cuts for the first k characters
        for (int i = 0; i <= n; i++) cut[i] = i-1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; i-j >= 0 && i+j < n && s[i-j]==s[i+j] ; j++) // odd length palindrome
                cut[i+j+1] = min(cut[i+j+1],1+cut[i-j]);

            for (int j = 1; i-j+1 >= 0 && i+j < n && s[i-j+1] == s[i+j]; j++) // even length palindrome
                cut[i+j+1] = min(cut[i+j+1],1+cut[i-j+1]);
        }
        return cut[n];
    }
};

class Solution {
    private static final int INF = (int) 1e9;

    int[] d1, d2;

    public void calcPalindromesSlow(char[] s, int n) {
        for (int i = 0; i < n; ++i) {
            d1[i] = 1;
            while (i - d1[i] >= 0 && i + d1[i] < n && s[i - d1[i]] == s[i + d1[i]]) ++d1[i];
            d2[i] = 0;
            while (i - d2[i] - 1 >= 0 && i + d2[i] < n && s[i - d2[i] - 1] == s[i + d2[i]]) ++d2[i];
        }
    }

    public int minCut(String s) {
        int n = s.length();
        d1 = new int[n];
        d2 = new int[n];
        calcPalindromesSlow(s.toCharArray(), n);
        int[] dp = new int[n + 1];
        Arrays.fill(dp, INF);
        dp[0] = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i; j < n; ++j) {
                int len = (j - i + 1) / 2;
                int[] d = (j - i + 1) % 2 == 1 ? d1 : d2;
                if (d[i + len] >= len + (j - i + 1) % 2) dp[j + 1] = Math.min(dp[j + 1], dp[i] + 1);
            }
        return dp[n] - 1;
    }
}


