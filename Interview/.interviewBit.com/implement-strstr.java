public class Solution {
    public int strStr(final String haystack, final String needle) {
        if (null == needle || 0 == needle.length()) {
            return -1;
        }
        if (null == haystack || 0 == haystack.length()) {
            return -1;
        }
        
        final int needleLength = needle.length();
        int [] prefix = new int [needleLength];
        int p = 0;
        for (int i = 1; i < needleLength; ++ i) {
            while (p > 0 && needle.charAt(i) != needle.charAt(p)) {
                p = prefix [p - 1];
            }
            p += needle.charAt(i) == needle.charAt(p) ? 1 : 0;
            prefix [i] = p;
        }
        
        final int haystackLength = haystack.length();
        p = 0;
        for (int i = 0; i < haystackLength; ++ i) {
            while (p > 0 && haystack.charAt(i) != needle.charAt(p)) {
                p = prefix [p - 1];
            }
            p += haystack.charAt(i) == needle.charAt(p) ? 1 : 0;
            if (p == needleLength) {
                return i - needleLength + 1;
            }
        }
        
        return -1;
    }
}
