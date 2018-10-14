/**
 * Given two non-negative integers num1 and num2 represented as string, return
 * the sum of num1 and num2.
 * 
 * Note:
 * 
 * The length of both num1 and num2 is < 5100. Both num1 and num2 contains only
 * digits 0-9. Both num1 and num2 does not contain any leading zero. You must
 * not use any built-in BigInteger library or convert the inputs to integer
 * directly.
 * 
 */
class Solution {
    public String addStrings(String a, String b) {
        final StringBuilder numa = reverse(a);
        int lena = numa.length();
        final StringBuilder numb = reverse(b);
        int lenb = numb.length();
        final StringBuilder numr = new StringBuilder(Math.max(lena, lenb));
        for (int i = 0, j = 0, carry = 0; i < lena || j < lenb || carry > 0; ++i, ++j) {
            int da = i < lena ? numa.charAt(i) - '0' : 0;
            int db = j < lenb ? numb.charAt(j) - '0' : 0;
            int dr = da + db + carry;
            numr.append(dr % 10);
            carry = dr / 10;
        }
        return numr.reverse().toString();
    }

    private StringBuilder reverse(String s) {
        return new StringBuilder(s).reverse();
    }
}
