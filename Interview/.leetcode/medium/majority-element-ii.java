/**
 * Given an integer array of size n, find all elements that appear more than ⌊
 * n/3 ⌋ times.
 * 
 * Note: The algorithm should run in linear time and in O(1) space.
 * 
 * Example 1:
 * 
 * Input: [3,2,3] Output: [3] Example 2:
 * 
 * Input: [1,1,1,3,3,2,2,2] Output: [1,2]
 */
class Solution {
    public List<Integer> majorityElement(int[] nums) {
        Map<Integer, Integer> counter = new HashMap<>(3); // O(Const) ~-> O(1)
        for (int x : nums) {
            counter.put(x, counter.getOrDefault(x, 0) + 1);
            if (counter.size() == 3) {
                for (int y : (new ArrayList<Integer>(counter.keySet()))) {
                    int newCount = counter.getOrDefault(y, 1) - 1;
                    counter.remove(y);
                    if (newCount > 0)
                        counter.put(y, newCount);
                }
            }
        }
        List<Integer> ret = new ArrayList<>();
        for (int x : counter.keySet()) { // O(N * Const) ~-> O(N)
            int count = 0;
            for (int y : nums)
                count += y == x ? 1 : 0;
            if (count > nums.length / 3)
                ret.add(x);
        }
        return ret;
    }
}
