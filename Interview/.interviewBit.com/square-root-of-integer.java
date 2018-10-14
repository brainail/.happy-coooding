public class Solution {
    public int sqrt(int a) {
        long low = 0;
        long high = a;
        while (high - low > 1) {
            final long mid = (high + low) >> 1;
            if (mid * mid > a) {
                high = mid;
            } else {
                low = mid;
            }
        }
        return high * high <= a ? (int) high : (int) low;
    }
}
