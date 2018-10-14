int paintHouses(int[][] cost) {
    int n = cost.length;
    int [][] dp = new int [n][3];
    dp [0][0] = cost [0][0];
    dp [0][1] = cost [0][1];
    dp [0][2] = cost [0][2];
    for (int i = 1; i < n; ++ i) Arrays.fill(dp [i], Integer.MAX_VALUE);
    for (int i = 1; i < n; ++ i) 
        for (int color = 0; color < 3; ++ color)
            for (int p = 0; p < 3; ++ p)
                if (p != color) {
                    dp [i][color] = Math.min(dp [i][color], dp [i - 1][p] + cost [i][color]);
                }
    return Math.min(Math.min(dp [n - 1][0], dp [n - 1][1]), dp [n - 1] [2]);
}
