package utilities;

import static java.lang.Math.*;
import static utilities.Constants.*;

import java.lang.reflect.*;

/**
 * <p>
 * Operations on arrays, primitive arrays (like <code>int[]</code>) and
 * primitive wrapper arrays (like <code>Integer[]</code>).
 * </p>
 * 
 * <p>
 * This class tries to handle <code>null</code> input gracefully. An exception
 * will not be thrown for a <code>null</code> array input. However, an Object
 * array that contains a <code>null</code> element may throw an exception. Each
 * method documents its behaviour.
 * </p>
 * 
 * <p>
 * #ThreadSafe#
 * </p>
 * 
 * @author Apache Software Foundation
 * @author Moritz Petersen
 * @author <a href="mailto:fredrik@westermarck.com">Fredrik Westermarck</a>
 * @author Nikolay Metchev
 * @author Matthew Hawthorne
 * @author Tim O'Brien
 * @author Pete Gieser
 * @author Gary Gregory
 * @author <a href="mailto:equinus100@hotmail.com">Ashwin S</a>
 * @author Maarten Coene
 * @author <a href="mailto:levon@lk.otherinbox.com">Levon Karayan</a>
 * @since 2.0
 * @version $Id: ArrayUtils.java 918868 2010-03-04 06:22:16Z bayard $
 */
public class ArrayUtils
{
    /**
     * <pre>
     *  Performs a pairwise xor on all elements of the given array of booleans
     * </pre>
     */
    public static boolean xorAll(boolean... array)
    {
        if (array == null || array.length == 0)
            throw new IllegalArgumentException(
                            "xorAll: array cannot be null or empty");
        boolean result = array[0];
        for (int i = 1; i < array.length; i++) {
            result ^= array[i];
        }
        return result;
    }

    public static boolean isAllZeros(int[] array)
    {
        for (int i = 0; i < array.length; i++) {
            if (array[i] != 0) {
                return false;
            }
        }
        return true;
    }

    public static boolean isWithinBounds(int[] array, int i)
    {
        try {
            array[i] += 0;
        } catch (ArrayIndexOutOfBoundsException e) {
            return false;
        }
        return true;
    }

