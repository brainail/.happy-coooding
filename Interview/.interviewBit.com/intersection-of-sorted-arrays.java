public class Solution {
    // DO NOT MODIFY THE LISTS
    public ArrayList<Integer> intersect(final List<Integer> a, final List<Integer> b) {
        final ArrayList<Integer> intersection = new ArrayList<> ();
        int aIndex = 0;
        int aSize = a.size();
        int bIndex = 0;
        int bSize = b.size();
        while (aIndex < aSize || bIndex < bSize) {
            if (aIndex < aSize && (bIndex >= bSize || a.get(aIndex) < b.get(bIndex))) {
                ++ aIndex;
            } else if (bIndex < bSize && (aIndex >= aSize || b.get(bIndex) < a.get(aIndex))) {
                ++ bIndex;
            }
            if (aIndex < aSize && bIndex < bSize && (int) a.get(aIndex) == (int) b.get(bIndex)) {
                intersection.add(a.get(aIndex));
                ++ aIndex;
                ++ bIndex;
            }
        }
        return intersection;
    }
}
