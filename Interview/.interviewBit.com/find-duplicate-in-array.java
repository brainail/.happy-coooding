public class Solution {
    // DO NOT MODIFY THE LIST
    public int repeatedNumber(final List<Integer> A) {
        int n = A.size() - 1;
        if (n < 1) {
            return -1;
        }

        int m = (int) Math.sqrt(n); 
        final int [] B = new int [(int) Math.ceil(Math.sqrt(n))];
        if (m * B.length < n) {
            ++ m;
        }

        final int lastPortion = n - (B.length - 1) * m;

        int overflowId = -1;
        for (final int num : A) {
            int i = (num - 1) / m;
            ++ B [i];
            
            boolean found = false;
            if (i == B.length - 1) {
                found = B [i] > lastPortion;
            } else {
                found = B [i] > m;
            }
            
            if (found) {
                overflowId = i;
                break;
            }
        }
        
        if (overflowId != -1) {
            Set<Integer> overflowSet = new HashSet<>();
            final int lo = overflowId * m + 1;
            final int hi = lo + m - 1;
            for (final int num : A) {
                if (num >= lo && num <= hi && !overflowSet.add(num)) {
                    return num;
                }
            }
        }
        
        return -1;
    }
}
