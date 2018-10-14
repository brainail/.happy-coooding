/**
 * Find the smallest prime palindrome greater than or equal to N.
 * 
 * Recall that a number is prime if it's only divisors are 1 and itself, and it
 * is greater than 1.
 * 
 * For example, 2,3,5,7,11 and 13 are primes.
 * 
 * Recall that a number is a palindrome if it reads the same from left to right
 * as it does from right to left.
 * 
 * For example, 12321 is a palindrome.
 * 
 * 
 * 
 * Example 1:
 * 
 * Input: 6 Output: 7 Example 2:
 * 
 * Input: 8 Output: 11 Example 3:
 * 
 * Input: 13 Output: 101
 * 
 * 
 * Note:
 * 
 * 1 <= N <= 10^8 The answer is guaranteed to exist and be less than 2 * 10^8.
 */
class Solution {
    List<Integer> primes = new ArrayList<>();
    boolean[] isPrime = new boolean[15000];
    StringBuilder s = new StringBuilder();

    private void initPrimes() {
        primes.clear();
        Arrays.fill(isPrime, true);
        for (int i = 2, size = isPrime.length; i < size; ++i) {
            if (!isPrime[i])
                continue;
            else
                primes.add(i);
            for (int j = i * i; j < size; j += i)
                isPrime[j] = false;
        }
    }

    private int findFirstPprime(int n, int odd) {
        s.setLength(0);
        s.append(n);
        int len = s.length(), m = 0;
        int prefix = (int) Math.pow(10, (len - 1) / 2);
        for (int p = prefix; p < 20000; ++p) {
            s.setLength(0);
            s.append(p);
            if ((int) (s.charAt(0) - '0') % 2 == 0) {
                s.setCharAt(0, (char) (s.charAt(0) + 1));
                p = Integer.valueOf(s.toString());
            }
            len = s.length();
            for (int i = len - 1 - odd; i >= 0; --i)
                s.append(s.charAt(i));
            m = Integer.valueOf(s.toString());
            if (m < n || 1 == m)
                continue;
            boolean isOk = true;
            for (int i = 0, size = primes.size(); i < size; ++i) {
                if (primes.get(i) >= m)
                    break;
                if ((m % primes.get(i)) == 0) {
                    isOk = false;
                    break;
                }
            }
            if (isOk)
                return m;
        }
        return Integer.MAX_VALUE;
    }

    public int primePalindrome(int n) {
        if (n <= 2)
            return 2;
        initPrimes();
        return Math.min(findFirstPprime(n, 0), findFirstPprime(n, 1));
    }
}
