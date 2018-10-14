public class Solution {
    public int uniquePathsWithObstacles(ArrayList<ArrayList<Integer>> a) {
        final int n = a.size();
        final int m = a.get(0).size();
        final int [][] ways = new int [2][m];
        for (final int [] row : ways) {
            Arrays.fill(row, 0);
        }
        
        ways [0][0] = 1 != a.get(0).get(0) ? 1 : 0;
        int level = 1;
        
        for (int i = 0; i < n; ++ i) {
            final int nextLevel = level ^ 1;
            for (int j = 0; j < m; ++ j) {
                if (1 != a.get(i).get(j)) {
                    if (i > 0) {
                        ways [nextLevel][j] += ways [level][j];
                    }
                    if (j > 0) {
                        ways [nextLevel][j] += ways [nextLevel][j - 1];
                    }
                }
            }
            Arrays.fill(ways [level], 0);
            level = nextLevel;
        }
        
        return ways [level][m - 1];
    }
}
