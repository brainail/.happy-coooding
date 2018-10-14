public class Solution {
    public static String nextPalindrome(String num) {
        int len = num.length();
        String left = num.substring(0, len / 2);
        String middle = num.substring(len / 2, len - len / 2);
        String right = num.substring(len - len / 2);
        if (right.compareTo(reverse(left)) < 0) return left + middle + reverse(left);
        String next = new BigInteger(left + middle).add(BigInteger.ONE).toString();
        return next.substring(0, left.length() + middle.length()) + reverse(next).substring(middle.length());
    }

    private static String reverse(String s) {
        return new StringBuilder(s).reverse().toString();
    }

    @Test
    public void testNextPalindrome() {
        // assertEquals("5", nextPalindrome("4"));
        // assertEquals("11", nextPalindrome("9"));
        // assertEquals("22", nextPalindrome("15"));
        // assertEquals("101", nextPalindrome("99"));
        // assertEquals("151", nextPalindrome("149"));
        // assertEquals("123454321", nextPalindrome("123450000"));
        // assertEquals("123464321", nextPalindrome("123454322"));
    }
}
