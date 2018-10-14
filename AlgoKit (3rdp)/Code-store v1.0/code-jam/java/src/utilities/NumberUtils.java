package utilities;

import static java.lang.Math.*;
import static utilities.Constants.*;

import java.util.*;

import utilities.struct.*;

/**
 * <p>
 * Provides extra functionality for Java Number classes.
 * </p>
 * 
 * @author Apache Software Foundation
 * @author <a href="mailto:rand_mcneely@yahoo.com">Rand McNeely</a>
 * @author <a href="mailto:steve.downey@netfolio.com">Steve Downey</a>
 * @author Eric Pugh
 * @author Phil Steitz
 * @author Matthew Hawthorne
 * @author <a href="mailto:ggregory@seagullsw.com">Gary Gregory</a>
 * @author <a href="mailto:fredrik@westermarck.com">Fredrik Westermarck</a>
 * @since 2.0
 * @version $Id: NumberUtils.java 916081 2010-02-25 01:28:13Z niallp $
 */
public class NumberUtils
{
    /** Reusable Long constant for zero. */
    public static final Long LONG_ZERO = new Long(0L);
    /** Reusable Long constant for one. */
    public static final Long LONG_ONE = new Long(1L);
    /** Reusable Long constant for minus one. */
    public static final Long LONG_MINUS_ONE = new Long(-1L);
    /** Reusable Integer constant for zero. */
    public static final Integer INTEGER_ZERO = new Integer(0);
    /** Reusable Integer constant for one. */
    public static final Integer INTEGER_ONE = new Integer(1);
    /** Reusable Integer constant for minus one. */
    public static final Integer INTEGER_MINUS_ONE = new Integer(-1);
    /** Reusable Short constant for zero. */
    public static final Short SHORT_ZERO = new Short((short) 0);
    /** Reusable Short constant for one. */
    public static final Short SHORT_ONE = new Short((short) 1);
    /** Reusable Short constant for minus one. */
    public static final Short SHORT_MINUS_ONE = new Short((short) -1);
    /** Reusable Byte constant for zero. */
    public static final Byte BYTE_ZERO = Byte.valueOf((byte) 0);
    /** Reusable Byte constant for one. */
    public static final Byte BYTE_ONE = Byte.valueOf((byte) 1);
    /** Reusable Byte constant for minus one. */
    public static final Byte BYTE_MINUS_ONE = Byte.valueOf((byte) -1);
    /** Reusable Double constant for zero. */
    public static final Double DOUBLE_ZERO = new Double(0.0d);
    /** Reusable Double constant for one. */
    public static final Double DOUBLE_ONE = new Double(1.0d);
    /** Reusable Double constant for minus one. */
    public static final Double DOUBLE_MINUS_ONE = new Double(-1.0d);
    /** Reusable Float constant for zero. */
    public static final Float FLOAT_ZERO = new Float(0.0f);
    /** Reusable Float constant for one. */
    public static final Float FLOAT_ONE = new Float(1.0f);
    /** Reusable Float constant for minus one. */
    public static final Float FLOAT_MINUS_ONE = new Float(-1.0f);

    /**
     * Solves the quadratic equation.
     * 
     * @return a pair containing the roots of the equation a*x<sup>2</sup> + b*x
     *         + c = 0 with the lesser of the two roots in
     *         <code>result.d1</code>. If no real roots exist, the returned pair
     *         will contain <code>NaN</code> for both values.
     * 
     * @see java.lang.Double#NaN
     **/
    public static Pair<Double, Double> quadraticSolution(
        double a,
        double b,
        double c)
    {
        if (a == 0.0) {
            if (b == 0.0) {
                return Pair.of(Double.NaN);
            } else {
                return Pair.of(-c / b);
            }
        } else {
            double discriminant = (b * b) - (4.0 * a * c);
            if (discriminant < 0.0) {
                return Pair.of(Double.NaN);
            } else {
                double sqrt = Math.sqrt(discriminant);
                double twoA = 2.0 * a;
                double lesserNum = -b - sqrt;
                double greaterNum = -b + sqrt;
                if (a > 0) {
                    return Pair.of(lesserNum / twoA, greaterNum / twoA);
                } else {
                    return Pair.of(greaterNum / twoA, lesserNum / twoA);
                }
            }
        }
    }

    /**
     * Polynomial function to compute sqrt(a^2 + b^2) without under/overflow
     * 
     * @param aa
     * @param bb
     * @return
     */
    public static double hypothenuse(double aa, double bb)
    {
        double cc = 0.0D, ratio = 0.0D;
        double amod = Math.abs(aa);
        double bmod = Math.abs(bb);

        if (amod == 0.0D) {
            cc = bmod;
        } else {
            if (bmod == 0.0D) {
                cc = amod;
            } else {
                if (amod <= bmod) {
                    ratio = amod / bmod;
                    cc = bmod * Math.sqrt(1.0D + ratio * ratio);
                } else {
                    ratio = bmod / amod;
                    cc = amod * Math.sqrt(1.0D + ratio * ratio);
                }
            }
        }
        return cc;
    }

