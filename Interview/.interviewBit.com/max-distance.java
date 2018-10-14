public class Solution {
    // DO NOT MODIFY THE LIST
    public int maximumGap(final List<Integer> arr) {
        final int n = arr.size();
        
        int bestDiff = -1;
        final int rightMax [] = new int [n];
        final int leftMin [] = new int [n];
 
        leftMin [0] = arr.get(0);
        rightMax [n - 1] = arr.get(n - 1);
        for (int i = 1; i < n; ++ i) {
            leftMin [i] = Math.min(arr.get(i), leftMin [i - 1]);
            rightMax [n - i - 1] = Math.max(arr.get(n - i - 1), rightMax [n - i]);
        }
 
        int li = 0; 
        int ri = 0; 
        while (li < n && ri < n) {
            if (leftMin [li] <= rightMax [ri]) {
                bestDiff = Math.max(bestDiff, ri - li);
                ++ ri;
            } else {
                ++ li;
            }
        }
 
        return bestDiff;
    }
}
