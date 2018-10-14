public class Solution {
    public String intToRoman(int intNumber) {
        final int [] intItem = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        final String [] romanItem = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        final StringBuilder romanNumber = new StringBuilder();
    
        for (int i = 0, length = intItem.length; i < length; ++ i) {
            while (intItem [i] <= intNumber) {
                intNumber -= intItem [i];
                romanNumber.append(romanItem [i]);
            }
        }
        
        return romanNumber.toString();
    }
}
