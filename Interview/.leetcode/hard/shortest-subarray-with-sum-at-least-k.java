/**
 * Return the length of the shortest, non-empty, contiguous subarray of A with
 * sum at least K.
 * 
 * Example 1:
 * 
 * Input: A = [1], K = 1 Output: 1 Example 2:
 * 
 * Input: A = [1,2], K = 4 Output: -1 Example 3:
 * 
 * Input: A = [2,-1,2], K = 3 Output: 3
 */
class Solution {
    public int shortestSubarray(int[] A, int K) {
        int N = A.length;
        long[] P = new long[N + 1];
        for (int i = 0; i < N; ++i)
            P[i + 1] = P[i] + (long) A[i];

        int ans = N + 1;
        LinkedList<Integer> monoq = new LinkedList<>();

        for (int y = 0; y < P.length; ++y) {
            while (!monoq.isEmpty() && P[y] <= P[monoq.getLast()])
                monoq.removeLast();
            while (!monoq.isEmpty() && P[y] >= P[monoq.getFirst()] + K)
                ans = Math.min(ans, y - monoq.removeFirst());
            monoq.addLast(y);
        }

        return ans < N + 1 ? ans : -1;
    }
}