public class Solution {
    // DO NOT MODIFY THE LIST
    public ArrayList<Integer> slidingMaximum(final List<Integer> a, int w) {
        if (null == a || 0 == a.size() || w <= 0) {
            return new ArrayList<Integer> ();
        }
        
        final int size = a.size();
        final ArrayList<Integer> outResult = new ArrayList<> (size);
        final LinkedList<Integer> window = new LinkedList<> ();
        
        for (int i = 0; i < w; ++ i) {
            if (i >= size) break;
            while (!window.isEmpty() && a.get(i) >= a.get(window.getLast())) window.removeLast();
            window.addLast(i);
        }
        
        for (int i = 0; i < size; ++ i) {
            outResult.add(a.get(window.getFirst()));
            if (i + w >= size) break;
            while (!window.isEmpty() && a.get(i + w) >= a.get(window.getLast())) window.removeLast();
            while (!window.isEmpty() && window.getFirst() <= i) window.removeFirst();
            window.add(i + w);
        }
        
        return outResult;
    }
}
