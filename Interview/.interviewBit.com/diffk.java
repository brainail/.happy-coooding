public class Solution {
    public int diffPossible(ArrayList<Integer> numbers, int diff) {
        int right = 1;
        final int size = numbers.size();
        for (int i = 0; i < size; ++ i) {
            right = Math.max(i + 1, right);
            final int target = numbers.get(i) + diff;
            while (right < size && numbers.get(right) < target) {
                ++ right;
            }
            if (right < size && numbers.get(right) == target) {
                return 1;
            }
        }
        return 0;
    }
}
