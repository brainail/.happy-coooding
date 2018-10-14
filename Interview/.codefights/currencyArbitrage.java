boolean currencyArbitrage(double[][] exchange) {
    final int n = exchange.length;
    
    final int INF = 1000000000;
    final double EPS = 1e-7;

    for (int u = 0; u < n; ++ u) {
        for (int v = 0; v < n; ++ v) {
            exchange [u][v] = Math.log(exchange [u][v]);
        }
    }

    for (int t = 0; t < n; ++ t)
        for (int x = 0; x < n; ++ x)
            for (int y = 0; y < n; ++ y)
                if (exchange [x][t] + exchange [t][y] > exchange [x][y]) {
                    exchange [x][y] = exchange [x][t] + exchange [t][y];
                }
        
    for (int t = 0; t < n; ++ t)
        if (exchange [t][t] > EPS) {
            return true;
        }
    
    return false;
}
