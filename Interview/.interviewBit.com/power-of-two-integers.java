/*
Given a positive integer which fits in a 32 bit signed integer, find if it can be expressed as A^P where P > 1 and A > 0. A and P both should be integers.

Example

Input : 4
Output : True  
as 2^2 = 4. 
*/

public class Solution {
    public boolean isPower(int n) {
        if (n <= 1) return true;
        for (int x = 2; x - 1 <= (int) Math.sqrt(n); ++ x) {
            long pow = x;
            while (pow <= n) {
                pow *= x;
                if (pow == n) {
                    return true;
                }
            }
        }
        return false;
    }
}
