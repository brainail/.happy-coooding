public class Solution {
    public int removeDuplicates(ArrayList<Integer> a) {
        if (0 == a.size()) {
            return 0;
        }
        
        final int size = a.size();
        int newSize = 1;
        for (int i = 1; i < size; ++ i) {
            final int val = a.get(i);
            if (val != a.get(newSize - 1)) {
                a.set(newSize ++, val);
            }
        }
        
        a.subList(newSize, size).clear();
        return newSize;
    }
}
