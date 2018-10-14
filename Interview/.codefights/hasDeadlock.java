void dfs(int u, boolean [] visited, List<Integer> sorted, int[][] connections) {
    visited [u] = true;
    for (int v : connections [u]) 
        if (!visited [v]) dfs(v, visited, sorted, connections);
    sorted.add(u);
}

boolean hasDeadlock(int[][] connections) {
    final int n = connections.length;
    boolean [] visited = new boolean [n];
    List<Integer> sorted = new ArrayList<>(n);
    for (int i = 0; i < n; ++ i)
        if (!visited [i]) {
            dfs(i, visited, sorted, connections);
        }
    Collections.reverse(sorted);
    Arrays.fill(visited, false);
    for (int u : sorted) {
        for (int v : connections [u]) 
            if (visited [v]) return true;
        visited [u] = true;
    }
    return false;
}
