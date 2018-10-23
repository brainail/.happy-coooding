/**
 * Given two non-negative integers num1 and num2 represented as strings, return
 * the product of num1 and num2, also represented as a string.
 * 
 * Example 1:
 * 
 * Input: num1 = "2", num2 = "3" Output: "6" Example 2:
 * 
 * Input: num1 = "123", num2 = "456" Output: "56088" Note:
 * 
 * The length of both num1 and num2 is < 110. Both num1 and num2 contain only
 * digits 0-9. Both num1 and num2 do not contain any leading zero, except the
 * number 0 itself. You must not use any built-in BigInteger library or convert
 * the inputs to integer directly.
 * 
 */
class Solution {
    public String multiply(String num1, String num2) {
        final int base = 10;
        char[] a = reverse(num1).toCharArray(), b = reverse(num2).toCharArray();
        int n = a.length, m = b.length;
        int[] c = new int[n + m];
        for (int j = 0, carry = 0; j < m; ++j) {
            int i = 0, y = b[j] - '0';
            while (i < n || carry > 0) {
                int x = i < n ? a[i] - '0' : 0;
                int z = x * y + carry;
                c[i + j] += z;
                carry = c[i + j] / base;
                c[i + j] %= base;
                ++i;
            }
        }
        int k = c.length - 1;
        while (k > 0 && c[k] == 0)
            --k;
        StringBuilder ret = new StringBuilder(k);
        for (; k >= 0; --k)
            ret.append(c[k]);
        return ret.toString();
    }

    private String reverse(String str) {
        return new StringBuilder(str).reverse().toString();
    }
}
