// 1. dp
// 2. c(n,m) using linear formula

public class Solution {
    public int uniquePaths(int a, int b) {
        final int n = a + b - 2;
        final int k = Math.min(a - 1, b - 1);
        
        long result = 1;
        for (int i = 1; i <= k; ++ i) {
            result = (result * (n - i + 1)) / i;
        }
        return (int) result;
    }
}
