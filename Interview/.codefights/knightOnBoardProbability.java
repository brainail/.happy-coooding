final int [] vx = {+2, +2, -2, -2, -1, +1, -1, +1};
final int [] vy = {-1, +1, -1, +1, +2, +2, -2, -2};

double knightOnBoardProbability(int n, int m, int steps, int x0, int y0) {
    BigInteger [][][] move = new BigInteger [n][m][steps + 1];
    move [x0][y0][0] = BigInteger.valueOf(1);
    for (int step = 0; step < steps; ++ step)
        for (int x = 0; x < n; ++ x)
            for (int y = 0; y < m; ++ y) {
                if (move [x][y][step] != null) 
                    for (int v = 0; v < 8; ++ v) {
                        int nx = x + vx [v];
                        int ny = y + vy [v];
                        if (nx < 0 || nx >= n) continue;
                        if (ny < 0 || ny >= m) continue;
                        if (move [nx][ny][step + 1] == null) {
                            move [nx][ny][step + 1] = BigInteger.valueOf(0);
                        }
                        move [nx][ny][step + 1] 
                            = move [nx][ny][step + 1].add(move [x][y][step]);
                    }
            }
    
    BigInteger moves = BigInteger.valueOf(0);
    for (int x = 0; x < n; ++ x)
        for (int y = 0; y < m; ++ y)
            if (move [x][y][steps] != null) {
                moves = moves.add(move [x][y][steps]);
            }
    
    BigInteger allMoves = BigInteger.valueOf(1);
    for (int step = 0; step < steps; ++ step) 
        allMoves = allMoves.multiply(BigInteger.valueOf(8));

    BigDecimal p = (new BigDecimal(moves)).divide(new BigDecimal(allMoves));
    p = p.setScale(20, BigDecimal.ROUND_UP);
    return p.doubleValue();
}
