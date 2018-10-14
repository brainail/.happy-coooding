public class Solution {
    // DO NOT MODIFY THE LISTS
    public int minimize(final List<Integer> a, final List<Integer> b, final List<Integer> c) {
        int pa = 0, pb = 0, pc = 0;
        int sizea = a.size(), sizeb = b.size(), sizec = c.size();
        int result = Integer.MAX_VALUE;
        while (pa < sizea && pb < sizeb && pc < sizec) {
            result = Math.min(
                result, 
                Math.max(
                    Math.max(
                        Math.abs(a.get(pa) - b.get(pb)), 
                        Math.abs(b.get(pb) - c.get(pc))
                    ), 
                    Math.abs(c.get(pc) - a.get(pa))
                )
            );
            if (a.get(pa) <= b.get(pb) && a.get(pa) <= c.get(pc)) ++ pa; 
            else if (b.get(pb) <= a.get(pa) && b.get(pb) <= c.get(pc)) ++ pb; 
            else ++ pc;
        }
        return result;
    }
}
