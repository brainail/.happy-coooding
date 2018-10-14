public class Solution {
    public void sortColors(ArrayList<Integer> colors) {
        int red = 0;
        int white = 0;
        int blue = 0;
        final int size = colors.size();
        for (int i = 0; i < size; ++ i) {
            red += 0 == colors.get(i) ? 1 : 0;
            white += 1 == colors.get(i) ? 1 : 0;
            blue += 2 == colors.get(i) ? 1 : 0;
        }
        for (int i = 0; i < size; ++ i) {
            if (i < red) {
                colors.set(i, 0);
            } else if (i < red + white) {
                colors.set(i, 1);
            } else {
                colors.set(i, 2);
            }
        }
    }
}
