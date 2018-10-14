package utilities.combinatorics;

import static java.lang.Math.*;

// Method 1b: recursive function
// main () {
// subsets( 0, {} );
// }
//
// subsets ( int i, Subset s ) {
// if( i == N ){
// return doSomethingWithTheBuiltSubset( s );
// }
// return min(subsets( i+1, s ), subsets( i+1, s + element(i) ));
// }
public class AllSubsetsRecursiveLoopVoid
{
    private static int n;
    private static int[] cal = new int[5], A = new int[5], B = new int[5],
                    C = new int[5];

    public static int check_subsets(int i, int cals, int a, int b, int c)
    {
        // --- Made a choice for all items?
        if (i == n) {
            // print completed subset (ie of size n) under consideration
            // System.out.println(i + ":  " + cals + " " + a + " " + b + " " +
            // c);
            if (a >= 100 && b >= 100 && c >= 100) {
                return cals;
            } else {
                return 20 * 100 + 1; // legal max
            }
        }

        // -- Either leave this one out or take it in.
        return min(check_subsets(i + 1, cals, a, b, c),
            check_subsets(i + 1, cals + cal[i], a + A[i], b + B[i], c + C[i]));
    }

    public static void main(String[] args)
    {
        n = 5;
        int[][] array = new int[n][4];
        // { calories, vitaminA, B, C }
        array[0] = new int[] { 28, 100, 33, 98 };
        array[1] = new int[] { 23, 100, 33, 1 };
        array[2] = new int[] { 6, 100, 33, 1 };
        array[3] = new int[] { 42, 100, 40, 1 };
        array[4] = new int[] { 496, 100, 100, 100 };

        // extract columns separately from 2D array
        for (int i = 0; i < array.length; i++) {
            cal[i] = array[i][0];
            A[i] = array[i][1];
            B[i] = array[i][2];
            C[i] = array[i][3];
        }

        // --- Answer.
        System.out.println("Number of calories: "
                        + check_subsets(0, 0, 0, 0, 0));
    }
}
