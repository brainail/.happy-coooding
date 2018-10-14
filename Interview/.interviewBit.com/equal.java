public class Solution {
    public static final class Pair {
        public final int first;
        public final int second;
        public Pair(final int first, final int second) {
            this.first = first;
            this.second = second;
        }
    }
    
    public static boolean less(final ArrayList<Integer> first, final ArrayList<Integer> second) {
        if (second.isEmpty()) {
            return true;
        }
        
        for (int i = 0; i < 4; ++ i) {
            if (first.get(i) < second.get(i)) {
                return true;
            }
            if (first.get(i) > second.get(i)) {
                return false;
            }
        }
        
        return false;
    }
    
    public ArrayList<Integer> equal(ArrayList<Integer> numbers) {
        final int n = numbers.size();
        final HashMap<Integer, ArrayList<Pair>> sum2Ind = new HashMap<> (n * (n - 1) / 2);
        ArrayList<Integer> result = new ArrayList<> (4);
        
        for (int i = 0; i < n; ++ i) {
            for (int q = i + 1; q < n; ++ q) {
                final int sum = numbers.get(i) + numbers.get(q);
                if (!sum2Ind.containsKey(sum)) {
                    sum2Ind.put(sum, new ArrayList<Pair> (1));
                }
                final Pair secondPair = new Pair(i, q);
                
                for (final Pair firstPair : sum2Ind.get(sum)) {
                    if (firstPair.first < secondPair.first 
                            && firstPair.second != secondPair.first
                            && firstPair.second != secondPair.second) {
                                
                                final ArrayList<Integer> candidate = new ArrayList<> (4);
                                candidate.add(firstPair.first);
                                candidate.add(firstPair.second);
                                candidate.add(secondPair.first);
                                candidate.add(secondPair.second);
                                
                                if (less(candidate, result)) {
                                    result = candidate;
                                }
                            }
                }
                
                // actually we don't need all this stuff with HashMap LOL :3
                if (sum2Ind.get(sum).isEmpty()) {
                    sum2Ind.get(sum).add(secondPair);
                }
            }
        }
        
        return result;
    }
}
