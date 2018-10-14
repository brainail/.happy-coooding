public class Solution {
    public int threeSumClosest(ArrayList<Integer> a, int target) {
        Collections.sort(a);
        int bestDiff = Integer.MAX_VALUE;
        final int size = a.size();
        for (int prev = 0; prev < size - 2; ++ prev) {
            int left = prev + 1;
            int right = size - 1;
            while (left < right) {
                final int currentSum = a.get(prev) + a.get(left) + a.get(right);
                final int diff = currentSum - target;
                if (Math.abs(diff) < Math.abs(bestDiff)) {
                    bestDiff = diff;
                }
                if (currentSum > target) {
                    -- right;
                } else {
                    ++ left;
                }
            }
        }
        return target + bestDiff;
    }
}
