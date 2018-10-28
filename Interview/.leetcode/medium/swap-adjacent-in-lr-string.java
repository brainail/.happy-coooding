/**
 * In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL", a
 * move consists of either replacing one occurrence of "XL" with "LX", or
 * replacing one occurrence of "RX" with "XR". Given the starting string start
 * and the ending string end, return True if and only if there exists a sequence
 * of moves to transform one string to the other.
 * 
 * Example:
 * 
 * Input: start = "RXXLRXRXL", end = "XRLXXRRLX" Output: True Explanation: We
 * can transform start to end following these steps: RXXLRXRXL -> XRXLRXRXL ->
 * XRLXRXRXL -> XRLXXRRXL -> XRLXXRRLX Note:
 * 
 * 1 <= len(start) = len(end) <= 10000. Both start and end will only consist of
 * characters in {'L', 'R', 'X'}.
 */
class Solution {
    public boolean canTransform(String start, String end) {
        if (!removeX(start).equals(removeX(end)))
            return false;
        int i = start.length() - 1, j = end.length() - 1;
        while (i >= 0 && j >= 0) {
            while (i >= 0 && start.charAt(i) != 'X') --i;
            while (j >= 0 && end.charAt(j) != 'X') --j;
            if (i < 0 || j < 0) break;
            int countL = 0, countR = 0;
            for (int p = Math.min(i, j); p <= Math.max(i, j); ++p) {
                countL += start.charAt(p) == 'L' ? 1 : 0;
                countR += start.charAt(p) == 'R' ? 1 : 0;
            }
            if (i < j && countR > 0) return false;
            if (i > j && countL > 0) return false;
            --i;
            --j;
        }
        return true;
    }

    private String removeX(String text) {
        int size = text.length();
        StringBuilder textNoX = new StringBuilder(size);
        for (int i = 0; i < size; ++i)
            if (text.charAt(i) != 'X')
                textNoX.append(text.charAt(i));
        return textNoX.toString();
    }
}
