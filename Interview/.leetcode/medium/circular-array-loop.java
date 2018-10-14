/**
 * You are given an array of positive and negative integers. If a number n at an
 * index is positive, then move forward n steps. Conversely, if it's negative
 * (-n), move backward n steps. Assume the first element of the array is forward
 * next to the last element, and the last element is backward next to the first
 * element. Determine if there is a loop in this array. A loop starts and ends
 * at a particular index with more than 1 element along the loop. The loop must
 * be "forward" or "backward'.
 * 
 * Example 1: Given the array [2, -1, 1, 2, 2], there is a loop, from index 0 ->
 * 2 -> 3 -> 0.
 * 
 * Example 2: Given the array [-1, 2], there is no loop.
 * 
 * Note: The given array is guaranteed to contain no element "0".
 * 
 * Can you do it in O(n) time complexity and O(1) space complexity?
 */
class Solution {
    public boolean circularArrayLoop(int[] nums) {
        for (int i = 0; i < nums.length; ++i) {
            int slow = i, fast = nextIndex(i, nums);
            while (slow != fast && nums[slow] != 0 && nums[fast] != 0) {
                slow = nextIndex(slow, nums);
                fast = nextIndex(nextIndex(fast, nums), nums);
            }
            if (slow == fast && nums[slow] != 0) {
                int loopSize = 1, index = nextIndex(slow, nums);
                int forward = nums[slow] > 0 ? 1 : 0, backward = nums[slow] < 0 ? 1 : 0;
                while (slow != index && nums[slow] != 0 && nums[fast] != 0) {
                    forward |= nums[index] > 0 ? 1 : 0;
                    backward |= nums[index] < 0 ? 1 : 0;
                    ++loopSize;
                    index = nextIndex(index, nums);
                }
                if (loopSize > 1 && forward + backward == 1)
                    return true;
            }
            int index = i;
            while (nums[index] != 0) {
                int nextIndex = nextIndex(index, nums);
                nums[index] = 0;
                index = nextIndex;
            }
        }
        return false;
    }

    public int nextIndex(int i, int[] nums) {
        int n = nums.length;
        return i + nums[i] >= 0 ? (i + nums[i]) % n : n + ((i + nums[i]) % n);
    }
}
