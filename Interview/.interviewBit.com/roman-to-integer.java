public class Solution {
    public int romanToInt(String romanNumber) {
        final int [] intItem = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        final String [] romanItem = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        int intNumber = 0;
        
        for (int i = 0, length = romanNumber.length(); i < length; ) {
            for (int t = 0, size = romanItem.length; t < size; ++ t) {
                if (romanNumber.charAt(i) == romanItem [t].charAt(0)) {
                    boolean match = true;
                    if (2 == romanItem [t].length()) {
                        if (i + 1 >= length || romanNumber.charAt(i + 1) != romanItem [t].charAt(1)) {
                            match = false;
                        }
                    }
                    
                    if (match) {
                        intNumber += intItem [t];
                        i += romanItem [t].length();
                        break;
                    }
                }
            }
        }
        
        return intNumber;
    }
}
