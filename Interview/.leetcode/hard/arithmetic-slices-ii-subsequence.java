/**
 * A sequence of numbers is called arithmetic if it consists of at least three
 * elements and if the difference between any two consecutive elements is the
 * same.
 * 
 * For example, these are arithmetic sequences:
 * 
 * 1, 3, 5, 7, 9 7, 7, 7, 7 3, -1, -5, -9 The following sequence is not
 * arithmetic.
 * 
 * 1, 1, 2, 5, 7
 * 
 * A zero-indexed array A consisting of N numbers is given. A subsequence slice
 * of that array is any sequence of integers (P0, P1, ..., Pk) such that 0 ≤ P0
 * < P1 < ... < Pk < N.
 * 
 * A subsequence slice (P0, P1, ..., Pk) of array A is called arithmetic if the
 * sequence A[P0], A[P1], ..., A[Pk-1], A[Pk] is arithmetic. In particular, this
 * means that k ≥ 2.
 * 
 * The function should return the number of arithmetic subsequence slices in the
 * array A.
 * 
 * The input contains N integers. Every integer is in the range of -231 and
 * 231-1 and 0 ≤ N ≤ 1000. The output is guaranteed to be less than 231-1.
 * 
 * 
 * Example:
 * 
 * Input: [2, 4, 6, 8, 10]
 * 
 * Output: 7
 * 
 * Explanation: All arithmetic subsequence slices are: [2,4,6] [4,6,8] [6,8,10]
 * [2,4,6,8] [4,6,8,10] [2,4,6,8,10] [2,6,10]
 */
class Solution {
    public int numberOfArithmeticSlices(int[] A) {
        int n = A.length;
        long ans = 0;
        Map<Integer, Integer>[] cnt = new Map[n];
        for (int i = 0; i < n; i++) {
            cnt[i] = new HashMap<>(i);
            for (int j = 0; j < i; j++) {
                long delta = (long)A[i] - (long)A[j];
                if (delta < Integer.MIN_VALUE || delta > Integer.MAX_VALUE) continue;
                int diff = (int) delta;
                int sum = cnt[j].getOrDefault(diff, 0);
                int origin = cnt[i].getOrDefault(diff, 0);
                cnt[i].put(diff, origin + sum + 1);
                ans += sum;
            }
        }
        return (int) ans;        
    }
}

/* a bit another approach, but due to forming key it's TL 
class Solution {
  public int numberOfArithmeticSlices(int[] a) {
    int n = a.length;
    int ret = -(n * (n - 1)) / 2;   
    Set<Long> diffs = new HashSet<>(n);
    Map<String, Long> dp = new HashMap<>();
    for (int i = 0; i < n; ++ i) {
      long x = a[i];
      diffs.clear();
      for (int j = 0; j < i; ++ j) {
        long d = x - a[j], prevX = x - (x - a[j]);   
        String curState = x + " " + d;  
        if (!diffs.add(d) || prevX < Integer.MIN_VALUE || prevX > Integer.MAX_VALUE) {
          long curDp = dp.getOrDefault(curState, 0L);
          dp.put(curState, curDp + 1);
          ++ ret;   
          continue;    
        } 
        long curDp = dp.getOrDefault(curState, 0L);
        long prevDp = dp.getOrDefault(prevX + " " + d, 0L);
        dp.put(curState, prevDp + 1 + curDp);
        ret = (int) (prevDp + 1 + ret);
      }
    } 
    return ret;
  }
}
*/

