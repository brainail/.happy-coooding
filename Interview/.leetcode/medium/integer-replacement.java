/**
 * Given a positive integer n and you can do operations as follow:
 * 
 * If n is even, replace n with n/2. If n is odd, you can replace n with either
 * n + 1 or n - 1. What is the minimum number of replacements needed for n to
 * become 1?
 * 
 * Example 1:
 * 
 * Input: 8
 * 
 * Output: 3
 * 
 * Explanation: 8 -> 4 -> 2 -> 1 Example 2:
 * 
 * Input: 7
 * 
 * Output: 4
 * 
 * Explanation: 7 -> 8 -> 4 -> 2 -> 1 or 7 -> 6 -> 3 -> 2 -> 1
 */

class Solution {
    public int integerReplacement(int n) {
        int c = 0;
        while (n != 1) {
            System.out.println(n);
            if ((n & 1) == 0) {
                n >>>= 1; // >>> due to negative possibilities (MAX_VALUE + 1 -> -...)
            } else if (n == 3 || ((n >>> 1) & 1) == 0) {
                --n;
            } else {
                ++n;
            }
            ++c;
        }
        return c;
    }
}

// Integer.bitCount(n + 1) ~-> almost O(1)
class Solution {
    public int integerReplacement(int n) {
        int c = 0;
        while (n != 1) {
            if ((n & 1) == 0) {
                n >>>= 1;
            } else if (n == 3 || Integer.bitCount(n + 1) > Integer.bitCount(n - 1)) {
                --n;
            } else {
                ++n;
            }
            ++c;
        }
        return c;
    }
}

// memo
class Solution {
    public int integerReplacement(int n) {
        Map<Integer, Integer> memo = new HashMap<>();
        memo.put(1, 0);
        memo.put(Integer.MAX_VALUE, Integer.SIZE);
        return integerReplacement(n, memo);
    }

    private int integerReplacement(int n, Map<Integer, Integer> memo) {
        if (memo.containsKey(n)) return memo.get(n);
        int count = 0;
        if (n % 2 == 0) {
            int rightmost = n & (-n);
            int bitIdx = (int) (Math.log(rightmost) / Math.log(2));
            count = bitIdx + integerReplacement(n >> bitIdx, memo);
        } else {
            count = Math.min(integerReplacement(n + 1, memo), integerReplacement(n - 1, memo)) + 1;
        }
        memo.put(n, count);
        return count;
    }
}