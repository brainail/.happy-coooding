// 1 - from root find longest path and then from the end of this path again find the longest path
// 2 - from root using DP approach (see below)

public class Solution {
    private final class MaxPathResult {
        public int zig = 0;
        public int zigZag = 0;
    }
    
    // o(n), recursion, bad idea for 40000+
    private MaxPathResult findMaxPathOverflow(final int v, final ArrayList<ArrayList<Integer>> tree) {
        if (tree.get(v).isEmpty()) {
            return new MaxPathResult();
        }
        
        final MaxPathResult maxPathResult = new MaxPathResult();
        maxPathResult.zig = -1;
        int maxPathZag = -1;
        
        for (final Integer to : tree.get(v)) {
            final MaxPathResult maxPath = findMaxPath(to, tree);
            
            if (maxPath.zig > maxPathResult.zig) {
                maxPathZag = maxPathResult.zig;
                maxPathResult.zig = maxPath.zig;
            } else {
                maxPathZag = Math.max(maxPathZag, maxPath.zig);
            }
            
            maxPathResult.zigZag = Math.max(maxPathResult.zigZag, maxPath.zigZag);
        }
        
        ++ maxPathResult.zig;
        if (maxPathZag >= 0) {
            maxPathResult.zigZag = Math.max(maxPathResult.zigZag, maxPathResult.zig + (maxPathZag + 1));
        } else {
            maxPathResult.zigZag = Math.max(maxPathResult.zigZag, maxPathResult.zig);
        }
        
        return maxPathResult;
    }
    
    // o(n), no recursion
    private MaxPathResult findMaxPath(final int root, final ArrayList<ArrayList<Integer>> tree) {
        final ArrayList<Integer> vOrder = new ArrayList<Integer> (tree.size()); 
        final MaxPathResult [] vResult = new MaxPathResult [tree.size()];
        vOrder.add(root);
        
        for (int i = 0; i < vOrder.size(); ++ i) {
            final int v = vOrder.get(i);
            
            for (final Integer to : tree.get(v)) {
                vOrder.add(to);
            }
        }

        for (int i = vOrder.size() - 1; i >= 0; -- i) {
            final int v = vOrder.get(i);
            
            if (tree.get(v).isEmpty()) {
                vResult [v] = new MaxPathResult();
                continue;
            }
            
            final MaxPathResult maxPathResult = new MaxPathResult();
            maxPathResult.zig = -1;
            int maxPathZag = -1;
        
            for (final Integer to : tree.get(v)) {
                final MaxPathResult maxPath = vResult [to];
            
                if (maxPath.zig > maxPathResult.zig) {
                    maxPathZag = maxPathResult.zig;
                    maxPathResult.zig = maxPath.zig;
                } else {
                    maxPathZag = Math.max(maxPathZag, maxPath.zig);
                }
            
                maxPathResult.zigZag = Math.max(maxPathResult.zigZag, maxPath.zigZag);
            }
        
            ++ maxPathResult.zig;
            if (maxPathZag >= 0) {
                maxPathResult.zigZag = Math.max(maxPathResult.zigZag, maxPathResult.zig + (maxPathZag + 1));
            } else {
                maxPathResult.zigZag = Math.max(maxPathResult.zigZag, maxPathResult.zig);
            }
            
            vResult [v] = maxPathResult;
        }
        
        return vResult [root];
    }
    
    public int solve(ArrayList<Integer> P) {
        final int n = P.size();
        final ArrayList<ArrayList<Integer>> tree = new ArrayList<ArrayList<Integer>> (n);
        
        for (int i = 0; i < n; ++ i) {
            tree.add(new ArrayList<Integer> ());
        }
        
        int root = -1;
        for (int i = 0; i < n; ++ i) {
            if (P.get(i) >= 0) {
                tree.get(P.get(i)).add(i);
            } else {
                root = i;
            }
        }
        
        return findMaxPath(root, tree).zigZag;
    }
}
