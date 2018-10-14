public class Feeeeding {
    int V;
    int color[];
    
    Feeeeding(int V) {
        this.V = V;
    }
 
    boolean isSafe(int v, int graph[][], int color[], int c) {
        for (int i = 0; i < V; i++)
            if (graph[v][i] == 1 && c == color[i]) return false;
        return true;
    }
 
    boolean graphColoringUtil(int graph[][], int m, int color[], int v) {
        if (v == V) return true;
        for (int c = 1; c <= m; c++) {
            if (isSafe(v, graph, color, c)) {
                color[v] = c;
                if (graphColoringUtil(graph, m, color, v + 1)) return true;
                color[v] = 0;
            }
        }
        return false;
    }
 
    boolean graphColoring(int graph[][], int m) {
        color = new int[V];
        return graphColoringUtil(graph, m, color, 0);
    }
}


int feedingTime(String[][] classes) {
    int n = classes.length;
    int [][] g = new int [n][n];
    for (int u = 0; u < n; ++ u) {
        for (int v = u + 1; v < n; ++ v) {
            Set<String> uSet = new HashSet<>(Arrays.asList(classes [u]));
            Set<String> vSet = new HashSet<>(Arrays.asList(classes [v]));
            final int edge = !Collections.disjoint(uSet, vSet) ? 1 : 0;
            g [u][v] = g [v][u] = edge;
        }
    }
    
    for (int days = 1; days <= 5; ++ days) {
        if (new Feeeeding(n).graphColoring(g, days)) {
            return days;
        }
    }
    
    return -1;
}