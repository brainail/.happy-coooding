/**
 * Given two integers dividend and divisor, divide two integers without using
 * multiplication, division and mod operator.
 * 
 * Return the quotient after dividing dividend by divisor.
 * 
 * The integer division should truncate toward zero.
 * 
 * Example 1:
 * 
 * Input: dividend = 10, divisor = 3 Output: 3 Example 2:
 * 
 * Input: dividend = 7, divisor = -3 Output: -2 Note:
 * 
 * Both dividend and divisor will be 32-bit signed integers. The divisor will
 * never be 0. Assume we are dealing with an environment which could only store
 * integers within the 32-bit signed integer range: [−231, 231 − 1]. For the
 * purpose of this problem, assume that your function returns 231 − 1 when the
 * division result overflows.
 */
class Solution {
    public int divide(int dividend, int divisor) {
        long n = dividend, m = divisor;
        int sign = ((n < 0 ? 1 : 0) ^ (m < 0 ? 1 : 0)) > 0 ? -1 : 1;
        n = Math.abs(n);
        m = Math.abs(m);
        long q = 0;
        for (long t = 0, i = 31; i >= 0; i--)
            if (t + (m << i) <= n) {
                t += m << i;
                q |= 1L << i;
            }
        if (sign < 0)
            q = -q;
        return q > Integer.MAX_VALUE || q < Integer.MIN_VALUE ? Integer.MAX_VALUE : (int) q;
    }
}

/**
 * Basic idea: a/b = e^(ln(a))/e^(ln(b)) = e^(ln(a)-ln(b))

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend==0) return 0;
        if (divisor==0) return INT_MAX;
        long long res=double(exp(log(fabs(dividend))-log(fabs(divisor))));
        if ((dividend<0)^(divisor<0)) res=-res;
        if (res>INT_MAX) res=INT_MAX;
        return res;
    }
};
 */