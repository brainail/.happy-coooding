public class Solution {
    public ArrayList<ArrayList<Integer>> generate(int a) {
        final ArrayList<ArrayList<Integer>> pascal = new ArrayList<ArrayList<Integer>> (a);
        for (int row = 0; row < a; ++ row) {
            final ArrayList<Integer> arr = new ArrayList<> (row + 1);
            arr.add(1);
            for (int col = 1; col < row; ++ col) {
                arr.add(pascal.get(row - 1).get(col - 1) + pascal.get(row - 1).get(col));
            }
            if (row > 0) arr.add(1);
            pascal.add(arr);
        }
        return pascal;
    }
}
