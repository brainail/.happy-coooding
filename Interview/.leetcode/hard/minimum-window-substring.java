/**
 * Given a string S and a string T, find the minimum window in S which will
 * contain all the characters in T in complexity O(n).
 * 
 * Example:
 * 
 * Input: S = "ADOBECODEBANC", T = "ABC" Output: "BANC" Note:
 * 
 * If there is no such window in S that covers all characters in T, return the
 * empty string "". If there is such window, you are guaranteed that there will
 * always be only one unique minimum window in S.
 */
class Solution {
    public String minWindow(String s, String t) {
        Map<Character, Integer> charCount = new HashMap<>();
        int kt = t.length();
        for (int i = 0; i < kt; ++i) {
            charCount.put(t.charAt(i), charCount.containsKey(t.charAt(i)) ? charCount.get(t.charAt(i)) + 1 : 1);
        }
        int resultLen = Integer.MAX_VALUE;
        int resultStartPoint = 0;
        int j = 0;
        for (int i = 0, len = s.length(); i < len; ++i) {
            while (j < len && kt > 0) {
                if (charCount.containsKey(s.charAt(j))) {
                    charCount.put(s.charAt(j), charCount.get(s.charAt(j)) - 1);
                    if (charCount.get(s.charAt(j)) >= 0)
                        --kt;
                }
                ++j;
            }
            if (0 == kt && j - i < resultLen) {
                resultLen = j - i;
                resultStartPoint = i;
            }
            if (charCount.containsKey(s.charAt(i))) {
                charCount.put(s.charAt(i), charCount.get(s.charAt(i)) + 1);
                if (charCount.get(s.charAt(i)) > 0)
                    ++kt;
            }
        }
        return Integer.MAX_VALUE == resultLen ? "" : s.substring(resultStartPoint, resultStartPoint + resultLen);
    }
}
