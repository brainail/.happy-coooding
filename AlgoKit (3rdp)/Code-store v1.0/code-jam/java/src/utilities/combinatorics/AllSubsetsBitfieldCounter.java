package utilities.combinatorics;

import static java.lang.Math.*;

public class AllSubsetsBitfieldCounter
{
    /**
     * finds min(calories) & vitamins(A,B,C) >= 100
     * 
     * @param args
     */
    public static void main(String[] args)
    {
        int n = 5;
        int[][] array = new int[n][4];
        // { calories, vitaminA, B, C }
        array[0] = new int[] { 28, 100, 33, 98 };
        array[1] = new int[] { 23, 100, 33, 1 };
        array[2] = new int[] { 6, 100, 33, 1 };
        array[3] = new int[] { 42, 100, 40, 1 };
        array[4] = new int[] { 496, 100, 100, 100 };

        int best = Integer.MAX_VALUE;
        // iteratively traverses through from 0 to 2^n - 1
        for (int B = 0; B < (1 << n); ++B) {

            int[] sum = new int[4]; // sum of each column

            // for each bit in this single permutation
            for (int b = 0; b < n; ++b) {
                if ((B & (1 << b)) != 0) {
                    // if bit is set => include choice, ie. array[b]

                    // compute sum of each vitamin corresponding to this row
                    for (int j = 0; j < 4; ++j) {
                        sum[j] += array[b][j];
                    }
                }
            }
            if (sum[1] >= 100 && sum[2] >= 100 && sum[3] >= 100) {
                best = min(best, sum[0]);
            }
        }

        System.out.println("Number of calories: " + best);
    }
}
