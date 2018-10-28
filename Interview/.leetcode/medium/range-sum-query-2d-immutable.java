/**
 * Given a 2D matrix matrix, find the sum of the elements inside the rectangle
 * defined by its upper left corner (row1, col1) and lower right corner (row2,
 * col2).
 */
class NumMatrix {
    int[][] sum;

    public NumMatrix(int[][] matrix) {
        sum = matrix;
        if (sum.length == 0)
            return;
        for (int j = 1; j < sum[0].length; ++j)
            sum[0][j] = sum[0][j - 1] + sum[0][j];
        for (int i = 1; i < sum.length; ++i)
            sum[i][0] = sum[i - 1][0] + sum[i][0];
        for (int i = 1; i < sum.length; ++i)
            for (int j = 1; j < sum[i].length; ++j)
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + sum[i][j];
    }

    public int sumRegion(int r1, int c1, int r2, int c2) {
        if (sum.length == 0)
            return 0;
        return sum[r2][c2] - (c1 > 0 ? sum[r2][c1 - 1] : 0) - (r1 > 0 ? sum[r1 - 1][c2] : 0)
                + (c1 > 0 && r1 > 0 ? sum[r1 - 1][c1 - 1] : 0);
    }
}
