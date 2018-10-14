import static java.lang.Math.*;
import static java.util.Arrays.*;
import static utilities.Constants.*;
import static utilities.IOUtils.*;

import java.io.*;
import java.util.*;

public class A
{
    private static String PROBLEM_NAME = "/Users/lwy08/Downloads/A.in";

    private static long[] grid;

    private static void run()
        throws Exception
    {
        grid = new long[10000005];
        for (long i = 10000005 - 1; i > 0; i--) {
            long combo = 1;
            for (int j = 1; j <= i; j++) {
                combo *= (i + 1 - j);
                combo /= j;
                if (combo > 10000005) break;
                grid[(int) combo] = i;
            }
        }

        /* INPUT */
        cases = INT();
        for (cc = 1; cc <= cases; cc++) {
            // for each case - read input
            long S = LONG();
            long T = 10000005 * 10;
            for (int i = 1; i * i <= S; i++) {
                if (S % i == 0) {
                    T = min(T, grid[i] + grid[(int) (S / i)]);
                }
            }

            println(cc, String.format("%s", T));
        } // end for each case
    } // end run()

    public static void main(String[] args)
        throws Exception
    {
        long start = System.currentTimeMillis();
        Locale.setDefault(Locale.US);
        init(PROBLEM_NAME);
        run();
        close();
        System.err.println(String.format("*** Total time: %.3f seconds ***",
            (System.currentTimeMillis() - start) / 1000.0));
    }
}
