/**
 * We have a sorted set of digits D, a non-empty subset of
 * {'1','2','3','4','5','6','7','8','9'}. (Note that '0' is not included.)
 * 
 * Now, we write numbers using these digits, using each digit as many times as
 * we want. For example, if D = {'1','3','5'}, we may write numbers such as
 * '13', '551', '1351315'.
 * 
 * Return the number of positive integers that can be written (using the digits
 * of D) that are less than or equal to N.
 * 
 * 
 * 
 * Example 1:
 * 
 * Input: D = ["1","3","5","7"], N = 100 Output: 20 Explanation: The 20 numbers
 * that can be written are: 1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53,
 * 55, 57, 71, 73, 75, 77. Example 2:
 * 
 * Input: D = ["1","4","9"], N = 1000000000 Output: 29523 Explanation: We can
 * write 3 one digit numbers, 9 two digit numbers, 27 three digit numbers, 81
 * four digit numbers, 243 five digit numbers, 729 six digit numbers, 2187 seven
 * digit numbers, 6561 eight digit numbers, and 19683 nine digit numbers. In
 * total, this is 29523 integers that can be written using the digits of D.
 */
class Solution {
    public int atMostNGivenDigitSet(String[] D, int N) {
        int nd = D.length + 1;
        char[] digits = new char[nd];
        digits[0] = '0';
        for (int i = 1; i < nd; ++i) digits[i] = D[i - 1].charAt(0);
        char[] limit = String.valueOf(N).toCharArray();
        int nl = limit.length;
        int[][][] dp = new int[nl + 1][2][2];
        for (int[][] arr : dp)
            for (int[] arr2 : arr)
                Arrays.fill(arr2, 0);
        dp[0][0][0] = 1;
        for (int i = 0; i < nl; ++i)
            for (int t = 0; t < 2; ++t)
                for (int z = 0; z < 2; ++z) {
                    if (dp[i][t][z] == 0) continue;
                    for (int j = 0; j < nd; ++j) {
                        if ((digits[j] > limit[i] && t == 0) || (j == 0 && z != 0)) continue;
                        int nt = (t == 1 || digits[j] < limit[i]) ? 1 : 0, nz = (z == 1 || j > 0) ? 1 : 0;
                        dp[i + 1][nt][nz] += dp[i][t][z];
                    }
                }
        return dp[nl][0][1] + dp[nl][1][1];
    }
}
