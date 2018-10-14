boolean[] squaresUnderQueenAttack(int n, int[][] queens, int[][] queries) {
    boolean [] d1 = new boolean [2 * n + 1];
    boolean [] d2 = new boolean [2 * n + 1];
    boolean [] d3 = new boolean [n + 1];
    boolean [] d4 = new boolean [n + 1];
    for (int i = 0; i < queens.length; ++ i) {
        d1 [queens [i][0] - queens [i][1] + n] = true;
        d2 [queens [i][0] + queens [i][1]] = true;
        d3 [queens [i][0]] = true;
        d4 [queens [i][1]] = true;
    }
    boolean [] result = new boolean [queries.length];
    for (int i = 0; i < queries.length; ++ i) {
        result [i] = d1 [queries [i][0] - queries [i][1] + n] 
            || d2 [queries [i][0] + queries [i][1]]
            || d3 [queries [i][0]]
            || d4 [queries [i][1]];
    }
    return result;
}
