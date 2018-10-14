package utilities;

import static utilities.Convert.*;

import java.util.*;

public class Debug
{
    public static <T> void print2DArray(T[][] array, String delimiter)
    {
        for (int i = 0; i < array.length; i++) {
            for (int j = 0; j < array[0].length; j++) {
                System.out.print(array[i][j] + delimiter);
            }
            System.out.print("\n");
        }
    }

    public static void assertTrue(Boolean b)
    {
        if (!b) {
            throw new RuntimeException("Assertion failed: " + b.toString());
        }
    }

    public static <T> void assertEqual(T item1, T item2)
    {
        if (!item1.equals(item2)) {
            throw new RuntimeException("Assertion failed: " + item1 + "!="
                            + item2);
        }
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // wrapper methods for Arrays.deepToString()
    // ////////////////////////////////////////////////////////////////////////////////////
    public static void debug(Object... os)
    {
        System.err.println(Arrays.deepToString(os));
    }

    public static String deepToString(boolean[] array)
    {
        return Arrays.deepToString(toObject(array));
    }

    public static String deepToString(byte[] array)
    {
        return Arrays.deepToString(toObject(array));
    }

    public static String deepToString(int[] array)
    {
        return Arrays.deepToString(toObject(array));
    }

    public static String deepToString(long[] array)
    {
        return Arrays.deepToString(toObject(array));
    }

    public static String deepToString(double[] array)
    {
        return Arrays.deepToString(toObject(array));
    }

    public static String deepToString(char[] array)
    {
        return Arrays.deepToString(toObject(array));
    }
}
