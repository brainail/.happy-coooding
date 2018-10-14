/*
You are given a read only array of n integers from 1 to n.

Each integer appears exactly once except A which appears twice and B which is missing.

Return A and B.

Note: Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Note that in your output A should precede B.

Example:

Input:[3 1 2 5 3] 

Output:[3, 4] 

A = 3, B = 4
*/

public class Solution {
    // DO NOT MODIFY THE LIST
    public ArrayList<Integer> repeatedNumber(final List<Integer> arr) {
        int n = arr.size();
        int all = 0;
        for (final Integer x : arr) all ^= x;
        for (int x = 1; x <= n; ++ x) all ^= x;
        final int helpBit = all & ~(all - 1);
        int A = 0, B = 0;
        for (final Integer x : arr) {
            if ((x & helpBit) > 0) {
                A ^= x; 
            } else {
                B ^= x; 
            }
        }
        for (int x = 1; x <= n; ++ x) {
            if ((x & helpBit) > 0) {
                A ^= x; 
            } else {
                B ^= x; 
            }
        }
        for (final Integer x : arr) {
            if (B == x) {
                final int buff = A;
                A = B;
                B = buff;
                break;
            }
        }
        return new ArrayList<Integer> (Arrays.asList(A, B));
    }
}
