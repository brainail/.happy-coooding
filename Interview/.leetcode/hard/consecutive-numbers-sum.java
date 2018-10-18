/**
 * Given a positive integer N, how many ways can we write it as a sum of
 * consecutive positive integers?
 * 
 * Example 1:
 * 
 * Input: 5 Output: 2 Explanation: 5 = 5 = 2 + 3 Example 2:
 * 
 * Input: 9 Output: 3 Explanation: 9 = 9 = 4 + 5 = 2 + 3 + 4 Example 3:
 * 
 * Input: 15 Output: 4 Explanation: 15 = 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4
 * + 5 Note: 1 <= N <= 10 ^ 9.
 */
class Solution {
    public int consecutiveNumbersSum(int n) {
        int kMax = (int) Math.sqrt(2 * n + 1);
        int ret = 0;
        for (int k = 1; k <= kMax; ++k) {
            int d = 2 * n - k * k + k;
            if (d <= 0)
                break;
            ret += (d % (2 * k)) == 0 ? 1 : 0;
        }
        return ret;
    }
}

/**
 * 2*N = k(2*x + k + 1)2∗N=k(2*x+k+1) with x >= 0, k >=0
 * 1x≥0,k≥1. Call kk the first factor, and 2*x + k + 12∗x+k+1 the second factor.
 * We are looking for ways to solve this equation without trying all 2*N2∗N
 * possibilities.
 * 
 * Now notice that the parity of kk and (2*x + k + 1)(2∗x+k+1) are different.
 * That is, if kk is even then the other quantity is odd, and vice versa. Also,
 * 2*x + k + 1 \geq k + 1 &gt; k 2∗x+k+1≥k+1>k, so the second factor must be
 * bigger.
 * 
 * Now write 2N = 2^\alpha * M2N=2 α ∗M where MM is odd. If we factor M = a *
 * bM=a∗b, then two candidate solutions are k = a, 2x+k+1 = b *
 * 2^\alphak=a,2x+k+1=b∗2 α , or k = a * 2^\alpha, 2x+k+1 = bk=a∗2 α ,2x+k+1=b.
 * However, only one of these solutions will have the second factor larger than
 * the first. (Because \alpha \geq 1α≥1, we are guaranteed that one factor is
 * strictly larger.)
 * 
 * Thus, the answer is the number of ways to factor the odd part of N.
 */
class Solution {
    public int consecutiveNumbersSum(int N) {
        while ((N & 1) == 0)
            N >>= 1;
        int ans = 1, d = 3;

        while (d * d <= N) {
            int e = 0;
            while (N % d == 0) {
                N /= d;
                e++;
            }
            ans *= e + 1;
            d += 2;
        }

        if (N > 1)
            ans <<= 1;
        return ans;
    }
}
