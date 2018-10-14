/**
 * Validate if a given string is numeric.
 * 
 * Some examples: "0" => true " 0.1 " => true "abc" => false "1 a" => false
 * "2e10" => true
 */
class Solution {
    public boolean isNumber(String s) {
        boolean result = true;
        try {
            double x = Double.valueOf(s);
            if (s.charAt(s.length() - 1) == 'd' || s.charAt(s.length() - 1) == 'D' || s.charAt(s.length() - 1) == 'f'
                    || s.charAt(s.length() - 1) == 'F') {
                result = false;
            }
        } catch (Throwable error) {
            result = false;
        }
        return result;
    }
}