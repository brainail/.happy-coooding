/**
 * There is an m by n grid with a ball. 
 * Given the start coordinate (i,j) of the ball, you can move the ball to 
 * adjacent cell or cross the grid boundary in four directions (up, down, left, right). 
 * However, you can at most move N times. Find out the number of paths to move 
 * the ball out of grid boundary. The answer may be very large, return it after mod 10^9 + 7.
 * Example 1:
 * Input: m = 2, n = 2, N = 2, i = 0, j = 0
 * Output: 6
*/

// assume N ~= 2n (n = m) -> O(n^2)
using namespace std;
#include <vector>

class Solution {
   public:
    using LL = long long;
    int findPaths(int m, int n, int N, int i, int j) {
        if (n == 0 || m == 0) return 0;

        int mod = (int)1e9 + 7;
        LL C[52][52];
        C[0][0] = C[0][1] = 1;
        for (int a = 1; a <= N; a++) {
            C[a][0] = C[a][a] = 1;
            for (int b = 1; b < a; b++)
                C[a][b] = (C[a - 1][b] + C[a - 1][b - 1]) % mod;
        }

        vector<LL> H(N + 2, 0), V(N + 2, 0);
        vector<LL> HB(N + 2, 0), VB(N + 2, 0);
        LL dp[2][52];
        int t = 0;

        memset(dp, 0, sizeof dp);
        dp[t][i + 1] = 1;
        V[0] = 1;
        VB[0] = (i + 1 == 1) + (i + 1 == m);
        for (int s = 1; s <= N; s++) {
            t = !t;
            for (int a = 1; a <= m; a++) V[s] += dp[t][a] = (dp[!t][a - 1] + dp[!t][a + 1]) % mod;
            V[s] %= mod, VB[s] = (dp[t][1] + dp[t][m]) % mod;
        }
        memset(dp, 0, sizeof dp);
        dp[t][j + 1] = 1;
        H[0] = 1;
        HB[0] = (j + 1 == 1) + (j + 1 == n);
        for (int s = 1; s <= N; s++) {
            t = !t;
            for (int b = 1; b <= n; b++) H[s] += (dp[t][b] = (dp[!t][b - 1] + dp[!t][b + 1]) % mod);
            H[s] %= mod, HB[s] += (dp[t][1] + dp[t][n]) % mod;
        }

        LL count = 0;
        for (int s = 0; s < N; s++)
            for (int dx = 0; dx <= s; dx++) {
                // [go horizontally anyhow + go to vertical boundary (& vise versa)] * (combine hvh..v/vhh..v/... -> C(X,Y))
                LL t = ((H[dx] * VB[s - dx]) % mod + (HB[dx] * V[s - dx]) % mod) % mod;
                count = (count + (C[s][dx] * t) % mod) % mod;
            }
        return count;
    }
};

// O(n^3)
class Solution {
    public:
     int findPaths(int m, int n, int N, int i, int j) {
         long long dp[51][50][50] = {};
         for (auto Ni = 1; Ni <= N; ++Ni)
             for (auto mi = 0; mi < m; ++mi)
                 for (auto ni = 0; ni < n; ++ni)
                     dp[Ni][mi][ni] = ((mi == 0 ? 1 : dp[Ni - 1][mi - 1][ni]) + (mi == m - 1 ? 1 : dp[Ni - 1][mi + 1][ni]) + (ni == 0 ? 1 : dp[Ni - 1][mi][ni - 1]) + (ni == n - 1 ? 1 : dp[Ni - 1][mi][ni + 1])) % 1000000007;
         return dp[N][i][j];
     }
};