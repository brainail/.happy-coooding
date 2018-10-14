/**
 * Given integers n and k, find the lexicographically k-th smallest integer in the range from 1 to n.

Note: 1 ≤ k ≤ n ≤ 109.

Example:

Input:
n: 13   k: 2

Output:
10

Explanation:
The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
 * 
 */
class Solution {
   public:
    int findKthNumber(int n, int k, int start = 0) {
        if (k > 0) {
            for (int i = (start == 0) ? 1 : 0; i <= 9; i++) {  // append 0-9 to the prefix
                int count = prefixCount(n, 10 * start + i);
                if (k <= count) return findKthNumber(n, k - 1, 10 * start + i);  // if k <= count, the answer is prefix..
                k -= count;                                                      // if the answer does not begin with the prefix, remove all the numbers begin with this prefix
            }
        }
        return start;
    }

    int prefixCount(int n, long long prefix) {
        long long base = 1;
        int count = 0;
        for (int digit = 1; digit <= 9; digit++) {
            long long min = prefix * base, max = prefix * base + (base - 1);
            if (n < min)
                break;
            else if (min <= n && n <= max) {
                count += (n - min + 1);
                break;
            } else
                count += base;
            base *= 10;
        }
        return count;
    }
};