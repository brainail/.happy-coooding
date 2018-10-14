public class Solution {
    // DO NOT MODIFY THE LIST
    public int findMin(final List<Integer> A) {
        final int N = A.size();
        
        int L = 0;
        int R = N - 1;
  
        while (A.get(L) > A.get(R)) {
            final int M = (L + R) >> 1;
            if (A.get(M) > A.get(R)) L = M + 1; else R = M;
        }
        
        return A.get(L);
    }
}
