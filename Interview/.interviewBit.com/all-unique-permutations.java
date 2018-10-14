public class Solution {
    public final void genAll(
        final int pos, 
        final int [] buff, 
        final ArrayList<ArrayList<Integer>> result,
        final HashMap<Integer, Integer> n2k) {
            
        if (pos == buff.length) {
            final ArrayList<Integer> buffList = new ArrayList<> (buff.length);
            for (final int buffItem : buff) {
                buffList.add(buffItem);
            }
            result.add(buffList);
            return;
        }
        
        for (final Integer item : n2k.keySet()) {
            if (n2k.get(item) > 0) {
                buff [pos] = item;
                n2k.put(item, n2k.get(item) - 1);
                genAll(pos + 1, buff, result, n2k);
                n2k.put(item, n2k.get(item) + 1);
            }
        }
    }
    
    public ArrayList<ArrayList<Integer>> permute(ArrayList<Integer> arr) {
        final HashMap<Integer, Integer> n2k = new HashMap<> (arr.size());
        for (final Integer x : arr) {
            n2k.put(x, !n2k.containsKey(x) ? 1 : n2k.get(x) + 1);
        }
        
        final ArrayList<ArrayList<Integer>> result = new ArrayList<ArrayList<Integer>>();
        final int [] buff = new int [arr.size()];
        genAll(0, buff, result, n2k);
        return result;
    }
}
