/**
 * Given an array of unique integers, each integer is strictly greater than 1.
 * 
 * We make a binary tree using these integers and each number may be used for
 * any number of times.
 * 
 * Each non-leaf node's value should be equal to the product of the values of
 * it's children.
 * 
 * How many binary trees can we make? Return the answer modulo 10 ** 9 + 7.
 * 
 * Example 1:
 * 
 * Input: A = [2, 4] Output: 3 Explanation: We can make these trees: [2], [4],
 * [4, 2, 2] Example 2:
 * 
 * Input: A = [2, 4, 5, 10] Output: 7 Explanation: We can make these trees: [2],
 * [4], [5], [10], [4, 2, 2], [10, 2, 5], [10, 5, 2].
 * 
 * 
 * Note:
 * 
 * 1 <= A.length <= 1000. 2 <= A[i] <= 10 ^ 9.
 */

// dp - n^2
class Solution {
    public int numFactoredBinaryTrees(int[] A) {
        int MOD = 1_000_000_007;
        int N = A.length;
        Arrays.sort(A);
        long[] dp = new long[N];
        Arrays.fill(dp, 1);

        Map<Integer, Integer> index = new HashMap();
        for (int i = 0; i < N; ++i)
            index.put(A[i], i);

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < i; ++j) {
                if (A[i] % A[j] == 0) { // A[j] is left child
                    int right = A[i] / A[j];
                    if (index.containsKey(right)) {
                        dp[i] = (dp[i] + dp[j] * dp[index.get(right)]) % MOD;
                    }
                }
            }

        long ans = 0;
        for (long x : dp)
            ans += x;
        return (int) (ans % MOD);
    }
}

// dp - n*sqrt(10^9)
class Solution {
    private static final int MODULO = (int) 1e9 + 7;

    public int numFactoredBinaryTrees(int[] nums) {
        Arrays.sort(nums);
        int[] dp = new int[nums.length];
        Map<Integer, Integer> numToPos = new HashMap<>();
        for (int pos = 0; pos < nums.length; ++pos)
            numToPos.put(nums[pos], pos);
        int ret = 0;
        for (int i = 0; i < nums.length; ++i) {
            for (int j = 2; j * j <= nums[i]; ++j)
                if ((nums[i] % j) == 0) {
                    int x = numToPos.getOrDefault(nums[i] / j, -1);
                    int y = numToPos.getOrDefault(j, -1);
                    if (x >= 0 && y >= 0) {
                        int childDp = (int) (((x == y ? 1L : 2L) * dp[x] * dp[y]) % MODULO);
                        dp[i] = (dp[i] + childDp) % MODULO;
                    }
                }
            dp[i] = (dp[i] + 1) % MODULO;
            ret = (ret + dp[i]) % MODULO;
        }
        return ret;
    }
}
