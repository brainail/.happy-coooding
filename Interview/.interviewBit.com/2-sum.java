public class Solution {
    public ArrayList<Integer> twoSum(final List<Integer> numbers, int target) {
        final HashMap<Integer, ArrayList<Integer>> numbersToIndexes 
            = new HashMap<Integer, ArrayList<Integer>> ();
        final int n = numbers.size();
        for (int index = 0; index < n; ++ index) {
            final int first = numbers.get(index);
            if (!numbersToIndexes.containsKey(first)) {
                numbersToIndexes.put(first, new ArrayList<Integer> ());
            }
            numbersToIndexes.get(first).add(index);
        }
        for (int index2 = 0; index2 < n; ++ index2) {
            final int first = target - numbers.get(index2);
            if (numbersToIndexes.containsKey(first)) {
                for (final Integer index : numbersToIndexes.get(first)) {
                    if (index < index2) {
                        final ArrayList<Integer> result = new ArrayList<> (2);
                        result.add(index + 1);
                        result.add(index2 + 1);
                        return result;
                    }
                }
            }
        }
        return new ArrayList<Integer> ();
    }
}
