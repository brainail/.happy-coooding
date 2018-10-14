/**
 * Implement atoi which converts a string to an integer.
 * 
 * The function first discards as many whitespace characters as necessary until
 * the first non-whitespace character is found. Then, starting from this
 * character, takes an optional initial plus or minus sign followed by as many
 * numerical digits as possible, and interprets them as a numerical value.
 * 
 * The string can contain additional characters after those that form the
 * integral number, which are ignored and have no effect on the behavior of this
 * function.
 * 
 * If the first sequence of non-whitespace characters in str is not a valid
 * integral number, or if no such sequence exists because either str is empty or
 * it contains only whitespace characters, no conversion is performed.
 * 
 * If no valid conversion could be performed, a zero value is returned.
 * 
 * Note:
 * 
 * Only the space character ' ' is considered as whitespace character. Assume we
 * are dealing with an environment which could only store integers within the
 * 32-bit signed integer range: [−231, 231 − 1]. If the numerical value is out
 * of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is
 * returned.
 */
class Solution {
    public int myAtoi(String str) {
        str = str.trim();
        char[] num = str.toCharArray();
        int n = str.length();
        if (0 == n)
            return 0;
        if (num[0] != '+' && num[0] != '-' && !Character.isDigit(num[0])) {
            return 0;
        }
        int i = 0;
        int sign = 1;
        if (num[0] == '-') {
            sign = -1;
            ++i;
        } else if (num[0] == '+') {
            ++i;
        }
        if (i >= n || !Character.isDigit(num[i])) {
            return 0;
        }
        long res = 0;
        while (i < n && Character.isDigit(num[i])) {
            res = res * 10 + (num[i++] - '0');
            if (res > Integer.MAX_VALUE) {
                break;
            }
        }
        res *= sign;
        if (res < Integer.MIN_VALUE)
            return Integer.MIN_VALUE;
        if (res > Integer.MAX_VALUE)
            return Integer.MAX_VALUE;
        return (int) res;
    }
}
