int bomber(char[][] field) {
    if (field.length == 0) return 0;
    
    final int n = field.length;
    final int m = field [0].length;
    final int [][][] enemy  = new int [n][m][4];
    
    for (int row = 0; row < n; ++ row) {
        int kl = 0, kr = 0;
        for (int column = 0; column < m; ++ column) {
            if ('E' == field [row][column]) ++ kl;
            if ('E' == field [row][m - column - 1]) ++ kr;
            if ('W' == field [row][column]) kl = 0;
            if ('W' == field [row][m - column - 1]) kr = 0;
            enemy [row][column][0] = kl;
            enemy [row][m - column - 1][1] = kr;
        }
    }

    for (int column = 0; column < m; ++ column) {
        int ku = 0, kd = 0;
        for (int row = 0; row < n; ++ row) {
            if ('E' == field [row][column]) ++ ku;
            if ('E' == field [n - row - 1][column]) ++ kd;
            if ('W' == field [row][column]) ku = 0;
            if ('W' == field [n - row - 1][column]) kd = 0;
            enemy [row][column][2] = ku;
            enemy [n - row - 1][column][3] = kd;
        }
    }
    
    int max = 0;
    for (int row = 0; row < n; ++ row) {
        for (int column = 0; column < m; ++ column) {
            if ('0' != field [row][column]) continue;
            int shot = 0;
            for (int k = 0; k < 4; ++ k) {
                shot += enemy [row][column][k];
            }
            max = Math.max(max, shot);
        }
    }
    
    return max;
}
