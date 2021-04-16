#include <bits/stdc++.h>

class Solution {
   public:
    int mergeStones(vector<int>& stones, int K) {
        int n = stones.size();
        if ((n - 1) % (K - 1)) return -1;

        vector<int> sum(n + 1);
        for (int i = 0; i < n; i++) {
            sum[i + 1] = sum[i] + stones[i];
        }

        vector<vector<int> > dp(n, vector<int>(n));
        for (int len = K; len <= n; ++len) {
            for (int i = 0, j = len - 1; i + len <= n; ++i, ++j) {
                dp[i][j] = INT_MAX;
                // perform greedy left collapse to mach the whole number of collapse phases
                // because we don't need to check all variations like below
                // int allK = (len - 1) % (K - 1) == 0 ? (len - K) / (K - 1) : (len - 1) / (K - 1);
                // for (int m = i; m < j; ++m) {
                //    int l = k - i + 1, r = j - k;
                //    if ((l - 1) / (K - 1) /* lK */ + (r - 1) / (K - 1) /* rK */ == allK) {
                //        ...
                //    }
                // }
                for (int m = i; m < j; m += K - 1) {
                    dp[i][j] = min(dp[i][j], dp[i][m] + dp[m + 1][j]);
                }
                if ((j - i) % (K - 1) == 0) dp[i][j] += sum[j + 1] - sum[i];
            }
        }
        return dp[0][n - 1];
    }
};