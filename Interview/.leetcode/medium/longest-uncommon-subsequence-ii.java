/**
 * Given a list of strings, you need to find the longest uncommon subsequence
 * among them. The longest uncommon subsequence is defined as the longest
 * subsequence of one of these strings and this subsequence should not be any
 * subsequence of the other strings.
 * 
 * A subsequence is a sequence that can be derived from one sequence by deleting
 * some characters without changing the order of the remaining elements.
 * Trivially, any string is a subsequence of itself and an empty string is a
 * subsequence of any string.
 * 
 * The input will be a list of strings, and the output needs to be the length of
 * the longest uncommon subsequence. If the longest uncommon subsequence doesn't
 * exist, return -1.
 * 
 * Example 1: Input: "aba", "cdc", "eae" Output: 3 Note:
 * 
 * All the given strings' lengths will not exceed 10. The length of the given
 * list will be in the range of [2, 50].
 */

class Solution {
    public int findLUSlength(String[] strs) {
        int n = strs.length, ret = -1;
        for (int i = 0; i < n; ++i) {
            boolean ok = true;
            int firstSize = strs[i].length();
            for (int j = 0; j < n; ++j) {
                if (i == j)
                    continue;
                int second = -1, secondSize = strs[j].length();
                for (int first = 0; first < firstSize; ++first) {
                    ++second;
                    while (second < secondSize && strs[i].charAt(first) != strs[j].charAt(second)) {
                        ++second;
                    }
                }
                if (second < secondSize) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ret = Math.max(ret, firstSize);
            }
        }
        return ret;
    }
}
