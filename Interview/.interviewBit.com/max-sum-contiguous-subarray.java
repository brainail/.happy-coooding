public class Solution {
    // DO NOT MODFIY THE LIST. 
    public int maxSubArray(final List<Integer> a) {
        int result = Integer.MIN_VALUE;
        int currentSum = 0;
        for (int i = 0, size = a.size(); i < size; ++ i) {
            currentSum += a.get(i);
            result = Math.max(result, currentSum);
            currentSum = currentSum < 0 ? 0 : currentSum;
        }
        return result;
    }
}