    public static boolean isWithinBounds(int[][] array, int x, int y)
    {
        try {
            array[x][y] += 0;
        } catch (ArrayIndexOutOfBoundsException e) {
            return false;
        }
        return true;
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // addAll(array1, array2)
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Adds all the elements of the given arrays into a new array.
     * </p>
     * <p>
     * The new array contains all of the element of <code>array1</code> followed
     * by all of the elements <code>array2</code>. When an array is returned, it
     * is always a new array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.addAll(array1, null)   = cloned copy of array1
     * ArrayUtils.addAll(null, array2)   = cloned copy of array2
     * ArrayUtils.addAll([], [])         = []
     * </pre>
     * 
     * @param array1 the first array whose elements are added to the new array.
     * @param array2 the second array whose elements are added to the new array.
     * @return The new boolean[] array.
     * @since 2.1
     */
    public static boolean[] addAll(boolean[] array1, boolean... array2)
    {
        if (array1 == null) {
            return clone(array2);
        } else if (array2 == null) {
            return clone(array1);
        }
        boolean[] joinedArray = new boolean[array1.length + array2.length];
        System.arraycopy(array1, 0, joinedArray, 0, array1.length);
        System.arraycopy(array2, 0, joinedArray, array1.length, array2.length);
        return joinedArray;
    }

    /**
     * <p>
     * Adds all the elements of the given arrays into a new array.
     * </p>
     * <p>
     * The new array contains all of the element of <code>array1</code> followed
     * by all of the elements <code>array2</code>. When an array is returned, it
     * is always a new array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.addAll(array1, null)   = cloned copy of array1
     * ArrayUtils.addAll(null, array2)   = cloned copy of array2
     * ArrayUtils.addAll([], [])         = []
     * </pre>
     * 
     * @param array1 the first array whose elements are added to the new array.
     * @param array2 the second array whose elements are added to the new array.
     * @return The new char[] array.
     * @since 2.1
     */
    public static char[] addAll(char[] array1, char... array2)
    {
        if (array1 == null) {
            return clone(array2);
        } else if (array2 == null) {
            return clone(array1);
        }
        char[] joinedArray = new char[array1.length + array2.length];
        System.arraycopy(array1, 0, joinedArray, 0, array1.length);
        System.arraycopy(array2, 0, joinedArray, array1.length, array2.length);
        return joinedArray;
    }

    /**
     * <p>
     * Adds all the elements of the given arrays into a new array.
     * </p>
     * <p>
     * The new array contains all of the element of <code>array1</code> followed
     * by all of the elements <code>array2</code>. When an array is returned, it
     * is always a new array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.addAll(array1, null)   = cloned copy of array1
     * ArrayUtils.addAll(null, array2)   = cloned copy of array2
     * ArrayUtils.addAll([], [])         = []
     * </pre>
     * 
     * @param array1 the first array whose elements are added to the new array.
     * @param array2 the second array whose elements are added to the new array.
     * @return The new byte[] array.
     * @since 2.1
     */
    public static byte[] addAll(byte[] array1, byte... array2)
    {
        if (array1 == null) {
            return clone(array2);
        } else if (array2 == null) {
            return clone(array1);
        }
        byte[] joinedArray = new byte[array1.length + array2.length];
        System.arraycopy(array1, 0, joinedArray, 0, array1.length);
        System.arraycopy(array2, 0, joinedArray, array1.length, array2.length);
        return joinedArray;
    }

    /**
     * <p>
     * Adds all the elements of the given arrays into a new array.
     * </p>
     * <p>
     * The new array contains all of the element of <code>array1</code> followed
     * by all of the elements <code>array2</code>. When an array is returned, it
     * is always a new array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.addAll(array1, null)   = cloned copy of array1
     * ArrayUtils.addAll(null, array2)   = cloned copy of array2
     * ArrayUtils.addAll([], [])         = []
     * </pre>
     * 
     * @param array1 the first array whose elements are added to the new array.
     * @param array2 the second array whose elements are added to the new array.
     * @return The new int[] array.
     * @since 2.1
     */
    public static int[] addAll(int[] array1, int... array2)
    {
        if (array1 == null) {
            return clone(array2);
        } else if (array2 == null) {
            return clone(array1);
        }
        int[] joinedArray = new int[array1.length + array2.length];
        System.arraycopy(array1, 0, joinedArray, 0, array1.length);
        System.arraycopy(array2, 0, joinedArray, array1.length, array2.length);
        return joinedArray;
    }

    /**
     * <p>
     * Adds all the elements of the given arrays into a new array.
     * </p>
     * <p>
     * The new array contains all of the element of <code>array1</code> followed
     * by all of the elements <code>array2</code>. When an array is returned, it
     * is always a new array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.addAll(array1, null)   = cloned copy of array1
     * ArrayUtils.addAll(null, array2)   = cloned copy of array2
     * ArrayUtils.addAll([], [])         = []
     * </pre>
     * 
     * @param array1 the first array whose elements are added to the new array.
     * @param array2 the second array whose elements are added to the new array.
     * @return The new long[] array.
     * @since 2.1
     */
    public static long[] addAll(long[] array1, long... array2)
    {
        if (array1 == null) {
            return clone(array2);
        } else if (array2 == null) {
            return clone(array1);
        }
        long[] joinedArray = new long[array1.length + array2.length];
        System.arraycopy(array1, 0, joinedArray, 0, array1.length);
        System.arraycopy(array2, 0, joinedArray, array1.length, array2.length);
        return joinedArray;
    }

    /**
     * <p>
     * Adds all the elements of the given arrays into a new array.
     * </p>
     * <p>
     * The new array contains all of the element of <code>array1</code> followed
     * by all of the elements <code>array2</code>. When an array is returned, it
     * is always a new array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.addAll(array1, null)   = cloned copy of array1
     * ArrayUtils.addAll(null, array2)   = cloned copy of array2
     * ArrayUtils.addAll([], [])         = []
     * </pre>
     * 
     * @param array1 the first array whose elements are added to the new array.
     * @param array2 the second array whose elements are added to the new array.
     * @return The new double[] array.
     * @since 2.1
     */
    public static double[] addAll(double[] array1, double... array2)
    {
        if (array1 == null) {
            return clone(array2);
        } else if (array2 == null) {
            return clone(array1);
        }
        double[] joinedArray = new double[array1.length + array2.length];
        System.arraycopy(array1, 0, joinedArray, 0, array1.length);
        System.arraycopy(array2, 0, joinedArray, array1.length, array2.length);
        return joinedArray;
    }

    /**
     * <p>
     * Adds all the elements of the given arrays into a new array.
     * </p>
     * <p>
     * The new array contains all of the element of <code>array1</code> followed
     * by all of the elements <code>array2</code>. When an array is returned, it
     * is always a new array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.addAll(null, null)     = null
     * ArrayUtils.addAll(array1, null)   = cloned copy of array1
     * ArrayUtils.addAll(null, array2)   = cloned copy of array2
     * ArrayUtils.addAll([], [])         = []
     * ArrayUtils.addAll([null], [null]) = [null, null]
     * ArrayUtils.addAll(["a", "b", "c"], ["1", "2", "3"]) = ["a", "b", "c", "1", "2", "3"]
     * </pre>
     * 
     * @param array1 the first array whose elements are added to the new array,
     *            may be <code>null</code>
     * @param array2 the second array whose elements are added to the new array,
     *            may be <code>null</code>
     * @return The new array, <code>null</code> if both arrays are
     *         <code>null</code>. The type of the new array is the type of the
     *         first array, unless the first array is null, in which case the
     *         type is the same as the second array.
     * @since 2.1
     * @throws IllegalArgumentException if the array types are incompatible
     */
    public static <T> T[] addAll(T[] array1, T... array2)
    {
        if (array1 == null) {
            return clone(array2);
        } else if (array2 == null) {
            return clone(array1);
        }
        final Class<?> type1 = array1.getClass().getComponentType();
        @SuppressWarnings("unchecked")
        // OK, because array is of type T
        T[] joinedArray = (T[]) Array.newInstance(type1, array1.length
                        + array2.length);
        System.arraycopy(array1, 0, joinedArray, 0, array1.length);
        try {
            System.arraycopy(array2, 0, joinedArray, array1.length,
                array2.length);
        } catch (ArrayStoreException ase) {
            // Check if problem was due to incompatible types
            /*
             * We do this here, rather than before the copy because: - it would
             * be a wasted check most of the time - safer, in case check turns
             * out to be too strict
             */
            final Class<?> type2 = array2.getClass().getComponentType();
            if (!type1.isAssignableFrom(type2)) {
                throw new IllegalArgumentException("Cannot store "
                                + type2.getName() + " in an array of "
                                + type1.getName(), ase);
            }
            throw ase; // No, so rethrow original
        }
        return joinedArray;
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // clone(array)
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Shallow clones an array returning a typecast result and handling
     * <code>null</code>.
     * </p>
     * 
     * <p>
     * The objects in the array are not cloned, thus there is no special
     * handling for multi-dimensional arrays.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array the array to shallow clone, may be <code>null</code>
     * @return the cloned array, <code>null</code> if <code>null</code> input
     */
    public static <T> T[] clone(T[] array)
    {
        if (array == null) {
            return null;
        }
        return array.clone();
    }

    /**
     * <p>
     * Clones an array returning a typecast result and handling
     * <code>null</code>.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array the array to clone, may be <code>null</code>
     * @return the cloned array, <code>null</code> if <code>null</code> input
     */
    public static long[] clone(long[] array)
    {
        if (array == null) {
            return null;
        }
        return array.clone();
    }

    /**
     * <p>
     * Clones an array returning a typecast result and handling
     * <code>null</code>.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array the array to clone, may be <code>null</code>
     * @return the cloned array, <code>null</code> if <code>null</code> input
     */
    public static int[] clone(int[] array)
    {
        if (array == null) {
            return null;
        }
        return array.clone();
    }

    /**
     * <p>
     * Clones an array returning a typecast result and handling
     * <code>null</code>.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array the array to clone, may be <code>null</code>
     * @return the cloned array, <code>null</code> if <code>null</code> input
     */
    public static char[] clone(char[] array)
    {
        if (array == null) {
            return null;
        }
        return array.clone();
    }

    /**
     * <p>
     * Clones an array returning a typecast result and handling
     * <code>null</code>.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array the array to clone, may be <code>null</code>
     * @return the cloned array, <code>null</code> if <code>null</code> input
     */
    public static byte[] clone(byte[] array)
    {
        if (array == null) {
            return null;
        }
        return array.clone();
    }

    /**
     * <p>
     * Clones an array returning a typecast result and handling
     * <code>null</code>.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array the array to clone, may be <code>null</code>
     * @return the cloned array, <code>null</code> if <code>null</code> input
     */
    public static double[] clone(double[] array)
    {
        if (array == null) {
            return null;
        }
        return array.clone();
    }

    /**
     * <p>
     * Clones an array returning a typecast result and handling
     * <code>null</code>.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array the array to clone, may be <code>null</code>
     * @return the cloned array, <code>null</code> if <code>null</code> input
     */
    public static boolean[] clone(boolean[] array)
    {
        if (array == null) {
            return null;
        }
        return array.clone();
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // subArray(array, startIndex, endIndex)
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Produces a new <code>boolean</code> array containing the elements between
     * the start and end indices.
     * </p>
     * 
     * <p>
     * The start index is inclusive, the end index exclusive. Null array input
     * produces null output.
     * </p>
     * 
     * @param array the array
     * @param startIndexInclusive the starting index. Undervalue (&lt;0) is
     *            promoted to 0, overvalue (&gt;array.length) results in an
     *            empty array.
     * @param endIndexExclusive elements up to endIndex-1 are present in the
     *            returned subarray. Undervalue (&lt; startIndex) produces empty
     *            array, overvalue (&gt;array.length) is demoted to array
     *            length.
     * @return a new array containing the elements between the start and end
     *         indices.
     * @since 2.1
     */
    public static boolean[] subarray(
        boolean[] array,
        int startIndexInclusive,
        int endIndexExclusive)
    {
        if (array == null) {
            return null;
        }
        if (startIndexInclusive < 0) {
            startIndexInclusive = 0;
        }
        if (endIndexExclusive > array.length) {
            endIndexExclusive = array.length;
        }
        int newSize = endIndexExclusive - startIndexInclusive;
        if (newSize <= 0) {
            return null;
        }

        boolean[] subarray = new boolean[newSize];
        System.arraycopy(array, startIndexInclusive, subarray, 0, newSize);
        return subarray;
    }

    /**
     * <p>
     * Produces a new <code>byte</code> array containing the elements between
     * the start and end indices.
     * </p>
     * 
     * <p>
     * The start index is inclusive, the end index exclusive. Null array input
     * produces null output.
     * </p>
     * 
     * @param array the array
     * @param startIndexInclusive the starting index. Undervalue (&lt;0) is
     *            promoted to 0, overvalue (&gt;array.length) results in an
     *            empty array.
     * @param endIndexExclusive elements up to endIndex-1 are present in the
     *            returned subarray. Undervalue (&lt; startIndex) produces empty
     *            array, overvalue (&gt;array.length) is demoted to array
     *            length.
     * @return a new array containing the elements between the start and end
     *         indices.
     * @since 2.1
     */
    public static byte[] subarray(
        byte[] array,
        int startIndexInclusive,
        int endIndexExclusive)
    {
        if (array == null) {
            return null;
        }
        if (startIndexInclusive < 0) {
            startIndexInclusive = 0;
        }
        if (endIndexExclusive > array.length) {
            endIndexExclusive = array.length;
        }
        int newSize = endIndexExclusive - startIndexInclusive;
        if (newSize <= 0) {
            return null;
        }

        byte[] subarray = new byte[newSize];
        System.arraycopy(array, startIndexInclusive, subarray, 0, newSize);
        return subarray;
    }

    /**
     * <p>
     * Produces a new <code>char</code> array containing the elements between
     * the start and end indices.
     * </p>
     * 
     * <p>
     * The start index is inclusive, the end index exclusive. Null array input
     * produces null output.
     * </p>
     * 
     * @param array the array
     * @param startIndexInclusive the starting index. Undervalue (&lt;0) is
     *            promoted to 0, overvalue (&gt;array.length) results in an
     *            empty array.
     * @param endIndexExclusive elements up to endIndex-1 are present in the
     *            returned subarray. Undervalue (&lt; startIndex) produces empty
     *            array, overvalue (&gt;array.length) is demoted to array
     *            length.
     * @return a new array containing the elements between the start and end
     *         indices.
     * @since 2.1
     */
    public static char[] subarray(
        char[] array,
        int startIndexInclusive,
        int endIndexExclusive)
    {
        if (array == null) {
            return null;
        }
        if (startIndexInclusive < 0) {
            startIndexInclusive = 0;
        }
        if (endIndexExclusive > array.length) {
            endIndexExclusive = array.length;
        }
        int newSize = endIndexExclusive - startIndexInclusive;
        if (newSize <= 0) {
            return null;
        }

        char[] subarray = new char[newSize];
        System.arraycopy(array, startIndexInclusive, subarray, 0, newSize);
        return subarray;
    }

    /**
     * <p>
     * Produces a new <code>double</code> array containing the elements between
     * the start and end indices.
     * </p>
     * 
     * <p>
     * The start index is inclusive, the end index exclusive. Null array input
     * produces null output.
     * </p>
     * 
     * @param array the array
     * @param startIndexInclusive the starting index. Undervalue (&lt;0) is
     *            promoted to 0, overvalue (&gt;array.length) results in an
     *            empty array.
     * @param endIndexExclusive elements up to endIndex-1 are present in the
     *            returned subarray. Undervalue (&lt; startIndex) produces empty
     *            array, overvalue (&gt;array.length) is demoted to array
     *            length.
     * @return a new array containing the elements between the start and end
     *         indices.
     * @since 2.1
     */
    public static double[] subarray(
        double[] array,
        int startIndexInclusive,
        int endIndexExclusive)
    {
        if (array == null) {
            return null;
        }
        if (startIndexInclusive < 0) {
            startIndexInclusive = 0;
        }
        if (endIndexExclusive > array.length) {
            endIndexExclusive = array.length;
        }
        int newSize = endIndexExclusive - startIndexInclusive;
        if (newSize <= 0) {
            return null;
        }

        double[] subarray = new double[newSize];
        System.arraycopy(array, startIndexInclusive, subarray, 0, newSize);
        return subarray;
    }

    /**
     * <p>
     * Produces a new <code>int</code> array containing the elements between the
     * start and end indices.
     * </p>
     * 
     * <p>
     * The start index is inclusive, the end index exclusive. Null array input
     * produces null output.
     * </p>
     * 
     * @param array the array
     * @param startIndexInclusive the starting index. Undervalue (&lt;0) is
     *            promoted to 0, overvalue (&gt;array.length) results in an
     *            empty array.
     * @param endIndexExclusive elements up to endIndex-1 are present in the
     *            returned subarray. Undervalue (&lt; startIndex) produces empty
     *            array, overvalue (&gt;array.length) is demoted to array
     *            length.
     * @return a new array containing the elements between the start and end
     *         indices.
     * @since 2.1
     */
    public static int[] subarray(
        int[] array,
        int startIndexInclusive,
        int endIndexExclusive)
    {
        if (array == null) {
            return null;
        }
        if (startIndexInclusive < 0) {
            startIndexInclusive = 0;
        }
        if (endIndexExclusive > array.length) {
            endIndexExclusive = array.length;
        }
        int newSize = endIndexExclusive - startIndexInclusive;
        if (newSize <= 0) {
            return null;
        }

        int[] subarray = new int[newSize];
        System.arraycopy(array, startIndexInclusive, subarray, 0, newSize);
        return subarray;
    }

    /**
     * <p>
     * Produces a new <code>long</code> array containing the elements between
     * the start and end indices.
     * </p>
     * 
     * <p>
     * The start index is inclusive, the end index exclusive. Null array input
     * produces null output.
     * </p>
     * 
     * @param array the array
     * @param startIndexInclusive the starting index. Undervalue (&lt;0) is
     *            promoted to 0, overvalue (&gt;array.length) results in an
     *            empty array.
     * @param endIndexExclusive elements up to endIndex-1 are present in the
     *            returned subarray. Undervalue (&lt; startIndex) produces empty
     *            array, overvalue (&gt;array.length) is demoted to array
     *            length.
     * @return a new array containing the elements between the start and end
     *         indices.
     * @since 2.1
     */
    public static long[] subarray(
        long[] array,
        int startIndexInclusive,
        int endIndexExclusive)
    {
        if (array == null) {
            return null;
        }
        if (startIndexInclusive < 0) {
            startIndexInclusive = 0;
        }
        if (endIndexExclusive > array.length) {
            endIndexExclusive = array.length;
        }
        int newSize = endIndexExclusive - startIndexInclusive;
        if (newSize <= 0) {
            return null;
        }

        long[] subarray = new long[newSize];
        System.arraycopy(array, startIndexInclusive, subarray, 0, newSize);
        return subarray;
    }

    /**
     * <p>
     * Produces a new array containing the elements between the start and end
     * indices.
     * </p>
     * 
     * <p>
     * The start index is inclusive, the end index exclusive. Null array input
     * produces null output.
     * </p>
     * 
     * <p>
     * The component type of the subarray is always the same as that of the
     * input array. Thus, if the input is an array of type <code>Date</code>,
     * the following usage is envisaged:
     * </p>
     * 
     * <pre>
     * Date[] someDates = (Date[]) ArrayUtils.subarray(allDates, 2, 5);
     * </pre>
     * 
     * @param array the array
     * @param startIndexInclusive the starting index. Undervalue (&lt;0) is
     *            promoted to 0, overvalue (&gt;array.length) results in an
     *            empty array.
     * @param endIndexExclusive elements up to endIndex-1 are present in the
     *            returned subarray. Undervalue (&lt; startIndex) produces empty
     *            array, overvalue (&gt;array.length) is demoted to array
     *            length.
     * @return a new array containing the elements between the start and end
     *         indices.
     * @since 2.1
     */
    public static <T> T[] subarray(
        T[] array,
        int startIndexInclusive,
        int endIndexExclusive)
    {
        if (array == null) {
            return null;
        }
        if (startIndexInclusive < 0) {
            startIndexInclusive = 0;
        }
        if (endIndexExclusive > array.length) {
            endIndexExclusive = array.length;
        }
        int newSize = endIndexExclusive - startIndexInclusive;
        Class<?> type = array.getClass().getComponentType();
        if (newSize <= 0) {
            @SuppressWarnings("unchecked")
            // OK, because array is of type T
            final T[] emptyArray = (T[]) Array.newInstance(type, 0);
            return emptyArray;
        }
        @SuppressWarnings("unchecked")
        // OK, because array is of type T
        T[] subarray = (T[]) Array.newInstance(type, newSize);
        System.arraycopy(array, startIndexInclusive, subarray, 0, newSize);
        return subarray;
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // removeElement(array, element)
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Removes the first occurrence of the specified element from the specified
     * array. All subsequent elements are shifted to the left (subtracts one
     * from their indices). If the array doesn't contains such an element, no
     * elements are removed from the array.
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the first occurrence of the specified element. The component type
     * of the returned array is always the same as that of the input array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.removeElement(null, true)                = null
     * ArrayUtils.removeElement([], true)                  = []
     * ArrayUtils.removeElement([true], false)             = [true]
     * ArrayUtils.removeElement([true, false], false)      = [true]
     * ArrayUtils.removeElement([true, false, true], true) = [false, true]
     * </pre>
     * 
     * @param array the array to remove the element from, may be
     *            <code>null</code>
     * @param element the element to be removed
     * @return A new array containing the existing elements except the first
     *         occurrence of the specified element.
     * @since 2.1
     */
    public static boolean[] removeElement(boolean[] array, boolean element)
    {
        int index = indexOf(array, element);
        if (index == INDEX_NOT_FOUND) {
            return clone(array);
        }
        return removeElemAtIndex(array, index);
    }

    /**
     * <p>
     * Removes the first occurrence of the specified element from the specified
     * array. All subsequent elements are shifted to the left (subtracts one
     * from their indices). If the array doesn't contains such an element, no
     * elements are removed from the array.
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the first occurrence of the specified element. The component type
     * of the returned array is always the same as that of the input array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.removeElement(null, 1)        = null
     * ArrayUtils.removeElement([], 1)          = []
     * ArrayUtils.removeElement([1], 0)         = [1]
     * ArrayUtils.removeElement([1, 0], 0)      = [1]
     * ArrayUtils.removeElement([1, 0, 1], 1)   = [0, 1]
     * </pre>
     * 
     * @param array the array to remove the element from, may be
     *            <code>null</code>
     * @param element the element to be removed
     * @return A new array containing the existing elements except the first
     *         occurrence of the specified element.
     * @since 2.1
     */
    public static byte[] removeElement(byte[] array, byte element)
    {
        int index = indexOf(array, element);
        if (index == INDEX_NOT_FOUND) {
            return clone(array);
        }
        return removeElemAtIndex(array, index);
    }

    /**
     * <p>
     * Removes the first occurrence of the specified element from the specified
     * array. All subsequent elements are shifted to the left (subtracts one
     * from their indices). If the array doesn't contains such an element, no
     * elements are removed from the array.
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the first occurrence of the specified element. The component type
     * of the returned array is always the same as that of the input array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.removeElement(null, 'a')            = null
     * ArrayUtils.removeElement([], 'a')              = []
     * ArrayUtils.removeElement(['a'], 'b')           = ['a']
     * ArrayUtils.removeElement(['a', 'b'], 'a')      = ['b']
     * ArrayUtils.removeElement(['a', 'b', 'a'], 'a') = ['b', 'a']
     * </pre>
     * 
     * @param array the array to remove the element from, may be
     *            <code>null</code>
     * @param element the element to be removed
     * @return A new array containing the existing elements except the first
     *         occurrence of the specified element.
     * @since 2.1
     */
    public static char[] removeElement(char[] array, char element)
    {
        int index = indexOf(array, element);
        if (index == INDEX_NOT_FOUND) {
            return clone(array);
        }
        return removeElemAtIndex(array, index);
    }

    /**
     * <p>
     * Removes the first occurrence of the specified element from the specified
     * array. All subsequent elements are shifted to the left (subtracts one
     * from their indices). If the array doesn't contains such an element, no
     * elements are removed from the array.
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the first occurrence of the specified element. The component type
     * of the returned array is always the same as that of the input array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.removeElement(null, 1.1)            = null
     * ArrayUtils.removeElement([], 1.1)              = []
     * ArrayUtils.removeElement([1.1], 1.2)           = [1.1]
     * ArrayUtils.removeElement([1.1, 2.3], 1.1)      = [2.3]
     * ArrayUtils.removeElement([1.1, 2.3, 1.1], 1.1) = [2.3, 1.1]
     * </pre>
     * 
     * @param array the array to remove the element from, may be
     *            <code>null</code>
     * @param element the element to be removed
     * @return A new array containing the existing elements except the first
     *         occurrence of the specified element.
     * @since 2.1
     */
    public static double[] removeElement(double[] array, double element)
    {
        int index = indexOf(array, element);
        if (index == INDEX_NOT_FOUND) {
            return clone(array);
        }
        return removeElemAtIndex(array, index);
    }

    /**
     * <p>
     * Removes the first occurrence of the specified element from the specified
     * array. All subsequent elements are shifted to the left (subtracts one
     * from their indices). If the array doesn't contains such an element, no
     * elements are removed from the array.
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the first occurrence of the specified element. The component type
     * of the returned array is always the same as that of the input array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.removeElement(null, 1)      = null
     * ArrayUtils.removeElement([], 1)        = []
     * ArrayUtils.removeElement([1], 2)       = [1]
     * ArrayUtils.removeElement([1, 3], 1)    = [3]
     * ArrayUtils.removeElement([1, 3, 1], 1) = [3, 1]
     * </pre>
     * 
     * @param array the array to remove the element from, may be
     *            <code>null</code>
     * @param element the element to be removed
     * @return A new array containing the existing elements except the first
     *         occurrence of the specified element.
     * @since 2.1
     */
    public static int[] removeElement(int[] array, int element)
    {
        int index = indexOf(array, element);
        if (index == INDEX_NOT_FOUND) {
            return clone(array);
        }
        return removeElemAtIndex(array, index);
    }

    /**
     * <p>
     * Removes the first occurrence of the specified element from the specified
     * array. All subsequent elements are shifted to the left (subtracts one
     * from their indices). If the array doesn't contains such an element, no
     * elements are removed from the array.
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the first occurrence of the specified element. The component type
     * of the returned array is always the same as that of the input array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.removeElement(null, 1)      = null
     * ArrayUtils.removeElement([], 1)        = []
     * ArrayUtils.removeElement([1], 2)       = [1]
     * ArrayUtils.removeElement([1, 3], 1)    = [3]
     * ArrayUtils.removeElement([1, 3, 1], 1) = [3, 1]
     * </pre>
     * 
     * @param array the array to remove the element from, may be
     *            <code>null</code>
     * @param element the element to be removed
     * @return A new array containing the existing elements except the first
     *         occurrence of the specified element.
     * @since 2.1
     */
    public static long[] removeElement(long[] array, long element)
    {
        int index = indexOf(array, element);
        if (index == INDEX_NOT_FOUND) {
            return clone(array);
        }
        return removeElemAtIndex(array, index);
    }

    /**
     * <p>
     * Removes the first occurrence of the specified element from the specified
     * array. All subsequent elements are shifted to the left (subtracts one
     * from their indices). If the array doesn't contains such an element, no
     * elements are removed from the array.
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the first occurrence of the specified element. The component type
     * of the returned array is always the same as that of the input array.
     * </p>
     * 
     * <pre>
     * ArrayUtils.removeElement(null, "a")            = null
     * ArrayUtils.removeElement([], "a")              = []
     * ArrayUtils.removeElement(["a"], "b")           = ["a"]
     * ArrayUtils.removeElement(["a", "b"], "a")      = ["b"]
     * ArrayUtils.removeElement(["a", "b", "a"], "a") = ["b", "a"]
     * </pre>
     * 
     * @param array the array to remove the element from, may be
     *            <code>null</code>
     * @param element the element to be removed
     * @return A new array containing the existing elements except the first
     *         occurrence of the specified element.
     * @since 2.1
     */
    public static <T> T[] removeElement(T[] array, Object element)
    {
        int index = indexOf(array, element);
        if (index == INDEX_NOT_FOUND) {
            return clone(array);
        }
        return removeElemAtIndex(array, index);
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // removeElemAtIndex(array, index)
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Removes the element at the specified position from the specified array.
     * All subsequent elements are shifted to the left (subtracts one from their
     * indices).
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the element on the specified position. The component type of the
     * returned array is always the same as that of the input array.
     * </p>
     * 
     * <p>
     * If the input array is <code>null</code>, an IndexOutOfBoundsException
     * will be thrown, because in that case no valid index can be specified.
     * </p>
     * 
     * <pre>
     * ArrayUtils.remove([true], 0)              = []
     * ArrayUtils.remove([true, false], 0)       = [false]
     * ArrayUtils.remove([true, false], 1)       = [true]
     * ArrayUtils.remove([true, true, false], 1) = [true, false]
     * </pre>
     * 
     * @param array the array to remove the element from, may not be
     *            <code>null</code>
     * @param index the position of the element to be removed
     * @return A new array containing the existing elements except the element
     *         at the specified position.
     * @throws IndexOutOfBoundsException if the index is out of range (index < 0
     *             || index >= array.length), or if the array is
     *             <code>null</code>.
     * @since 2.1
     */
    public static boolean[] removeElemAtIndex(boolean[] array, int index)
    {
        return (boolean[]) remove(array, index);
    }

    /**
     * <p>
     * Removes the element at the specified position from the specified array.
     * All subsequent elements are shifted to the left (subtracts one from their
     * indices).
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the element on the specified position. The component type of the
     * returned array is always the same as that of the input array.
     * </p>
     * 
     * <p>
     * If the input array is <code>null</code>, an IndexOutOfBoundsException
     * will be thrown, because in that case no valid index can be specified.
     * </p>
     * 
     * <pre>
     * ArrayUtils.remove([1], 0)          = []
     * ArrayUtils.remove([1, 0], 0)       = [0]
     * ArrayUtils.remove([1, 0], 1)       = [1]
     * ArrayUtils.remove([1, 0, 1], 1)    = [1, 1]
     * </pre>
     * 
     * @param array the array to remove the element from, may not be
     *            <code>null</code>
     * @param index the position of the element to be removed
     * @return A new array containing the existing elements except the element
     *         at the specified position.
     * @throws IndexOutOfBoundsException if the index is out of range (index < 0
     *             || index >= array.length), or if the array is
     *             <code>null</code>.
     * @since 2.1
     */
    public static byte[] removeElemAtIndex(byte[] array, int index)
    {
        return (byte[]) remove(array, index);
    }

    /**
     * <p>
     * Removes the element at the specified position from the specified array.
     * All subsequent elements are shifted to the left (subtracts one from their
     * indices).
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the element on the specified position. The component type of the
     * returned array is always the same as that of the input array.
     * </p>
     * 
     * <p>
     * If the input array is <code>null</code>, an IndexOutOfBoundsException
     * will be thrown, because in that case no valid index can be specified.
     * </p>
     * 
     * <pre>
     * ArrayUtils.remove(['a'], 0)           = []
     * ArrayUtils.remove(['a', 'b'], 0)      = ['b']
     * ArrayUtils.remove(['a', 'b'], 1)      = ['a']
     * ArrayUtils.remove(['a', 'b', 'c'], 1) = ['a', 'c']
     * </pre>
     * 
     * @param array the array to remove the element from, may not be
     *            <code>null</code>
     * @param index the position of the element to be removed
     * @return A new array containing the existing elements except the element
     *         at the specified position.
     * @throws IndexOutOfBoundsException if the index is out of range (index < 0
     *             || index >= array.length), or if the array is
     *             <code>null</code>.
     * @since 2.1
     */
    public static char[] removeElemAtIndex(char[] array, int index)
    {
        return (char[]) remove(array, index);
    }

    /**
     * <p>
     * Removes the element at the specified position from the specified array.
     * All subsequent elements are shifted to the left (subtracts one from their
     * indices).
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the element on the specified position. The component type of the
     * returned array is always the same as that of the input array.
     * </p>
     * 
     * <p>
     * If the input array is <code>null</code>, an IndexOutOfBoundsException
     * will be thrown, because in that case no valid index can be specified.
     * </p>
     * 
     * <pre>
     * ArrayUtils.remove([1.1], 0)           = []
     * ArrayUtils.remove([2.5, 6.0], 0)      = [6.0]
     * ArrayUtils.remove([2.5, 6.0], 1)      = [2.5]
     * ArrayUtils.remove([2.5, 6.0, 3.8], 1) = [2.5, 3.8]
     * </pre>
     * 
     * @param array the array to remove the element from, may not be
     *            <code>null</code>
     * @param index the position of the element to be removed
     * @return A new array containing the existing elements except the element
     *         at the specified position.
     * @throws IndexOutOfBoundsException if the index is out of range (index < 0
     *             || index >= array.length), or if the array is
     *             <code>null</code>.
     * @since 2.1
     */
    public static double[] removeElemAtIndex(double[] array, int index)
    {
        return (double[]) remove(array, index);
    }

    /**
     * <p>
     * Removes the element at the specified position from the specified array.
     * All subsequent elements are shifted to the left (subtracts one from their
     * indices).
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the element on the specified position. The component type of the
     * returned array is always the same as that of the input array.
     * </p>
     * 
     * <p>
     * If the input array is <code>null</code>, an IndexOutOfBoundsException
     * will be thrown, because in that case no valid index can be specified.
     * </p>
     * 
     * <pre>
     * ArrayUtils.remove([1], 0)         = []
     * ArrayUtils.remove([2, 6], 0)      = [6]
     * ArrayUtils.remove([2, 6], 1)      = [2]
     * ArrayUtils.remove([2, 6, 3], 1)   = [2, 3]
     * </pre>
     * 
     * @param array the array to remove the element from, may not be
     *            <code>null</code>
     * @param index the position of the element to be removed
     * @return A new array containing the existing elements except the element
     *         at the specified position.
     * @throws IndexOutOfBoundsException if the index is out of range (index < 0
     *             || index >= array.length), or if the array is
     *             <code>null</code>.
     * @since 2.1
     */
    public static int[] removeElemAtIndex(int[] array, int index)
    {
        return (int[]) remove(array, index);
    }

    /**
     * <p>
     * Removes the element at the specified position from the specified array.
     * All subsequent elements are shifted to the left (subtracts one from their
     * indices).
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the element on the specified position. The component type of the
     * returned array is always the same as that of the input array.
     * </p>
     * 
     * <p>
     * If the input array is <code>null</code>, an IndexOutOfBoundsException
     * will be thrown, because in that case no valid index can be specified.
     * </p>
     * 
     * <pre>
     * ArrayUtils.remove([1], 0)         = []
     * ArrayUtils.remove([2, 6], 0)      = [6]
     * ArrayUtils.remove([2, 6], 1)      = [2]
     * ArrayUtils.remove([2, 6, 3], 1)   = [2, 3]
     * </pre>
     * 
     * @param array the array to remove the element from, may not be
     *            <code>null</code>
     * @param index the position of the element to be removed
     * @return A new array containing the existing elements except the element
     *         at the specified position.
     * @throws IndexOutOfBoundsException if the index is out of range (index < 0
     *             || index >= array.length), or if the array is
     *             <code>null</code>.
     * @since 2.1
     */
    public static long[] removeElemAtIndex(long[] array, int index)
    {
        return (long[]) remove(array, index);
    }

    /**
     * <p>
     * Removes the element at the specified position from the specified array.
     * All subsequent elements are shifted to the left (subtracts one from their
     * indices).
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the element on the specified position. The component type of the
     * returned array is always the same as that of the input array.
     * </p>
     * 
     * <p>
     * If the input array is <code>null</code>, an IndexOutOfBoundsException
     * will be thrown, because in that case no valid index can be specified.
     * </p>
     * 
     * <pre>
     * ArrayUtils.remove(["a"], 0)           = []
     * ArrayUtils.remove(["a", "b"], 0)      = ["b"]
     * ArrayUtils.remove(["a", "b"], 1)      = ["a"]
     * ArrayUtils.remove(["a", "b", "c"], 1) = ["a", "c"]
     * </pre>
     * 
     * @param array the array to remove the element from, may not be
     *            <code>null</code>
     * @param index the position of the element to be removed
     * @return A new array containing the existing elements except the element
     *         at the specified position.
     * @throws IndexOutOfBoundsException if the index is out of range (index < 0
     *             || index >= array.length), or if the array is
     *             <code>null</code>.
     * @since 2.1
     */
    @SuppressWarnings("unchecked")
    // remove() always creates an array of the same type as its input
    public static <T> T[] removeElemAtIndex(T[] array, int index)
    {
        return (T[]) remove(array, index);
    }

    /**
     * <p>
     * Removes the element at the specified position from the specified array.
     * All subsequent elements are shifted to the left (subtracts one from their
     * indices).
     * </p>
     * 
     * <p>
     * This method returns a new array with the same elements of the input array
     * except the element on the specified position. The component type of the
     * returned array is always the same as that of the input array.
     * </p>
     * 
     * <p>
     * If the input array is <code>null</code>, an IndexOutOfBoundsException
     * will be thrown, because in that case no valid index can be specified.
     * </p>
     * 
     * @param array the array to remove the element from, may not be
     *            <code>null</code>
     * @param index the position of the element to be removed
     * @return A new array containing the existing elements except the element
     *         at the specified position.
     * @throws IndexOutOfBoundsException if the index is out of range (index < 0
     *             || index >= array.length), or if the array is
     *             <code>null</code>.
     * @since 2.1
     */
    private static Object remove(Object array, int index)
    {
        int length = getLength(array);
        if (index < 0 || index >= length) {
            throw new IndexOutOfBoundsException("Index: " + index
                            + ", Length: " + length);
        }
        Object result = Array.newInstance(array.getClass().getComponentType(),
            length - 1);
        System.arraycopy(array, 0, result, 0, index);
        if (index < length - 1) {
            System.arraycopy(array, index + 1, result, index, length - index
                            - 1);
        }
        return result;
    }

    /**
     * <p>
     * Returns the length of the specified array. This method can deal with
     * <code>Object</code> arrays and with primitive arrays.
     * </p>
     * 
     * <p>
     * If the input array is <code>null</code>, <code>0</code> is returned.
     * </p>
     * 
     * <pre>
     * ArrayUtils.getLength(null)            = 0
     * ArrayUtils.getLength([])              = 0
     * ArrayUtils.getLength([null])          = 1
     * ArrayUtils.getLength([true, false])   = 2
     * ArrayUtils.getLength([1, 2, 3])       = 3
     * ArrayUtils.getLength(["a", "b", "c"]) = 3
     * </pre>
     * 
     * @param array the array to retrieve the length from, may be null
     * @return The length of the array, or <code>0</code> if the array is
     *         <code>null</code>
     * @throws IllegalArgumentException if the object arguement is not an array.
     * @since 2.1
     */
    public static int getLength(Object array)
    {
        if (array == null) {
            return 0;
        }
        return Array.getLength(array);
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // Search for specified element in array - indexOf() / contains()
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * The index value when an element is not found in a list or array:
     * <code>-1</code>. This value is returned by methods in this class and can
     * also be used in comparisons with values returned by various method from
     * {@link java.util.List}.
     */
    public static final int INDEX_NOT_FOUND = -1;

    /**
     * <p>
     * Checks if the value is in the given array.
     * </p>
     * 
     * <p>
     * The method returns <code>false</code> if a <code>null</code> array is
     * passed in.
     * </p>
     * 
     * @param array the array to search through
     * @param valueToFind the value to find
     * @return <code>true</code> if the array contains the object
     */
    public static boolean contains(boolean[] array, boolean valueToFind)
    {
        return indexOf(array, valueToFind) != INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Checks if the value is in the given array.
     * </p>
     * 
     * <p>
     * The method returns <code>false</code> if a <code>null</code> array is
     * passed in.
     * </p>
     * 
     * @param array the array to search through
     * @param valueToFind the value to find
     * @return <code>true</code> if the array contains the object
     */
    public static boolean contains(byte[] array, byte valueToFind)
    {
        return indexOf(array, valueToFind) != INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Checks if the value is in the given array.
     * </p>
     * 
     * <p>
     * The method returns <code>false</code> if a <code>null</code> array is
     * passed in.
     * </p>
     * 
     * @param array the array to search through
     * @param valueToFind the value to find
     * @return <code>true</code> if the array contains the object
     * @since 2.1
     */
    public static boolean contains(char[] array, char valueToFind)
    {
        return indexOf(array, valueToFind) != INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Checks if a value falling within the given tolerance is in the given
     * array. If the array contains a value within the inclusive range defined
     * by (value - tolerance) to (value + tolerance).
     * </p>
     * 
     * <p>
     * The method returns <code>false</code> if a <code>null</code> array is
     * passed in.
     * </p>
     * 
     * @param array the array to search
     * @param valueToFind the value to find
     * @param tolerance default = DBL_EPSILON (1E-6)
     * @return true if value falling within tolerance is in array
     */
    public static boolean contains(double[] array, double valueToFind)
    {
        return indexOf(array, valueToFind, 0, DBL_EPSILON) != INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Checks if the value is in the given array.
     * </p>
     * 
     * <p>
     * The method returns <code>false</code> if a <code>null</code> array is
     * passed in.
     * </p>
     * 
     * @param array the array to search through
     * @param valueToFind the value to find
     * @return <code>true</code> if the array contains the object
     */
    public static boolean contains(int[] array, int valueToFind)
    {
        return indexOf(array, valueToFind) != INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Checks if the value is in the given array.
     * </p>
     * 
     * <p>
     * The method returns <code>false</code> if a <code>null</code> array is
     * passed in.
     * </p>
     * 
     * @param array the array to search through
     * @param valueToFind the value to find
     * @return <code>true</code> if the array contains the object
     */
    public static boolean contains(long[] array, long valueToFind)
    {
        return indexOf(array, valueToFind) != INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Checks if the object is in the given array.
     * </p>
     * 
     * <p>
     * The method returns <code>false</code> if a <code>null</code> array is
     * passed in.
     * </p>
     * 
     * @param array the array to search through
     * @param objectToFind the object to find
     * @return <code>true</code> if the array contains the object
     */
    public static boolean contains(Object[] array, Object objectToFind)
    {
        return indexOf(array, objectToFind) != INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Finds the index of the given value in the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @return the index of the value within the array, {@link #INDEX_NOT_FOUND}
     *         (<code>-1</code>) if not found or <code>null</code> array input
     */
    public static int indexOf(boolean[] array, boolean valueToFind)
    {
        return indexOf(array, valueToFind, 0);
    }

    /**
     * <p>
     * Finds the index of the given value in the array starting at the given
     * index.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex is treated as zero. A startIndex larger than the
     * array length will return {@link #INDEX_NOT_FOUND} (<code>-1</code>).
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @param startIndex the index to start searching at
     * @return the index of the value within the array, {@link #INDEX_NOT_FOUND}
     *         (<code>-1</code>) if not found or <code>null</code> array input
     */
    public static int indexOf(
        boolean[] array,
        boolean valueToFind,
        int startIndex)
    {
        if (ArrayUtils.isEmpty(array)) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            startIndex = 0;
        }
        for (int i = startIndex; i < array.length; i++) {
            if (valueToFind == array[i]) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Finds the index of the given value in the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @return the index of the value within the array, {@link #INDEX_NOT_FOUND}
     *         (<code>-1</code>) if not found or <code>null</code> array input
     */
    public static int indexOf(byte[] array, byte valueToFind)
    {
        return indexOf(array, valueToFind, 0);
    }

    /**
     * <p>
     * Finds the index of the given value in the array starting at the given
     * index.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex is treated as zero. A startIndex larger than the
     * array length will return {@link #INDEX_NOT_FOUND} (<code>-1</code>).
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @param startIndex the index to start searching at
     * @return the index of the value within the array, {@link #INDEX_NOT_FOUND}
     *         (<code>-1</code>) if not found or <code>null</code> array input
     */
    public static int indexOf(byte[] array, byte valueToFind, int startIndex)
    {
        if (array == null) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            startIndex = 0;
        }
        for (int i = startIndex; i < array.length; i++) {
            if (valueToFind == array[i]) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Finds the index of the given value in the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @return the index of the value within the array, {@link #INDEX_NOT_FOUND}
     *         (<code>-1</code>) if not found or <code>null</code> array input
     * @since 2.1
     */
    public static int indexOf(char[] array, char valueToFind)
    {
        return indexOf(array, valueToFind, 0);
    }

    /**
     * <p>
     * Finds the index of the given value in the array starting at the given
     * index.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex is treated as zero. A startIndex larger than the
     * array length will return {@link #INDEX_NOT_FOUND} (<code>-1</code>).
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @param startIndex the index to start searching at
     * @return the index of the value within the array, {@link #INDEX_NOT_FOUND}
     *         (<code>-1</code>) if not found or <code>null</code> array input
     * @since 2.1
     */
    public static int indexOf(char[] array, char valueToFind, int startIndex)
    {
        if (array == null) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            startIndex = 0;
        }
        for (int i = startIndex; i < array.length; i++) {
            if (valueToFind == array[i]) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Finds the index of the given value in the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @return the index of the value within the array, {@link #INDEX_NOT_FOUND}
     *         (<code>-1</code>) if not found or <code>null</code> array input
     */
    public static int indexOf(double[] array, double valueToFind)
    {
        return indexOf(array, valueToFind, 0, DBL_EPSILON);
    }

    /**
     * <p>
     * Finds the index of the given value in the array starting at the given
     * index. This method will return the index of the first value which falls
     * between the region defined by valueToFind - tolerance and valueToFind +
     * tolerance.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex is treated as zero. A startIndex larger than the
     * array length will return {@link #INDEX_NOT_FOUND} (<code>-1</code>).
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @param startIndex the index to start searching at
     * @param tolerance tolerance of the search
     * @return the index of the value within the array, {@link #INDEX_NOT_FOUND}
     *         (<code>-1</code>) if not found or <code>null</code> array input
     */
    public static int indexOf(
        double[] array,
        double valueToFind,
        int startIndex,
        double tolerance)
    {
        if (ArrayUtils.isEmpty(array)) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            startIndex = 0;
        }
        for (int i = startIndex; i < array.length; i++) {
            if (abs(array[i] - valueToFind) <= DBL_EPSILON) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Finds the index of the given value in the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @return the index of the value within the array, {@link #INDEX_NOT_FOUND}
     *         (<code>-1</code>) if not found or <code>null</code> array input
     */
    public static int indexOf(int[] array, int valueToFind)
    {
        return indexOf(array, valueToFind, 0);
    }

    /**
     * <p>
     * Finds the index of the given value in the array starting at the given
     * index.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex is treated as zero. A startIndex larger than the
     * array length will return {@link #INDEX_NOT_FOUND} (<code>-1</code>).
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @param startIndex the index to start searching at
     * @return the index of the value within the array, {@link #INDEX_NOT_FOUND}
     *         (<code>-1</code>) if not found or <code>null</code> array input
     */
    public static int indexOf(int[] array, int valueToFind, int startIndex)
    {
        if (array == null) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            startIndex = 0;
        }
        for (int i = startIndex; i < array.length; i++) {
            if (valueToFind == array[i]) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Finds the index of the given value in the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @return the index of the value within the array, {@link #INDEX_NOT_FOUND}
     *         (<code>-1</code>) if not found or <code>null</code> array input
     */
    public static int indexOf(long[] array, long valueToFind)
    {
        return indexOf(array, valueToFind, 0);
    }

    /**
     * <p>
     * Finds the index of the given value in the array starting at the given
     * index.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex is treated as zero. A startIndex larger than the
     * array length will return {@link #INDEX_NOT_FOUND} (<code>-1</code>).
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @param startIndex the index to start searching at
     * @return the index of the value within the array, {@link #INDEX_NOT_FOUND}
     *         (<code>-1</code>) if not found or <code>null</code> array input
     */
    public static int indexOf(long[] array, long valueToFind, int startIndex)
    {
        if (array == null) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            startIndex = 0;
        }
        for (int i = startIndex; i < array.length; i++) {
            if (valueToFind == array[i]) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Finds the index of the given object in the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param objectToFind the object to find, may be <code>null</code>
     * @return the index of the object within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int indexOf(Object[] array, Object objectToFind)
    {
        return indexOf(array, objectToFind, 0);
    }

    /**
     * <p>
     * Finds the index of the given object in the array starting at the given
     * index.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex is treated as zero. A startIndex larger than the
     * array length will return {@link #INDEX_NOT_FOUND} (<code>-1</code>).
     * </p>
     * 
     * @param array the array to search through for the object, may be
     *            <code>null</code>
     * @param objectToFind the object to find, may be <code>null</code>
     * @param startIndex the index to start searching at
     * @return the index of the object within the array starting at the index,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int indexOf(
        Object[] array,
        Object objectToFind,
        int startIndex)
    {
        if (array == null) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            startIndex = 0;
        }
        if (objectToFind == null) {
            for (int i = startIndex; i < array.length; i++) {
                if (array[i] == null) {
                    return i;
                }
            }
        } else if (array.getClass().getComponentType().isInstance(objectToFind)) {
            for (int i = startIndex; i < array.length; i++) {
                if (objectToFind.equals(array[i])) {
                    return i;
                }
            }
        }
        return INDEX_NOT_FOUND;
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // lastIndexOf(array, element)
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Finds the last index of the given value within the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) if
     * <code>null</code> array input.
     * </p>
     * 
     * @param array the array to traverse backwords looking for the object, may
     *            be <code>null</code>
     * @param valueToFind the object to find
     * @return the last index of the value within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int lastIndexOf(boolean[] array, boolean valueToFind)
    {
        return lastIndexOf(array, valueToFind, Integer.MAX_VALUE);
    }

    /**
     * <p>
     * Finds the last index of the given value in the array starting at the
     * given index.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex will return {@link #INDEX_NOT_FOUND} (
     * <code>-1</code>). A startIndex larger than the array length will search
     * from the end of the array.
     * </p>
     * 
     * @param array the array to traversee for looking for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @param startIndex the start index to traverse backwards from
     * @return the last index of the value within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int lastIndexOf(
        boolean[] array,
        boolean valueToFind,
        int startIndex)
    {
        if (ArrayUtils.isEmpty(array)) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            return INDEX_NOT_FOUND;
        } else if (startIndex >= array.length) {
            startIndex = array.length - 1;
        }
        for (int i = startIndex; i >= 0; i--) {
            if (valueToFind == array[i]) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Finds the last index of the given value within the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * @param array the array to traverse backwords looking for the object, may
     *            be <code>null</code>
     * @param valueToFind the object to find
     * @return the last index of the value within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int lastIndexOf(byte[] array, byte valueToFind)
    {
        return lastIndexOf(array, valueToFind, Integer.MAX_VALUE);
    }

    /**
     * <p>
     * Finds the last index of the given value in the array starting at the
     * given index.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex will return {@link #INDEX_NOT_FOUND} (
     * <code>-1</code>). A startIndex larger than the array length will search
     * from the end of the array.
     * </p>
     * 
     * @param array the array to traversee for looking for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @param startIndex the start index to traverse backwards from
     * @return the last index of the value within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int lastIndexOf(byte[] array, byte valueToFind, int startIndex)
    {
        if (array == null) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            return INDEX_NOT_FOUND;
        } else if (startIndex >= array.length) {
            startIndex = array.length - 1;
        }
        for (int i = startIndex; i >= 0; i--) {
            if (valueToFind == array[i]) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Finds the last index of the given value within the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * @param array the array to traverse backwords looking for the object, may
     *            be <code>null</code>
     * @param valueToFind the object to find
     * @return the last index of the value within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     * @since 2.1
     */
    public static int lastIndexOf(char[] array, char valueToFind)
    {
        return lastIndexOf(array, valueToFind, Integer.MAX_VALUE);
    }

    /**
     * <p>
     * Finds the last index of the given value in the array starting at the
     * given index.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex will return {@link #INDEX_NOT_FOUND} (
     * <code>-1</code>). A startIndex larger than the array length will search
     * from the end of the array.
     * </p>
     * 
     * @param array the array to traversee for looking for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @param startIndex the start index to traverse backwards from
     * @return the last index of the value within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     * @since 2.1
     */
    public static int lastIndexOf(char[] array, char valueToFind, int startIndex)
    {
        if (array == null) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            return INDEX_NOT_FOUND;
        } else if (startIndex >= array.length) {
            startIndex = array.length - 1;
        }
        for (int i = startIndex; i >= 0; i--) {
            if (valueToFind == array[i]) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Finds the last index of the given value within the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * @param array the array to traverse backwords looking for the object, may
     *            be <code>null</code>
     * @param valueToFind the object to find
     * @return the last index of the value within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int lastIndexOf(double[] array, double valueToFind)
    {
        return lastIndexOf(array, valueToFind, Integer.MAX_VALUE);
    }

    /**
     * <p>
     * Finds the last index of the given value in the array starting at the
     * given index. This method will return the index of the last value which
     * falls between the region defined by valueToFind - tolerance and
     * valueToFind + tolerance.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex will return {@link #INDEX_NOT_FOUND} (
     * <code>-1</code>). A startIndex larger than the array length will search
     * from the end of the array.
     * </p>
     * 
     * @param array the array to traversee for looking for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @param startIndex the start index to traverse backwards from
     * @param tolerance search for value within plus/minus this amount
     * @return the last index of the value within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int lastIndexOf(
        double[] array,
        double valueToFind,
        int startIndex)
    {
        if (ArrayUtils.isEmpty(array)) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            return INDEX_NOT_FOUND;
        } else if (startIndex >= array.length) {
            startIndex = array.length - 1;
        }
        for (int i = startIndex; i >= 0; i--) {
            if (abs(array[i] - valueToFind) < DBL_EPSILON) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Finds the last index of the given value within the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * @param array the array to traverse backwords looking for the object, may
     *            be <code>null</code>
     * @param valueToFind the object to find
     * @return the last index of the value within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int lastIndexOf(int[] array, int valueToFind)
    {
        return lastIndexOf(array, valueToFind, Integer.MAX_VALUE);
    }

    /**
     * <p>
     * Finds the last index of the given value in the array starting at the
     * given index.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex will return {@link #INDEX_NOT_FOUND} (
     * <code>-1</code>). A startIndex larger than the array length will search
     * from the end of the array.
     * </p>
     * 
     * @param array the array to traversee for looking for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @param startIndex the start index to traverse backwards from
     * @return the last index of the value within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int lastIndexOf(int[] array, int valueToFind, int startIndex)
    {
        if (array == null) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            return INDEX_NOT_FOUND;
        } else if (startIndex >= array.length) {
            startIndex = array.length - 1;
        }
        for (int i = startIndex; i >= 0; i--) {
            if (valueToFind == array[i]) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Finds the last index of the given value within the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * @param array the array to traverse backwords looking for the object, may
     *            be <code>null</code>
     * @param valueToFind the object to find
     * @return the last index of the value within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int lastIndexOf(long[] array, long valueToFind)
    {
        return lastIndexOf(array, valueToFind, Integer.MAX_VALUE);
    }

    /**
     * <p>
     * Finds the last index of the given value in the array starting at the
     * given index.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex will return {@link #INDEX_NOT_FOUND} (
     * <code>-1</code>). A startIndex larger than the array length will search
     * from the end of the array.
     * </p>
     * 
     * @param array the array to traversee for looking for the object, may be
     *            <code>null</code>
     * @param valueToFind the value to find
     * @param startIndex the start index to traverse backwards from
     * @return the last index of the value within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int lastIndexOf(long[] array, long valueToFind, int startIndex)
    {
        if (array == null) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            return INDEX_NOT_FOUND;
        } else if (startIndex >= array.length) {
            startIndex = array.length - 1;
        }
        for (int i = startIndex; i >= 0; i--) {
            if (valueToFind == array[i]) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>
     * Finds the last index of the given object within the array.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * @param array the array to traverse backwords looking for the object, may
     *            be <code>null</code>
     * @param objectToFind the object to find, may be <code>null</code>
     * @return the last index of the object within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int lastIndexOf(Object[] array, Object objectToFind)
    {
        return lastIndexOf(array, objectToFind, Integer.MAX_VALUE);
    }

    /**
     * <p>
     * Finds the last index of the given object in the array starting at the
     * given index.
     * </p>
     * 
     * <p>
     * This method returns {@link #INDEX_NOT_FOUND} (<code>-1</code>) for a
     * <code>null</code> input array.
     * </p>
     * 
     * <p>
     * A negative startIndex will return {@link #INDEX_NOT_FOUND} (
     * <code>-1</code>). A startIndex larger than the array length will search
     * from the end of the array.
     * </p>
     * 
     * @param array the array to traversee for looking for the object, may be
     *            <code>null</code>
     * @param objectToFind the object to find, may be <code>null</code>
     * @param startIndex the start index to traverse backwards from
     * @return the last index of the object within the array,
     *         {@link #INDEX_NOT_FOUND} (<code>-1</code>) if not found or
     *         <code>null</code> array input
     */
    public static int lastIndexOf(
        Object[] array,
        Object objectToFind,
        int startIndex)
    {
        if (array == null) {
            return INDEX_NOT_FOUND;
        }
        if (startIndex < 0) {
            return INDEX_NOT_FOUND;
        } else if (startIndex >= array.length) {
            startIndex = array.length - 1;
        }
        if (objectToFind == null) {
            for (int i = startIndex; i >= 0; i--) {
                if (array[i] == null) {
                    return i;
                }
            }
        } else if (array.getClass().getComponentType().isInstance(objectToFind)) {
            for (int i = startIndex; i >= 0; i--) {
                if (objectToFind.equals(array[i])) {
                    return i;
                }
            }
        }
        return INDEX_NOT_FOUND;
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // isEmpty(array)
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Checks if an array of primitive booleans is empty or <code>null</code>.
     * </p>
     * 
     * @param array the array to test
     * @return <code>true</code> if the array is empty or <code>null</code>
     * @since 2.1
     */
    public static boolean isEmpty(boolean[] array)
    {
        if (array == null || array.length == 0) {
            return true;
        }
        return false;
    }

    /**
     * <p>
     * Checks if an array of primitive bytes is empty or <code>null</code>.
     * </p>
     * 
     * @param array the array to test
     * @return <code>true</code> if the array is empty or <code>null</code>
     * @since 2.1
     */
    public static boolean isEmpty(byte[] array)
    {
        if (array == null || array.length == 0) {
            return true;
        }
        return false;
    }

    /**
     * <p>
     * Checks if an array of primitive chars is empty or <code>null</code>.
     * </p>
     * 
     * @param array the array to test
     * @return <code>true</code> if the array is empty or <code>null</code>
     * @since 2.1
     */
    public static boolean isEmpty(char[] array)
    {
        if (array == null || array.length == 0) {
            return true;
        }
        return false;
    }

    /**
     * <p>
     * Checks if an array of primitive doubles is empty or <code>null</code>.
     * </p>
     * 
     * @param array the array to test
     * @return <code>true</code> if the array is empty or <code>null</code>
     * @since 2.1
     */
    public static boolean isEmpty(double[] array)
    {
        if (array == null || array.length == 0) {
            return true;
        }
        return false;
    }

    /**
     * <p>
     * Checks if an array of primitive ints is empty or <code>null</code>.
     * </p>
     * 
     * @param array the array to test
     * @return <code>true</code> if the array is empty or <code>null</code>
     * @since 2.1
     */
    public static boolean isEmpty(int[] array)
    {
        if (array == null || array.length == 0) {
            return true;
        }
        return false;
    }

    /**
     * <p>
     * Checks if an array of primitive longs is empty or <code>null</code>.
     * </p>
     * 
     * @param array the array to test
     * @return <code>true</code> if the array is empty or <code>null</code>
     * @since 2.1
     */
    public static boolean isEmpty(long[] array)
    {
        if (array == null || array.length == 0) {
            return true;
        }
        return false;
    }

    /**
     * <p>
     * Checks if an array of Objects is empty or <code>null</code>.
     * </p>
     * 
     * @param array the array to test
     * @return <code>true</code> if the array is empty or <code>null</code>
     * @since 2.1
     */
    public static <T> boolean isEmpty(T[] array)
    {
        if (array == null || array.length == 0) {
            return true;
        }
        return false;
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // isSameLength(array1, array2)
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Checks whether two arrays are the same length, treating <code>null</code>
     * arrays as length <code>0</code>.
     * </p>
     * 
     * @param array1 the first array, may be <code>null</code>
     * @param array2 the second array, may be <code>null</code>
     * @return <code>true</code> if length of arrays matches, treating
     *         <code>null</code> as an empty array
     */
    public static boolean isSameLength(boolean[] array1, boolean[] array2)
    {
        if ((array1 == null && array2 != null && array2.length > 0)
                        || (array2 == null && array1 != null && array1.length > 0)
                        || (array1 != null && array2 != null && array1.length != array2.length)) {
            return false;
        }
        return true;
    }

    /**
     * <p>
     * Checks whether two arrays are the same length, treating <code>null</code>
     * arrays as length <code>0</code>.
     * </p>
     * 
     * @param array1 the first array, may be <code>null</code>
     * @param array2 the second array, may be <code>null</code>
     * @return <code>true</code> if length of arrays matches, treating
     *         <code>null</code> as an empty array
     */
    public static boolean isSameLength(byte[] array1, byte[] array2)
    {
        if ((array1 == null && array2 != null && array2.length > 0)
                        || (array2 == null && array1 != null && array1.length > 0)
                        || (array1 != null && array2 != null && array1.length != array2.length)) {
            return false;
        }
        return true;
    }

    /**
     * <p>
     * Checks whether two arrays are the same length, treating <code>null</code>
     * arrays as length <code>0</code>.
     * </p>
     * 
     * @param array1 the first array, may be <code>null</code>
     * @param array2 the second array, may be <code>null</code>
     * @return <code>true</code> if length of arrays matches, treating
     *         <code>null</code> as an empty array
     */
    public static boolean isSameLength(char[] array1, char[] array2)
    {
        if ((array1 == null && array2 != null && array2.length > 0)
                        || (array2 == null && array1 != null && array1.length > 0)
                        || (array1 != null && array2 != null && array1.length != array2.length)) {
            return false;
        }
        return true;
    }

    /**
     * <p>
     * Checks whether two arrays are the same length, treating <code>null</code>
     * arrays as length <code>0</code>.
     * </p>
     * 
     * @param array1 the first array, may be <code>null</code>
     * @param array2 the second array, may be <code>null</code>
     * @return <code>true</code> if length of arrays matches, treating
     *         <code>null</code> as an empty array
     */
    public static boolean isSameLength(double[] array1, double[] array2)
    {
        if ((array1 == null && array2 != null && array2.length > 0)
                        || (array2 == null && array1 != null && array1.length > 0)
                        || (array1 != null && array2 != null && array1.length != array2.length)) {
            return false;
        }
        return true;
    }

    /**
     * <p>
     * Checks whether two arrays are the same length, treating <code>null</code>
     * arrays as length <code>0</code>.
     * </p>
     * 
     * @param array1 the first array, may be <code>null</code>
     * @param array2 the second array, may be <code>null</code>
     * @return <code>true</code> if length of arrays matches, treating
     *         <code>null</code> as an empty array
     */
    public static boolean isSameLength(int[] array1, int[] array2)
    {
        if ((array1 == null && array2 != null && array2.length > 0)
                        || (array2 == null && array1 != null && array1.length > 0)
                        || (array1 != null && array2 != null && array1.length != array2.length)) {
            return false;
        }
        return true;
    }

    /**
     * <p>
     * Checks whether two arrays are the same length, treating <code>null</code>
     * arrays as length <code>0</code>.
     * </p>
     * 
     * @param array1 the first array, may be <code>null</code>
     * @param array2 the second array, may be <code>null</code>
     * @return <code>true</code> if length of arrays matches, treating
     *         <code>null</code> as an empty array
     */
    public static boolean isSameLength(long[] array1, long[] array2)
    {
        if ((array1 == null && array2 != null && array2.length > 0)
                        || (array2 == null && array1 != null && array1.length > 0)
                        || (array1 != null && array2 != null && array1.length != array2.length)) {
            return false;
        }
        return true;
    }

    /**
     * <p>
     * Checks whether two arrays are the same length, treating <code>null</code>
     * arrays as length <code>0</code>.
     * 
     * <p>
     * Any multi-dimensional aspects of the arrays are ignored.
     * </p>
     * 
     * @param array1 the first array, may be <code>null</code>
     * @param array2 the second array, may be <code>null</code>
     * @return <code>true</code> if length of arrays matches, treating
     *         <code>null</code> as an empty array
     */
    public static boolean isSameLength(Object[] array1, Object[] array2)
    {
        if ((array1 == null && array2 != null && array2.length > 0)
                        || (array2 == null && array1 != null && array1.length > 0)
                        || (array1 != null && array2 != null && array1.length != array2.length)) {
            return false;
        }
        return true;
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // reverse(array)
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Reverses the order of the given array.
     * </p>
     * 
     * <p>
     * This method does nothing for a <code>null</code> input array.
     * </p>
     * 
     * @param array the array to reverse, may be <code>null</code>
     */
    public static void reverse(boolean[] array)
    {
        if (array == null) {
            return;
        }
        int i = 0;
        int j = array.length - 1;
        boolean tmp;
        while (j > i) {
            tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
            j--;
            i++;
        }
    }

    /**
     * <p>
     * Reverses the order of the given array.
     * </p>
     * 
     * <p>
     * This method does nothing for a <code>null</code> input array.
     * </p>
     * 
     * @param array the array to reverse, may be <code>null</code>
     */
    public static void reverse(byte[] array)
    {
        if (array == null) {
            return;
        }
        int i = 0;
        int j = array.length - 1;
        byte tmp;
        while (j > i) {
            tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
            j--;
            i++;
        }
    }

    /**
     * <p>
     * Reverses the order of the given array.
     * </p>
     * 
     * <p>
     * This method does nothing for a <code>null</code> input array.
     * </p>
     * 
     * @param array the array to reverse, may be <code>null</code>
     */
    public static void reverse(char[] array)
    {
        if (array == null) {
            return;
        }
        int i = 0;
        int j = array.length - 1;
        char tmp;
        while (j > i) {
            tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
            j--;
            i++;
        }
    }

    /**
     * <p>
     * Reverses the order of the given array.
     * </p>
     * 
     * <p>
     * This method does nothing for a <code>null</code> input array.
     * </p>
     * 
     * @param array the array to reverse, may be <code>null</code>
     */
    public static void reverse(double[] array)
    {
        if (array == null) {
            return;
        }
        int i = 0;
        int j = array.length - 1;
        double tmp;
        while (j > i) {
            tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
            j--;
            i++;
        }
    }

    /**
     * <p>
     * Reverses the order of the given array.
     * </p>
     * 
     * <p>
     * This method does nothing for a <code>null</code> input array.
     * </p>
     * 
     * @param array the array to reverse, may be <code>null</code>
     */
    public static void reverse(int[] array)
    {
        if (array == null) {
            return;
        }
        int i = 0;
        int j = array.length - 1;
        int tmp;
        while (j > i) {
            tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
            j--;
            i++;
        }
    }

    /**
     * <p>
     * Reverses the order of the given array.
     * </p>
     * 
     * <p>
     * This method does nothing for a <code>null</code> input array.
     * </p>
     * 
     * @param array the array to reverse, may be <code>null</code>
     */
    public static void reverse(long[] array)
    {
        if (array == null) {
            return;
        }
        int i = 0;
        int j = array.length - 1;
        long tmp;
        while (j > i) {
            tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
            j--;
            i++;
        }
    }

    /**
     * <p>
     * Reverses the order of the given array.
     * </p>
     * 
     * <p>
     * There is no special handling for multi-dimensional arrays.
     * </p>
     * 
     * <p>
     * This method does nothing for a <code>null</code> input array.
     * </p>
     * 
     * @param array the array to reverse, may be <code>null</code>
     */
    public static void reverse(Object[] array)
    {
        if (array == null) {
            return;
        }
        int i = 0;
        int j = array.length - 1;
        Object tmp;
        while (j > i) {
            tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;
            j--;
            i++;
        }
    }
}
