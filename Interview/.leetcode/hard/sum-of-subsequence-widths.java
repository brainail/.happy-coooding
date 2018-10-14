/**
 * Given an array of integers A, consider all non-empty subsequences of A.
 * 
 * For any sequence S, let the width of S be the difference between the maximum
 * and minimum element of S.
 * 
 * Return the sum of the widths of all subsequences of A.
 * 
 * As the answer may be very large, return the answer modulo 10^9 + 7.
 * 
 * 
 * 
 * Example 1:
 * 
 * Input: [2,1,3] Output: 6 Explanation: Subsequences are [1], [2], [3], [2,1],
 * [2,3], [1,3], [2,1,3]. The corresponding widths are 0, 0, 0, 1, 1, 2, 2. The
 * sum of these widths is 6.
 * 
 * 
 * Note:
 * 
 * 1 <= A.length <= 20000 1 <= A[i] <= 20000
 */
class Solution {
    public int sumSubseqWidths(int[] A) {
        int MOD = (int) 1e9 + 7;
        int N = A.length;
        Arrays.sort(A);

        long[] pow2 = new long[N];
        pow2[0] = 1;
        for (int i = 1; i < N; ++i)
            pow2[i] = pow2[i - 1] * 2 % MOD;

        long ans = 0;
        for (int i = 0; i < N; ++i)
            ans = (ans + (pow2[i] - pow2[N - 1 - i]) * A[i]) % MOD;

        return (int) ans;
    }
}

/**
 * j>i ∑ ​ (2 j−i−1 )(A j ​ −A i ​ )
 * 
 * = \big( \sum\limits_{i = 0}^{n-2} \sum\limits_{j = i+1}^{n-1} (2^{j-i-1})
 * (A_j) \big) - \big( \sum\limits_{i = 0}^{n-2} \sum\limits_{j = i+1}^{n-1}
 * (2^{j-i-1}) (A_i) \big) =( i=0 ∑ n−2 ​
 * 
 * j=i+1 ∑ n−1 ​ (2 j−i−1 )(A j ​ ))−( i=0 ∑ n−2 ​
 * 
 * j=i+1 ∑ n−1 ​ (2 j−i−1 )(A i ​ ))
 * 
 * = \big( (2^0 A_1 + 2^1 A_2 + 2^2 A_3 + \cdots) + (2^0 A_2 + 2^1 A_3 + \cdots)
 * + (2^0 A_3 + 2^1 A_4 + \cdots) + \cdots \big) =((2 0 A 1 ​ +2 1 A 2 ​ +2 2 A
 * 3 ​ +⋯)+(2 0 A 2 ​ +2 1 A 3 ​ +⋯)+(2 0 A 3 ​ +2 1 A 4 ​ +⋯)+⋯)
 * 
 * - \big( \sum\limits_{i = 0}^{n-2} (2^0 + 2^1 + \cdots + 2^{N-i-2}) (A_i)
 * \big) −( i=0 ∑ n−2 ​ (2 0 +2 1 +⋯+2 N−i−2 )(A i ​ ))
 * 
 * = \big( \sum\limits_{j = 1}^{n-1} (2^j - 1) A_j \big) - \big( \sum\limits_{i
 * = 0}^{n-2} (2^{N-i-1} - 1) A_i \big) =( j=1 ∑ n−1 ​ (2 j −1)A j ​ )−( i=0 ∑
 * n−2 ​ (2 N−i−1 −1)A i ​ )
 * 
 * = \sum\limits_{i = 0}^{n-1} \big(((2^i - 1) A_i) - ((2^{N-i-1} - 1) A_i)\big)
 * = i=0 ∑ n−1 ​ (((2 i −1)A i ​ )−((2 N−i−1 −1)A i ​ ))
 * 
 * = \sum\limits_{i = 0}^{n-1} (2^i - 2^{N-i-1}) A_i = i=0 ∑ n−1 ​ (2 i −2 N−i−1
 * )A i ​
 */