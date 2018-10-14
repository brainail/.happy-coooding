package utilities.math;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.DecimalFormat;

/*
 In combinatorics, the nth Bell number, named after Eric Temple Bell, is the
 number of partitions of a set with n members, or equivalently, the number of
 equivalence relations on it.

 Partitions of a set

 In general, Bn is the number of partitions of a set of size n. A partition of
 a set S is defined as a set of nonempty, pairwise disjoint subsets of S whose
 union is S. For example, B3 = 5 because the 3-element set {a, b, c} can be
 partitioned in 5 distinct ways: { {a}, {b}, {c} } { {a}, {b, c} } { {b}, {a,
 c} } { {c}, {a, b} } { {a, b, c} }. B0 is 1 because there is exactly one
 partition of the empty set. Every member of the empty set is a nonempty set
 (that is vacuously true), and their union is the empty set. Therefore, the
 empty set is the only partition of itself. Note that, as suggested by the set
 notation above, we consider neither the order of the partitions nor the order
 of elements within each partition. This means the following partitionings are
 all considered identical: { {b}, {a, c} } { {a, c}, {b} } { {b}, {c, a} } {
 {c, a}, {b} }.

 Another view of Bell numbers

 Bell numbers can also be viewed as the number of distinct possible ways of
 putting n distinguishable balls into one or more indistinguishable boxes. For
 example, let us suppose n is 3. We have three balls, which we will label a, b,
 and c, and three boxes. If the boxes can not be distinguished from each other,
 there are five ways of putting the balls in the boxes: All three balls go in
 to one box. Since the boxes are anonymous, this is only considered one
 combination. a goes in to one box; b and c go in to another box. b goes in to
 one box; a and c go in to another box. c goes in to one box; a and b go in to
 another box. Each ball goes in to its own box.
 */

public class Bell_Numbers
{

    static double[] dp = new double[1000000];
    static double[] dpB = new double[1000000];

    static double factorial(int n)
    {
        if (dp[n] != Double.MAX_VALUE) return dp[n];
        return dp[n] = n * factorial(n - 1);
    }

    static double combination(int n, int r)
    {
        return factorial(n) / (factorial(r) * factorial(n - r));
    }

    static double bell(int n)
    {
        if (dpB[n] != Double.MAX_VALUE) return dpB[n];
        double acum = 0;
        for (int i = 0; i <= n - 1; i++) {
            acum += combination(n - 1, i) * bell(i);
        }
        return dpB[n] = acum;
    }

    public static void main(String[] args)
        throws NumberFormatException,
            IOException
    {
        for (int i = 0; i < 1000000; i++) {
            dp[i] = Double.MAX_VALUE;
            dpB[i] = Double.MAX_VALUE;
        }
        dp[0] = 1;
        dpB[0] = 1;
        dpB[1] = 1;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            int n = Integer.parseInt(br.readLine());
            if (n == 0) return;
            System.out.println(n
                            + " "
                            + (DecimalFormat.getNumberInstance()
                                            .format(bell(n)) + "").replace(",",
                                ""));
        }
    }

}
