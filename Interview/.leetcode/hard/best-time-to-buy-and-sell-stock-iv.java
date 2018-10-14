/**
 * Say you have an array for which the ith element is the price of a given stock
 * on day i.
 * 
 * Design an algorithm to find the maximum profit. You may complete at most k
 * transactions.
 * 
 * Note: You may not engage in multiple transactions at the same time (ie, you
 * must sell the stock before you buy again).
 * 
 * Example 1:
 * 
 * Input: [2,4,1], k = 2 Output: 2 Explanation: Buy on day 1 (price = 2) and
 * sell on day 2 (price = 4), profit = 4-2 = 2. Example 2:
 * 
 * Input: [3,2,6,5,0,3], k = 2 Output: 7 Explanation: Buy on day 2 (price = 2)
 * and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price =
 * 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
 */
class Solution {
    private static final int SELL = 0;
    private static final int BUY = 1;
    private static final int INF = (int) 1e9;

    public int maxProfit(int k, int[] prices) {
        int n = prices.length;
        k = Math.min(k, n / 2);
        int[][][] dp = new int[2][k + 1][2];
        for (int[][] sub : dp)
            for (int[] cells : sub)
                Arrays.fill(cells, -INF);
        dp[0][0][0] = 0;
        int lev = 0;
        int result = 0;
        for (int i = 0; i <= n; ++i) {
            for (int t = 0; t <= k; ++t) {
                for (int op = 0; op < 2; ++op) {
                    if (op == SELL) result = Math.max(result, dp[lev][t][op]);
                    if (dp[lev][t][op] == -INF || i == n || t == k) continue;
                    dp[lev ^ 1][t][op] = Math.max(dp[lev ^ 1][t][op], dp[lev][t][op]); // skip the day
                    dp[lev ^ 1][t + (op == BUY ? 1 : 0)][op ^ 1] = Math.max(
                            dp[lev ^ 1][t + (op == BUY ? 1 : 0)][op ^ 1],
                            dp[lev][t][op] + (op == BUY ? prices[i] : -prices[i])); // perform op
                }
            }
            lev ^= 1;
        }
        return result;
    }
}
