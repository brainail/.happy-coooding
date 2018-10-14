/**
 * Given two binary strings, return their sum (also a binary string).
 * 
 * The input strings are both non-empty and contains only characters 1 or 0.
 * 
 * Example 1:
 * 
 * Input: a = "11", b = "1" Output: "100" Example 2:
 * 
 * Input: a = "1010", b = "1011" Output: "10101"
 */
class Solution {
    public String addBinary(String a, String b) {
        final StringBuilder numa = reverse(a);
        int lena = numa.length();
        final StringBuilder numb = reverse(b);
        int lenb = numb.length();
        final StringBuilder numr = new StringBuilder(Math.max(lena, lenb));
        for (int i = 0, j = 0, carry = 0; i < lena || j < lenb || carry > 0; ++i, ++j) {
            int da = i < lena ? numa.charAt(i) - '0' : 0;
            int db = j < lenb ? numb.charAt(j) - '0' : 0;
            int dr = da + db + carry;
            numr.append(dr % 2);
            carry = dr / 2;
        }
        return numr.reverse().toString();
    }

    private StringBuilder reverse(String s) {
        return new StringBuilder(s).reverse();
    }
}
