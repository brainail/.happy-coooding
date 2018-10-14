/**
 * Given an unsorted array of integers, find the length of the longest
 * consecutive elements sequence.
 * 
 * Your algorithm should run in O(n) complexity.
 * 
 * Example:
 * 
 * Input: [100, 4, 200, 1, 3, 2] Output: 4 Explanation: The longest consecutive
 * elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
 */
class Solution {
    public int longestConsecutive(int[] nums) {
        final Set<Integer> set = new HashSet<>();
        set.addAll(Arrays.stream(nums).boxed().collect(Collectors.toList()));
        int result = 0;
        while (!set.isEmpty()) {
            Iterator<Integer> it = set.iterator();
            int x = it.next();
            it.remove();
            int chain = 1;
            int prev = x - 1;
            while (set.contains(prev)) {
                set.remove(prev--);
                ++chain;
            }
            int next = x + 1;
            while (set.contains(next)) {
                set.remove(next++);
                ++chain;
            }
            result = Math.max(result, chain);
        }
        return result;
    }
}

// Neat approach
/**
 * class Solution {
    public int longestConsecutive(int[] nums) {
        Set<Integer> num_set = new HashSet<Integer>();
        for (int num : nums) {
            num_set.add(num);
        }

        int longestStreak = 0;

        for (int num : num_set) {
            if (!num_set.contains(num-1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.contains(currentNum+1)) {
                    currentNum += 1;
                    currentStreak += 1;
                }

                longestStreak = Math.max(longestStreak, currentStreak);
            }
        }

        return longestStreak;
    }
}
 */
