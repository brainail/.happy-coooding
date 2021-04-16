/**
 * We are given an array A of N lowercase letter strings, all of the same
 * length.
 * 
 * Now, we may choose any set of deletion indices, and for each string, we
 * delete all the characters in those indices.
 * 
 * For example, if we have an array A = ["abcdef","uvwxyz"] and deletion indices
 * {0, 2, 3}, then the final array after deletions is ["bef","vyz"].
 * 
 * Suppose we chose a set of deletion indices D such that after deletions, the
 * final array has its elements in lexicographic order (A[0] <= A[1] <= A[2] ...
 * <= A[A.length - 1]).
 * 
 * Return the minimum possible value of D.length.
 * 
 * 
 * 
 * Example 1:
 * 
 * Input: ["ca","bb","ac"] Output: 1 Explanation: After deleting the first
 * column, A = ["a", "b", "c"]. Now A is in lexicographic order (ie. A[0] <=
 * A[1] <= A[2]). We require at least 1 deletion since initially A was not in
 * lexicographic order, so the answer is 1.
 */

class Solution {
    public int minDeletionSize(String[] arr) {
        int deletion = 0;
        int n = arr.length;
        int m = arr[0].length();
        String[] upd = new String[n];
        Arrays.fill(upd, "");
        for (int j = 0; j < m; ++j) {
            boolean sorted = true;
            for (int i = 1; i < n; ++i) {
                String prev = upd[i - 1] + arr[i - 1].charAt(j);
                String curr = upd[i] + arr[i].charAt(j);
                if (prev.compareTo(curr) > 0) {
                    sorted = false;
                    break;
                }
            }
            deletion += sorted ? 0 : 1;
            if (sorted) {
                for (int i = 0; i < n; ++i) {
                    upd[i] += arr[i].charAt(j);
                }
            }
        }
        return deletion;
    }
}

// O(n * len)
class Solution {
    public int minDeletionSize(String[] A) {
        int N = A.length;
        int W = A[0].length();
        boolean[] cuts = new boolean[N - 1];

        int ans = 0;
        search: for (int j = 0; j < W; ++j) {
            for (int i = 0; i < N - 1; ++i)
                if (!cuts[i] && A[i].charAt(j) > A[i + 1].charAt(j)) {
                    ans++;
                    continue search;
                }

            for (int i = 0; i < N - 1; ++i)
                if (A[i].charAt(j) < A[i + 1].charAt(j)) cuts[i] = true;
        }

        return ans;
    }
}
