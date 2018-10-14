/**
 * A positive integer is magical if it is divisible by either A or B.
 * 
 * Return the N-th magical number. Since the answer may be very large, return it
 * modulo 10^9 + 7.
 * 
 * 
 * 
 * Example 1:
 * 
 * Input: N = 1, A = 2, B = 3 Output: 2
 */
class Solution {
    public int nthMagicalNumber(int N, int A, int B) {
        final int L = A / gcd(A, B) * B;
        long lo = 0, hi = (long) 1e16;
        while (lo < hi) {
            final long mi = (hi + lo) >> 1L;
            if (mi / A + mi / B - mi / L < N) {
                lo = mi + 1;
            } else {
                hi = mi;
            }
        }

        return (int) (lo % ((int) 1e9 + 7));
    }

    public int gcd(int x, int y) {
        return 0 == x ? y : gcd(y % x, x);
    }
}