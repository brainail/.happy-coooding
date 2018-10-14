/**
 * Given two integers representing the numerator and denominator of a fraction,
 * return the fraction in string format.
 * 
 * If the fractional part is repeating, enclose the repeating part in
 * parentheses.
 * 
 * Example 1:
 * 
 * Input: numerator = 1, denominator = 2 Output: "0.5" Example 2:
 * 
 * Input: numerator = 2, denominator = 1 Output: "2" Example 3:
 * 
 * Input: numerator = 2, denominator = 3 Output: "0.(6)"
 */
class Solution {
    public String fractionToDecimal(int numerator, int denominator) {
        long nume = numerator, deno = denominator;
        int sign = ((nume < 0 ? 1 : 0) ^ (deno < 0 ? 1 : 0)) > 0 ? -1 : 1;
        StringBuilder result = new StringBuilder();
        nume = Math.abs(nume);
        deno = Math.abs(deno);
        if (sign < 0 && nume > 0)
            result.append("-");
        result.append(nume / deno);
        nume %= deno;
        if (nume > 0)
            result.append(".");
        HashMap<Long, Integer> period = new HashMap<>();
        List<Byte> fract = new ArrayList<>();
        int periodStart = -1;
        while (nume > 0) {
            period.put(nume, fract.size());
            nume *= 10;
            long x = nume / deno;
            nume %= deno;
            fract.add((byte) x);
            if (period.containsKey(nume)) {
                periodStart = period.get(nume);
                break;
            }
        }
        for (int i = 0; i < fract.size(); ++i) {
            if (i == periodStart)
                result.append("(");
            result.append(fract.get(i));
        }
        if (periodStart >= 0)
            result.append(")");
        return result.toString();
    }
}
