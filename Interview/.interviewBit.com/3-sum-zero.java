public class Solution {
    public ArrayList<ArrayList<Integer>> threeSum(ArrayList<Integer> a) {
        HashSet<ArrayList<Integer>> result = new HashSet<>();
        Collections.sort(a);
        final int size = a.size();
        for (int prev = 0; prev < size - 2; ++ prev) {
            int left = prev + 1;
            int right = size - 1;
            while (left < right) {
                final int currentSum = a.get(prev) + a.get(left) + a.get(right);
                if (0 == currentSum) {
                    final ArrayList<Integer> triple = new ArrayList<>(3);
                    triple.add(a.get(prev));
                    triple.add(a.get(left));
                    triple.add(a.get(right));
                    result.add(triple);
                    ++ left;
                } else if (currentSum > 0) {
                    -- right;
                } else {
                    ++ left;
                }
            }
        }
        return new ArrayList<ArrayList<Integer>>(result);
    }
}
