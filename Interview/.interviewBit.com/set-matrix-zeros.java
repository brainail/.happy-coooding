public class Solution {
    public void setZeroes(ArrayList<ArrayList<Integer>> a) {
        final int n = a.size();
        final int m = a.get(0).size();
        boolean fillRow = false;
        boolean fillCol = false;
        
        for (int row = 0; row < n; ++ row) {
            for (int col = 0; col < m; ++ col) {
                if (0 == a.get(row).get(col)) {
                    if (0 == row) fillRow = true;
                    if (0 == col) fillCol = true;
                    a.get(0).set(col, 0);
                    a.get(row).set(0, 0);
                }
            }
        }
        
        for (int row = 1; row < n; ++ row) {
            for (int col = 1; col < m; ++ col) {
                if (0 == a.get(row).get(0) || 0 == a.get(0).get(col)) {
                    a.get(row).set(col, 0);
                }
            }
        }
        
        if (fillRow) {
            for (int col = 0; col < m; ++ col) {
                a.get(0).set(col, 0);
            }
        }
        
        if (fillCol) {
            for (int row = 0; row < n; ++ row) {
                a.get(row).set(0, 0);
            }
        }
    }
}
