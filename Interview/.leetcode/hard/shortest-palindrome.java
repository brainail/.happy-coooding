/**
 * Given a string s, you are allowed to convert it to a palindrome by adding
 * characters in front of it. Find and return the shortest palindrome you can
 * find by performing this transformation.
 * 
 * Example 1:
 * 
 * Input: "aacecaaa" Output: "aaacecaaa" Example 2:
 * 
 * Input: "abcd" Output: "dcbabcd"
 */
class Solution {
    private int[] calcZf(final CharSequence s) {
        int n = s.length();
        int[] zf = new int[n];
        for (int i = 1, l = 0, r = 0; i < n; ++i) {
            if (i <= r)
                zf[i] = Math.min(r - i + 1, zf[i - l]);
            while (i + zf[i] < n && s.charAt(zf[i]) == s.charAt(i + zf[i]))
                ++zf[i];
            if (i + zf[i] - 1 > r) {
                l = i;
                r = i + zf[i] - 1;
            }
        }
        return zf;
    }

    public String shortestPalindrome(String s) {
        int n = s.length();
        if (0 == n)
            return s;
        StringBuilder sb = new StringBuilder(s);
        StringBuilder rsb = (new StringBuilder(s)).reverse();
        sb.append("#").append(rsb);
        int zf[] = calcZf(sb);
        for (int i = n + 1, l = n, size = zf.length; i < size; ++i, --l) {
            if (zf[i] >= l)
                return rsb.substring(0, i - n - 1) + s;
        }
        throw new IllegalArgumentException(";(");
    }
}