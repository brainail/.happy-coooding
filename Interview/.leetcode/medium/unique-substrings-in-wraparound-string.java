/**
 * Consider the string s to be the infinite wraparound string of
 * "abcdefghijklmnopqrstuvwxyz", so s will look like this:
 * "...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
 * 
 * Now we have another string p. Your job is to find out how many unique
 * non-empty substrings of p are present in s. In particular, your input is the
 * string p and you need to output the number of different non-empty substrings
 * of p in the string s.
 * 
 * Note: p consists of only lowercase English letters and the size of p might be
 * over 10000.
 * 
 * Example 1: Input: "a" Output: 1
 * 
 * Explanation: Only the substring "a" of string "a" is in the string s.
 * Example 2: Input: "cac" Output: 2 Explanation: There are two substrings "a",
 * "c" of string "cac" in the string s. Example 3: Input: "zab" Output: 6
 * Explanation: There are six substrings "z", "a", "b", "za", "ab", "zab" of
 * string "zab" in the string s.
 */

// #1
class Solution {
    int findSubstringInWraproundString(String str) {
        char[] p = str.toCharArray();
        int[] letters = new int[26];
        int res = 0, len = 0;
        for (int i = 0; i < p.length; i++) {
            int cur = p[i] - 'a';
            if (i > 0 && p[i - 1] != (cur + 25) % 26 + 'a') len = 0;
            if (++ len > letters[cur]) { // len at end
                res += len - letters[cur]; // dif with previous max
                letters[cur] = len; // save max
            }
        }
        return res;
    }
}

 // #2
class Solution {
    public int findSubstringInWraproundString(String p) {
        char[] chars = p.toCharArray();
        int[] maxLen = new int[26];
        int n = chars.length;
        int i = 0;
        while (i < n) {
            int j = i + 1;
            while (j < n && areNeighbors(chars[j - 1], chars[j]))
                ++j;
            for (int q = i; q < j; ++q) {
                maxLen[chars[q] - 'a'] = Math.max(maxLen[chars[q] - 'a'], j - q);
            }
            i = j;
        }
        int ret = 0;
        for (i = 0; i < 26; ++i)
            ret += maxLen[i];
        return ret;
    }

    private static boolean areNeighbors(char a, char b) {
        return ((b - a + 26) % 26 == 1);
    }
}
