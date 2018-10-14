public class Solution {
    public int diffPossible(final List<Integer> numbers, int target) {
        final int n = numbers.size();
        final HashMap<Integer, ArrayList<Integer>> numbersToIndexes
            = new HashMap<Integer, ArrayList<Integer>> (n);
        for (int i = 0; i < n; ++ i) {
            if (!numbersToIndexes.containsKey(numbers.get(i))) {
                numbersToIndexes.put(numbers.get(i), new ArrayList<Integer> (1));
            }
            numbersToIndexes.get(numbers.get(i)).add(i);
        }
        for (int i = 0; i < n; ++ i) {
            final int second = target + numbers.get(i);
            if (numbersToIndexes.containsKey(second)) {
                for (final Integer index : numbersToIndexes.get(second)) {
                    if (index != i) {
                        return 1;
                    }
                }
            }
        }
        return 0;
    }
}
