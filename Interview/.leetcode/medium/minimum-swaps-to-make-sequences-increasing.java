/**
 * We have two integer sequences A and B of the same non-zero length.
 * 
 * We are allowed to swap elements A[i] and B[i]. Note that both elements are in
 * the same index position in their respective sequences.
 * 
 * At the end of some number of swaps, A and B are both strictly increasing. (A
 * sequence is strictly increasing if and only if A[0] < A[1] < A[2] < ... <
 * A[A.length - 1].)
 * 
 * Given A and B, return the minimum number of swaps to make both sequences
 * strictly increasing. It is guaranteed that the given input always makes it
 * possible.
 * 
 * Example: Input: A = [1,3,5,4], B = [1,2,3,7] Output: 1 Explanation: Swap A[3]
 * and B[3]. Then the sequences are: A = [1, 3, 5, 7] and B = [1, 2, 3, 4] which
 * are both strictly increasing. Note:
 * 
 * A, B are arrays with the same length, and that length will be in the range
 * [1, 1000]. A[i], B[i] are integer values in the range [0, 2000].
 */
class Solution {
    public int minSwap(int[] A, int[] B) {
        int n = A.length;
        if (n == 0)
            return 0;
        int[][] swaps = new int[n][2]; // could be O(const) space, but keep for understanding
        for (int[] arr : swaps)
            Arrays.fill(arr, Integer.MAX_VALUE);
        swaps[0][0] = 0;
        swaps[0][1] = 1;
        for (int i = 1; i < n; ++i) {
            for (int order = 0; order < 2; ++order) {
                if (swaps[i - 1][order] == Integer.MAX_VALUE)
                    continue;
                int a = order == 0 ? A[i - 1] : B[i - 1];
                int b = order == 0 ? B[i - 1] : A[i - 1];
                for (int order2 = 0; order2 < 2; ++order2) {
                    int a2 = order2 == 0 ? A[i] : B[i];
                    int b2 = order2 == 0 ? B[i] : A[i];
                    if (a2 > a && b2 > b) {
                        swaps[i][order2] = Math.min(swaps[i][order2], swaps[i - 1][order] + order2);
                    }
                }
            }
        }
        return Math.min(swaps[n - 1][0], swaps[n - 1][1]);
    }
}
