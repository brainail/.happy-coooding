public class Solution {
    public void rotate(final ArrayList<ArrayList<Integer>> matrix) {
        final int n = matrix.size();
        for (int i = 0; i < 3; ++ i) { // LOL ;)
        for (int x = 0; x < (n >> 1); ++ x) {
            for (int y = x; y < n - x - 1; ++ y) {
                final int buffer = matrix.get(x).get(y);
                matrix.get(x).set(y, matrix.get(y).get(n-1-x));
                matrix.get(y).set(n - x - 1, matrix.get(n - x - 1).get(n - y - 1));
                matrix.get(n - x - 1).set(n - y - 1, matrix.get(n - y - 1).get(x));
                matrix.get(n - y - 1).set(x, buffer);
            }
        }
        }
    }
}