    public static boolean isEqual(double a, double b)
    {
        if (abs(a - b) < DBL_EPSILON) {
            return true;
        }
        return false;
    }

    /**
     * optimised function to determine if a given n is prime
     * 
     * @param n
     * @return boolean
     */
    public static boolean isPrime(int n)
    {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        int m = (int) ceil(sqrt(n));
        for (int i = 3; i <= m; i += 2)
            if (n % i == 0) return false;
        return true;
    }

    /**
     * implements Sieve of Eratosthenes to find all the prime numbers within a
     * given range
     * 
     * @param n
     * @return boolean[]
     */
    public static boolean[] sieve(int n)
    {
        boolean[] prime = new boolean[n + 1];
        Arrays.fill(prime, true);
        prime[0] = false;
        prime[1] = false;
        int m = (int) ceil(sqrt(n));
        for (int i = 2; i <= m; i++)
            if (prime[i]) for (int k = i * i; k <= n; k += i)
                prime[k] = false;

        return prime;
    }

    /**
     * implements "binary gcd" method for finding GCD(a,b)
     * can be applied to solve linear Diophantine equations
     * ie. of form ax + by = c, with integer coefficients
     * 
     * pre: assume that a and b cannot both be 0
     * 
     * @param a
     * @param b
     * @return
     */
    public static int GCD(int a, int b)
    {
        if (a == 0 & b == 0)
            throw new RuntimeException("GCD: a & b cannot both be 0");
        if (a == 0) return b;
        if (b == 0) return a;
        return Fraction.greatestCommonDivisor(a, b);
    }

    /**
     * uses GCD(a,b) to find LCM
     * 
     * @param a
     * @param b
     * @return
     */
    public static int LCM(int a, int b)
    {
        return b * a / GCD(a, b);
    }

    /**
     * finds the maximum in given vararg input x
     * 
     * pre: input int parameter x cannot be empty
     * 
     * @param x
     * @return
     */
    public static byte max(byte... x)
    {
        if (x == null || x.length == 0)
            throw new RuntimeException("max: supplied x cannot be empty!");

        byte maxValue = x[0];
        for (byte value : x) {
            if (value > maxValue) {
                maxValue = value;
            }
        }
        return maxValue;
    }

    public static double max(double... x)
    {
        if (x == null || x.length == 0)
            throw new RuntimeException("max: supplied x cannot be empty!");

        double maxValue = x[0];
        for (double value : x) {
            if (value > maxValue) {
                maxValue = value;
            }
        }
        return maxValue;
    }

    public static int max(int... x)
    {
        if (x == null || x.length == 0)
            throw new RuntimeException("max: supplied x cannot be empty!");

        int maxValue = x[0];
        for (int value : x) {
            if (value > maxValue) {
                maxValue = value;
            }
        }
        return maxValue;
    }

    public static long max(long... x)
    {
        if (x == null || x.length == 0)
            throw new RuntimeException("max: supplied x cannot be empty!");

        long maxValue = x[0];
        for (long value : x) {
            if (value > maxValue) {
                maxValue = value;
            }
        }
        return maxValue;
    }

    /**
     * finds the minimum in given vararg input x
     * 
     * pre: input int parameter x cannot be empty
     * 
     * @param x
     * @return
     */
    public static byte min(byte... x)
    {
        if (x == null || x.length == 0)
            throw new RuntimeException("min: supplied x cannot be empty!");

        byte minValue = x[0];
        for (byte value : x) {
            if (value > minValue) {
                minValue = value;
            }
        }
        return minValue;
    }

    public static double min(double... x)
    {
        if (x == null || x.length == 0)
            throw new RuntimeException("min: supplied x cannot be empty!");

        double minValue = x[0];
        for (double value : x) {
            if (value > minValue) {
                minValue = value;
            }
        }
        return minValue;
    }

    public static int min(int... x)
    {
        if (x == null || x.length == 0)
            throw new RuntimeException("min: supplied x cannot be empty!");

        int minValue = x[0];
        for (int value : x) {
            if (value > minValue) {
                minValue = value;
            }
        }
        return minValue;
    }

    public static long min(long... x)
    {
        if (x == null || x.length == 0)
            throw new RuntimeException("min: supplied x cannot be empty!");

        long minValue = x[0];
        for (long value : x) {
            if (value > minValue) {
                minValue = value;
            }
        }
        return minValue;
    }
}
