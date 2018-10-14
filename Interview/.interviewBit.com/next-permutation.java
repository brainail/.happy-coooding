public class Solution {
    public void nextPermutation(ArrayList<Integer> a) {
        int pivot = -1;
        int n = a.size();
        for (int index = n - 1; index > 0; -- index) {
            if (a.get(index - 1) < a.get(index)) {
                pivot = index - 1;
                break;
            }
        }
        if (pivot >= 0) {
            for (int index = n - 1; index > pivot; -- index) {
                if (a.get(index) > a.get(pivot)) {
                    int buff = a.get(index);
                    a.set(index, a.get(pivot));
                    a.set(pivot, buff);
                    break;
                }
            }
        }
        for (int index = n - 1; index > pivot; -- index) {
            int revIndex = pivot + n - index;
            if (revIndex < index) {
                int buff = a.get(index);
                a.set(index, a.get(revIndex));
                a.set(revIndex, buff);
            }
        }
    }
}
