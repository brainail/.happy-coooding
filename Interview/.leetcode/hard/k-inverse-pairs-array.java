/**
 * Given two integers n and k, find how many different arrays consist of numbers
 * from 1 to n such that there are exactly k inverse pairs.
 * 
 * We define an inverse pair as following: For ith and jth element in the array,
 * if i < j and a[i] > a[j] then it's an inverse pair; Otherwise, it's not.
 * 
 * Since the answer may be very large, the answer should be modulo 109 + 7.
 * 
 * Example 1: Input: n = 3, k = 0 Output: 1 Explanation: Only the array [1,2,3]
 * which consists of numbers from 1 to 3 has exactly 0 inverse pair. Example 2:
 * Input: n = 3, k = 1 Output: 2 Explanation: The array [1,3,2] and [2,1,3] have
 * exactly 1 inverse pair. Note: The integer n is in the range [1, 1000] and k
 * is in the range [0, 1000].
 */
public class Solution {
    public int kInversePairs(int n, int k) {
        int[] dp = new int[k + 1];
        int M = 1000000007;
        for (int i = 1; i <= n; i++) {
            int[] temp = new int[k + 1];
            temp[0] = 1;
            for (int j = 1; j <= k; j++) {
                int val = (dp[j] + M - ((j - i) >= 0 ? dp[j - i] : 0)) % M;
                temp[j] = (temp[j - 1] + val) % M;
            }
            dp = temp;
        }
        return ((dp[k] + M - (k > 0 ? dp[k - 1] : 0)) % M);
    }
}

// approach memo (slow)
/**
 * if we know the number of inverse pairs (say x) in any arbitrary array b with
 * some n items, we can add a new element n+1 (max at this moment) to this array b 
 * at a position p
 * steps from the right, such that x + p = k to generate an array with a total
 * of k inverse pairs.
 */
public class Solution {
    Integer[][] memo = new Integer[1001][1001];

    public int kInversePairs(int n, int k) {
        if (n == 0)
            return 0;
        if (k == 0)
            return 1;
        if (memo[n][k] != null)
            return memo[n][k];
        int inv = 0;
        for (int i = 0; i <= Math.min(k, n - 1); i++)
            inv = (inv + kInversePairs(n - 1, k - i)) % 1000000007;
        memo[n][k] = inv;
        return inv;
    }
}

// approach dp (slow)
public class Solution {
    public int kInversePairs(int n, int k) {
        int[][] dp = new int[n + 1][k + 1];
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                if (j == 0)
                    dp[i][j] = 1;
                else {
                    for (int p = 0; p <= Math.min(j, i - 1); p++)
                        dp[i][j] = (dp[i][j] + dp[i - 1][j - p]) % 1000000007;
                }
            }
        }
        return dp[n][k];
    }
}

// approach dp (sums), fine
public class Solution {
    public int kInversePairs(int n, int k) {
        int[][] dp = new int[n + 1][k + 1];
        int M = 1000000007;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                if (j == 0)
                    dp[i][j] = 1;
                else {
                    int val = (dp[i - 1][j] + M - ((j - i) >= 0 ? dp[i - 1][j - i] : 0)) % M;
                    dp[i][j] = (dp[i][j - 1] + val) % M;
                }
            }
        }
        return ((dp[n][k] + M - (k > 0 ? dp[n][k - 1] : 0)) % M);
    }
}