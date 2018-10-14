void dfs(int u, int p, int[][] connections) {
    ++ timer;
    visited [u] = true;
    tin [u] = tup [u] = timer;
    for (int v = 0; v < connections [u].length; ++ v) {
        if (u == v || connections [u][v] == 0) continue;
        if (v == p) continue;
        if (!visited [v]) {
            dfs(v, u, connections);
            tup [u] = Math.min(tup [u], tup [v]);
            if (tup [v] > tin [u]) ++ failEdges;
        } else {
            tup [u] = Math.min(tup [u], tin [v]);
        }
    }
}

boolean [] visited;
int [] tin;
int [] tup;
int timer = 0;
int failEdges = 0;

int singlePointOfFailure(int[][] connections) {
    final int n = connections.length;
    visited = new boolean [n];
    tin = new int [n];
    tup = new int [n];
    timer = 0;
    failEdges = 0;
    for (int i = 0; i < n; ++ i)
        if (!visited [i]) {
            dfs(i, -1, connections);
        }
    return failEdges;
}
