public class Solution {
    public ArrayList<ArrayList<Integer>> fourSum(ArrayList<Integer> a, int target) {
        final LinkedHashSet<ArrayList<Integer>> uniqueItems = new LinkedHashSet<ArrayList<Integer>> ();
        Collections.sort(a);
        final int n = a.size();
        
        for (int i = 0; i < n - 3; ++ i) {
            for (int t = i + 1; t < n - 2; ++ t) {
                int f = t + 1;
                int l = n - 1;
                while (f < l) {
                    final int currentSum = a.get(i) + a.get(t) + a.get(f) + a.get(l);
                    if (target == currentSum) {
                        final ArrayList<Integer> quadruplet = new ArrayList<> (4);
                        quadruplet.add(a.get(i));
                        quadruplet.add(a.get(t));
                        quadruplet.add(a.get(f));
                        quadruplet.add(a.get(l));
                        uniqueItems.add(quadruplet);
                        ++ f;
                    } else if (currentSum > target) {
                        -- l;
                    } else {
                        ++ f;
                    }
                }
            }
        }
        
        return new ArrayList<ArrayList<Integer>> (uniqueItems);
    }
}
