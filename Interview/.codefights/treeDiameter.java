private final class MaxPathResult {
    public int zig = 0;
    public int zigZag = 0;
    }

    private MaxPathResult findMaxPath(final int root, final int parent, final ArrayList<ArrayList<Integer>> tree) {
        final ArrayList<Integer> vOrder = new ArrayList<Integer>(tree.size());
        final ArrayList<Integer> pOrder = new ArrayList<Integer>(tree.size());
        final MaxPathResult[] vResult = new MaxPathResult[tree.size()];
        vOrder.add(root);
        pOrder.add(parent);

        for (int i = 0; i < vOrder.size(); ++i) {
            final int v = vOrder.get(i);
            final int p = pOrder.get(i);

            for (final Integer to : tree.get(v)) {
                if (to == p)
                    continue;
                vOrder.add(to);
                pOrder.add(v);
            }
        }

        for (int i = vOrder.size() - 1; i >= 0; --i) {
            final int v = vOrder.get(i);
            final int p = pOrder.get(i);

            if (tree.get(v).isEmpty()) {
                vResult[v] = new MaxPathResult();
                continue;
            }

            if (tree.get(v).get(0) == p && tree.get(v).size() == 1) {
                vResult[v] = new MaxPathResult();
                continue;
            }

            final MaxPathResult maxPathResult = new MaxPathResult();
            maxPathResult.zig = -1;
            int maxPathZag = -1;

            for (final Integer to : tree.get(v)) {
                if (to == p)
                    continue;

                final MaxPathResult maxPath = vResult[to];

                if (maxPath.zig > maxPathResult.zig) {
                    maxPathZag = maxPathResult.zig;
                    maxPathResult.zig = maxPath.zig;
                } else {
                    maxPathZag = Math.max(maxPathZag, maxPath.zig);
                }

                maxPathResult.zigZag = Math.max(maxPathResult.zigZag, maxPath.zigZag);
            }

            ++maxPathResult.zig;
            if (maxPathZag >= 0) {
                maxPathResult.zigZag = Math.max(maxPathResult.zigZag, maxPathResult.zig + (maxPathZag + 1));
            } else {
                maxPathResult.zigZag = Math.max(maxPathResult.zigZag, maxPathResult.zig);
            }

            vResult[v] = maxPathResult;
        }

        return vResult[root];
    }

int treeDiameter(int n, int[][] treep) {
    final ArrayList<ArrayList<Integer>> tree = new ArrayList<ArrayList<Integer>> (n);
    for (int i = 0; i < n; ++ i) tree.add(new ArrayList<>(1));
    for (int i = 0; i < treep.length; ++ i) {
        tree.get(treep [i][0]).add(treep [i][1]);
        tree.get(treep [i][1]).add(treep [i][0]);
    }
    return findMaxPath(0, -1, tree).zigZag;
}
