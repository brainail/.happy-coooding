public class Solution {
    public int maxArea(ArrayList<Integer> height) {
        if (null == height || height.size() < 2) {
            return 0;
        }
 
        int result = 0;
        int left = 0;
        int right = height.size() - 1;
 
        while (left < right) {
            result = Math.max(result, (right - left) * Math.min(height.get(left), height.get(right)));
            if (height.get(left) < height.get(right)) {
                ++ left;
            } else {
                -- right;
            }
        }
 
        return result;
    }
}
