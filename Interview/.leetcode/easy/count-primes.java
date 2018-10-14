/**
 * Count the number of prime numbers less than a non-negative number, n.
 * 
 * Example:
 * 
 * Input: 10 Output: 4 Explanation: There are 4 prime numbers less than 10, they
 * are 2, 3, 5, 7.
 * 
 */
class Solution {
    public int countPrimes(int n) {
        --n;
        boolean[] isComposite = new boolean[n + 1];
        int ret = 0;
        for (int i = 2; i <= n; ++i) {
            if (isComposite[i])
                continue;
            ++ret;
            if ((long) i * i > n)
                continue;
            for (int j = i * i; j <= n; j += i) {
                isComposite[j] = true;
            }
        }
        return ret;
    }
}
