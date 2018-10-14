public class Solution {
    // DO NOT MODIFY THE LIST. IT IS READ ONLY
    public int hammingDistance(final List<Integer> A) {
        final int n = A.size();
        long result = 0;
        
        for (int bij = 0; bij < 32; ++ bij) {
            long good = 0;
            for (final Integer val : A) {
                good += ((long) val >> (long) bij) & 1L;
            }

            result += (good * (n - good));
            result %= 1000000007L;
        }
        
        result = (result * 2L) % 1000000007L;
        return (int) result;
    }
}
