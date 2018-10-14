/**
 * Given an input string, reverse the string word by word.
 * 
 * Example:
 * 
 * Input: "the sky is blue", Output: "blue is sky the". Note:
 * 
 * A word is defined as a sequence of non-space characters. Input string may
 * contain leading or trailing spaces. However, your reversed string should not
 * contain leading or trailing spaces. You need to reduce multiple spaces
 * between two words to a single space in the reversed string. Follow up: For C
 * programmers, try to solve it in-place in O(1) space.
 */
public class Solution {
    private void reversePart(StringBuilder text, int i, int j) {
        for (int p = i; j - 2 * p + i > 0; ++p) {
            char buff = text.charAt(p);
            text.setCharAt(p, text.charAt(j - (p - i)));
            text.setCharAt(j - (p - i), buff);
        }
    }

    public String reverseWords(String s) {
        s = s.trim();
        int len = s.length();
        StringBuilder text = new StringBuilder(len);
        for (int i = 0; i < len; ++i) {
            boolean isPreviousAlphabet = i > 0 && !Character.isSpace(s.charAt(i - 1));
            if (!Character.isSpace(s.charAt(i)) || isPreviousAlphabet)
                text.append(s.charAt(i));
        }
        int size = text.length();
        reversePart(text, 0, size - 1);
        System.out.println(text.toString());
        int i = 0;
        while (i < size) {
            if (Character.isSpace(text.charAt(i))) {
                ++i;
                continue;
            }
            int j = i;
            while (j + 1 < size && !Character.isSpace(text.charAt(j + 1)))
                ++j;
            reversePart(text, i, j);
            i = j + 1;
        }
        return text.toString();
    }
}
