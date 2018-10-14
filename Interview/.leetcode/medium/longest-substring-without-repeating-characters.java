/**
 * Given a string, find the length of the longest substring without repeating
 * characters.
 * 
 * Example 1:
 * 
 * Input: "abcabcbb" Output: 3 Explanation: The answer is "abc", with the length
 * of 3. Example 2:
 * 
 * Input: "bbbbb" Output: 1 Explanation: The answer is "b", with the length of
 * 1. Example 3:
 * 
 * Input: "pwwkew" Output: 3 Explanation: The answer is "wke", with the length
 * of 3. Note that the answer must be a substring, "pwke" is a subsequence and
 * not a substring.
 */
class Solution {
    public int lengthOfLongestSubstring(String s) {
        Set<Character> set = new HashSet<>();
        int n = s.length();
        char[] text = s.toCharArray();
        int left = 0;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            if (set.contains(text[i])) {
                while (text[left] != text[i])
                    set.remove(text[left++]);
                ++left;
            } else {
                set.add(text[i]);
            }
            result = Math.max(result, i - left + 1);
        }
        return result;
    }
}
