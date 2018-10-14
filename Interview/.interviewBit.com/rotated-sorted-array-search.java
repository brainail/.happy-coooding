public class Solution {
    // DO NOT MODIFY THE LIST
    public int search(final List<Integer> a, int t) {
        int low = 0;
        int high = a.size() - 1;
        while (low <= high) {
            int mid = (low + high) >> 1;
            if (a.get(mid) == t) {
                return mid;
            }
            if (a.get(low) <= a.get(mid)) {
                if (t >= a.get(low) && t <= a.get(mid)) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else {
                if (t >= a.get(mid) && t <= a.get(high)) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
                
            }
        }
        return -1;
    }
}
