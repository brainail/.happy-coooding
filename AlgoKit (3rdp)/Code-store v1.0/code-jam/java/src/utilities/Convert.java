package utilities;

import java.util.*;

/**
 * Primitive/Object array converters for selected primitive data types:
 * { boolean, byte, char, double, int, long }
 */
public class Convert
{
    /**
     * used in {@link Character#toObject(char)}
     */
    private static final Character[] CHAR_ARRAY = new Character[128];
    static {
        for (int i = 127; i >= 0; i--) {
            CHAR_ARRAY[i] = new Character((char) i);
        }
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // toObject()
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Converts an array of primitive booleans to objects.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>boolean</code> array
     * @return a <code>Boolean</code> array, <code>null</code> if null array
     *         input
     */
    public static Boolean[] toObject(boolean[] array)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final Boolean[] result = new Boolean[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = (array[i] ? Boolean.TRUE : Boolean.FALSE);
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of primitive bytes to objects.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>byte</code> array
     * @return a <code>Byte</code> array, <code>null</code> if null array input
     */
    public static Byte[] toObject(byte[] array)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final Byte[] result = new Byte[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = Byte.valueOf(array[i]);
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of primitive chars to objects.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>char</code> array
     * @return a <code>Character</code> array, <code>null</code> if null array
     *         input
     */
    public static Character[] toObject(char[] array)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final Character[] result = new Character[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = Character.valueOf(array[i]);
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of primitive doubles to objects.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>double</code> array
     * @return a <code>Double</code> array, <code>null</code> if null array
     *         input
     */
    public static Double[] toObject(double[] array)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final Double[] result = new Double[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = Double.valueOf(array[i]);
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of primitive ints to objects.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array an <code>int</code> array
     * @return an <code>Integer</code> array, <code>null</code> if null array
     *         input
     */
    public static Integer[] toObject(int[] array)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final Integer[] result = new Integer[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = Integer.valueOf(array[i]);
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of primitive longs to objects.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>long</code> array
     * @return a <code>Long</code> array, <code>null</code> if null array input
     */
    public static Long[] toObject(long[] array)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final Long[] result = new Long[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = Long.valueOf(array[i]);
        }
        return result;
    }

    /**
     * <p>
     * Converts the character to a Character.
     * </p>
     * 
     * <p>
     * For ASCII 7 bit characters, this uses a cache that will return the same
     * Character object each time.
     * </p>
     * 
     * <pre>
     *   CharUtils.toCharacterObject(' ')  = ' '
     *   CharUtils.toCharacterObject('A')  = 'A'
     * </pre>
     * 
     * @param ch the character to convert
     * @return a Character of the specified character
     */
    public static Character toObject(char ch)
    {
        if (ch < CHAR_ARRAY.length) {
            return CHAR_ARRAY[ch];
        }
        return new Character(ch);
    }

    public static Integer[][] toObject(int[][] array)
    {
        Integer[][] result = new Integer[array.length][array[0].length];
        for (int i = 0; i < array.length; i++) {
            for (int j = 0; j < array[0].length; j++) {
                result[i][j] = array[i][j];
            }
        }
        return result;
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // toPrimitive(array, valueForNull)
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Converts an array of object Booleans to primitives.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>Boolean</code> array, may be <code>null</code>
     * @return a <code>boolean</code> array, <code>null</code> if null array
     *         input
     * @throws NullPointerException if array content is <code>null</code>
     */
    public static boolean[] toPrimitive(Boolean[] array)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final boolean[] result = new boolean[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = array[i].booleanValue();
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of object Booleans to primitives handling
     * <code>null</code>.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>Boolean</code> array, may be <code>null</code>
     * @param valueForNull the value to insert if <code>null</code> found
     * @return a <code>boolean</code> array, <code>null</code> if null array
     *         input
     */
    public static boolean[] toPrimitive(Boolean[] array, boolean valueForNull)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final boolean[] result = new boolean[array.length];
        for (int i = 0; i < array.length; i++) {
            Boolean b = array[i];
            result[i] = (b == null ? valueForNull : b.booleanValue());
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of object Bytes to primitives.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>Byte</code> array, may be <code>null</code>
     * @return a <code>byte</code> array, <code>null</code> if null array input
     * @throws NullPointerException if array content is <code>null</code>
     */
    public static byte[] toPrimitive(Byte[] array)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final byte[] result = new byte[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = array[i].byteValue();
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of object Bytes to primitives handling
     * <code>null</code>.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>Byte</code> array, may be <code>null</code>
     * @param valueForNull the value to insert if <code>null</code> found
     * @return a <code>byte</code> array, <code>null</code> if null array input
     */
    public static byte[] toPrimitive(Byte[] array, byte valueForNull)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final byte[] result = new byte[array.length];
        for (int i = 0; i < array.length; i++) {
            Byte b = array[i];
            result[i] = (b == null ? valueForNull : b.byteValue());
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of object Characters to primitives.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>Character</code> array, may be <code>null</code>
     * @return a <code>char</code> array, <code>null</code> if null array input
     * @throws NullPointerException if array content is <code>null</code>
     */
    public static char[] toPrimitive(Character[] array)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final char[] result = new char[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = array[i].charValue();
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of object Character to primitives handling
     * <code>null</code>.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>Character</code> array, may be <code>null</code>
     * @param valueForNull the value to insert if <code>null</code> found
     * @return a <code>char</code> array, <code>null</code> if null array input
     */
    public static char[] toPrimitive(Character[] array, char valueForNull)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final char[] result = new char[array.length];
        for (int i = 0; i < array.length; i++) {
            Character b = array[i];
            result[i] = (b == null ? valueForNull : b.charValue());
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of object Doubles to primitives.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>Double</code> array, may be <code>null</code>
     * @return a <code>double</code> array, <code>null</code> if null array
     *         input
     * @throws NullPointerException if array content is <code>null</code>
     */
    public static double[] toPrimitive(Double[] array)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final double[] result = new double[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = array[i].doubleValue();
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of object Doubles to primitives handling
     * <code>null</code>.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>Double</code> array, may be <code>null</code>
     * @param valueForNull the value to insert if <code>null</code> found
     * @return a <code>double</code> array, <code>null</code> if null array
     *         input
     */
    public static double[] toPrimitive(Double[] array, double valueForNull)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final double[] result = new double[array.length];
        for (int i = 0; i < array.length; i++) {
            Double b = array[i];
            result[i] = (b == null ? valueForNull : b.doubleValue());
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of object Integers to primitives.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>Integer</code> array, may be <code>null</code>
     * @return an <code>int</code> array, <code>null</code> if null array input
     * @throws NullPointerException if array content is <code>null</code>
     */
    public static int[] toPrimitive(Integer[] array)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final int[] result = new int[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = array[i].intValue();
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of object Integer to primitives handling
     * <code>null</code>.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>Integer</code> array, may be <code>null</code>
     * @param valueForNull the value to insert if <code>null</code> found
     * @return an <code>int</code> array, <code>null</code> if null array input
     */
    public static int[] toPrimitive(Integer[] array, int valueForNull)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final int[] result = new int[array.length];
        for (int i = 0; i < array.length; i++) {
            Integer b = array[i];
            result[i] = (b == null ? valueForNull : b.intValue());
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of object Longs to primitives.
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>Long</code> array, may be <code>null</code>
     * @return a <code>long</code> array, <code>null</code> if null array input
     * @throws NullPointerException if array content is <code>null</code>
     */
    public static long[] toPrimitive(Long[] array)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final long[] result = new long[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = array[i].longValue();
        }
        return result;
    }

    /**
     * <p>
     * Converts an array of object Long to primitives handling <code>null</code>
     * .
     * </p>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array a <code>Long</code> array, may be <code>null</code>
     * @param valueForNull the value to insert if <code>null</code> found
     * @return a <code>long</code> array, <code>null</code> if null array input
     */
    public static long[] toPrimitive(Long[] array, long valueForNull)
    {
        if (array == null || array.length == 0) {
            return null;
        }
        final long[] result = new long[array.length];
        for (int i = 0; i < array.length; i++) {
            Long b = array[i];
            result[i] = (b == null ? valueForNull : b.longValue());
        }
        return result;
    }

    /**
     * <p>
     * Converts a Boolean to a boolean handling <code>null</code> by returning
     * <code>false</code>.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toBoolean(Boolean.TRUE)  = true
     *   BooleanUtils.toBoolean(Boolean.FALSE) = false
     *   BooleanUtils.toBoolean(null)          = false
     * </pre>
     * 
     * @param bool the boolean to convert
     * @return <code>true</code> or <code>false</code>, <code>null</code>
     *         returns <code>false</code>
     */
    public static boolean toPrimitive(Boolean bool)
    {
        if (bool == null) {
            return false;
        }
        return bool.booleanValue() ? true : false;
    }

    /**
     * <p>
     * Converts a Boolean to a boolean handling <code>null</code>.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toBooleanDefaultIfNull(Boolean.TRUE, false) = true
     *   BooleanUtils.toBooleanDefaultIfNull(Boolean.FALSE, true) = false
     *   BooleanUtils.toBooleanDefaultIfNull(null, true)          = true
     * </pre>
     * 
     * @param bool the boolean to convert
     * @param valueIfNull the boolean value to return if <code>null</code>
     * @return <code>true</code> or <code>false</code>
     */
    public static boolean toPrimitive(Boolean bool, boolean valueForNull)
    {
        if (bool == null) {
            return valueForNull;
        }
        return bool.booleanValue() ? true : false;
    }

    /**
     * <p>
     * Converts the Character to a char throwing an exception for
     * <code>null</code>.
     * </p>
     * 
     * <pre>
     *   CharUtils.toChar(null) = IllegalArgumentException
     *   CharUtils.toChar(' ')  = ' '
     *   CharUtils.toChar('A')  = 'A'
     * </pre>
     * 
     * @param ch the character to convert
     * @return the char value of the Character
     * @throws IllegalArgumentException if the Character is null
     */
    public static char toPrimitive(Character ch)
    {
        if (ch == null) {
            throw new IllegalArgumentException("The Character must not be null");
        }
        return ch.charValue();
    }

    /**
     * <p>
     * Converts the Character to a char handling <code>null</code>.
     * </p>
     * 
     * <pre>
     *   CharUtils.toChar(null, 'X') = 'X'
     *   CharUtils.toChar(' ', 'X')  = ' '
     *   CharUtils.toChar('A', 'X')  = 'A'
     * </pre>
     * 
     * @param ch the character to convert
     * @param defaultValue the value to use if the Character is null
     * @return the char value of the Character or the default if null
     */
    public static char toPrimitive(Character ch, char valueForNull)
    {
        if (ch == null) {
            return valueForNull;
        }
        return ch.charValue();
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // Integer <=> Boolean conversions
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Converts an int to a boolean using the convention that <code>zero</code>
     * is <code>false</code>.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toBoolean(0) = false
     *   BooleanUtils.toBoolean(1) = true
     *   BooleanUtils.toBoolean(2) = true
     * </pre>
     * 
     * @param value the int to convert
     * @return <code>true</code> if non-zero, <code>false</code> if zero
     */
    public static boolean intToBoolean(int value)
    {
        return value == 0 ? false : true;
    }

    /**
     * <p>
     * Converts an int to a boolean specifying the conversion values.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toBoolean(0, 1, 0) = false
     *   BooleanUtils.toBoolean(1, 1, 0) = true
     *   BooleanUtils.toBoolean(2, 1, 2) = false
     *   BooleanUtils.toBoolean(2, 2, 0) = true
     * </pre>
     * 
     * @param value the Integer to convert
     * @param trueValue the value to match for <code>true</code>
     * @param falseValue the value to match for <code>false</code>
     * @return <code>true</code> or <code>false</code>
     * @throws IllegalArgumentException if no match
     */
    public static boolean intToBoolean(int value, int trueValue, int falseValue)
    {
        if (value == trueValue) {
            return true;
        } else if (value == falseValue) {
            return false;
        }
        // no match
        throw new IllegalArgumentException(
                        "The Integer did not match either specified value");
    }

    /**
     * <p>
     * Converts an int to a Boolean using the convention that <code>zero</code>
     * is <code>false</code>.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toBoolean(0) = Boolean.FALSE
     *   BooleanUtils.toBoolean(1) = Boolean.TRUE
     *   BooleanUtils.toBoolean(2) = Boolean.TRUE
     * </pre>
     * 
     * @param value the int to convert
     * @return Boolean.TRUE if non-zero, Boolean.FALSE if zero,
     *         <code>null</code> if <code>null</code>
     */
    public static Boolean intToBooleanObject(int value)
    {
        return value == 0 ? Boolean.FALSE : Boolean.TRUE;
    }

    /**
     * <p>
     * Converts an Integer to a Boolean using the convention that
     * <code>zero</code> is <code>false</code>.
     * </p>
     * 
     * <p>
     * <code>null</code> will be converted to <code>null</code>.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toBoolean(new Integer(0))    = Boolean.FALSE
     *   BooleanUtils.toBoolean(new Integer(1))    = Boolean.TRUE
     *   BooleanUtils.toBoolean(new Integer(null)) = null
     * </pre>
     * 
     * @param value the Integer to convert
     * @return Boolean.TRUE if non-zero, Boolean.FALSE if zero,
     *         <code>null</code> if <code>null</code> input
     */
    public static Boolean integerToBooleanObject(Integer value)
    {
        if (value == null) {
            return null;
        }
        return value.intValue() == 0 ? Boolean.FALSE : Boolean.TRUE;
    }

    /**
     * <p>
     * Converts an Integer to a boolean specifying the conversion values.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toBoolean(new Integer(0), new Integer(1), new Integer(0)) = false
     *   BooleanUtils.toBoolean(new Integer(1), new Integer(1), new Integer(0)) = true
     *   BooleanUtils.toBoolean(new Integer(2), new Integer(1), new Integer(2)) = false
     *   BooleanUtils.toBoolean(new Integer(2), new Integer(2), new Integer(0)) = true
     *   BooleanUtils.toBoolean(null, null, new Integer(0))                     = true
     * </pre>
     * 
     * @param value the Integer to convert
     * @param trueValue the value to match for <code>true</code>, may be
     *            <code>null</code>
     * @param falseValue the value to match for <code>false</code>, may be
     *            <code>null</code>
     * @return <code>true</code> or <code>false</code>
     * @throws IllegalArgumentException if no match
     */
    public static boolean integerToBoolean(
        Integer value,
        Integer trueValue,
        Integer falseValue)
    {
        if (value == null) {
            if (trueValue == null) {
                return true;
            } else if (falseValue == null) {
                return false;
            }
        } else if (value.equals(trueValue)) {
            return true;
        } else if (value.equals(falseValue)) {
            return false;
        }
        // no match
        throw new IllegalArgumentException(
                        "The Integer did not match either specified value");
    }

    /**
     * <p>
     * Converts an int to a Boolean specifying the conversion values.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toBooleanObject(0, 0, 2, 3) = Boolean.TRUE
     *   BooleanUtils.toBooleanObject(2, 1, 2, 3) = Boolean.FALSE
     *   BooleanUtils.toBooleanObject(3, 1, 2, 3) = null
     * </pre>
     * 
     * @param value the Integer to convert
     * @param trueValue the value to match for <code>true</code>
     * @param falseValue the value to match for <code>false</code>
     * @param nullValue the value to to match for <code>null</code>
     * @return Boolean.TRUE, Boolean.FALSE, or <code>null</code>
     * @throws IllegalArgumentException if no match
     */
    public static Boolean intToBooleanObject(
        int value,
        int trueValue,
        int falseValue,
        int nullValue)
    {
        if (value == trueValue) {
            return Boolean.TRUE;
        } else if (value == falseValue) {
            return Boolean.FALSE;
        } else if (value == nullValue) {
            return null;
        }
        // no match
        throw new IllegalArgumentException(
                        "The Integer did not match any specified value");
    }

    /**
     * <p>
     * Converts an Integer to a Boolean specifying the conversion values.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toBooleanObject(new Integer(0), new Integer(0), new Integer(2), new Integer(3)) = Boolean.TRUE
     *   BooleanUtils.toBooleanObject(new Integer(2), new Integer(1), new Integer(2), new Integer(3)) = Boolean.FALSE
     *   BooleanUtils.toBooleanObject(new Integer(3), new Integer(1), new Integer(2), new Integer(3)) = null
     * </pre>
     * 
     * @param value the Integer to convert
     * @param trueValue the value to match for <code>true</code>, may be
     *            <code>null</code>
     * @param falseValue the value to match for <code>false</code>, may be
     *            <code>null</code>
     * @param nullValue the value to to match for <code>null</code>, may be
     *            <code>null</code>
     * @return Boolean.TRUE, Boolean.FALSE, or <code>null</code>
     * @throws IllegalArgumentException if no match
     */
    public static Boolean integerToBooleanObject(
        Integer value,
        Integer trueValue,
        Integer falseValue,
        Integer nullValue)
    {
        if (value == null) {
            if (trueValue == null) {
                return Boolean.TRUE;
            } else if (falseValue == null) {
                return Boolean.FALSE;
            } else if (nullValue == null) {
                return null;
            }
        } else if (value.equals(trueValue)) {
            return Boolean.TRUE;
        } else if (value.equals(falseValue)) {
            return Boolean.FALSE;
        } else if (value.equals(nullValue)) {
            return null;
        }
        // no match
        throw new IllegalArgumentException(
                        "The Integer did not match any specified value");
    }

    /**
     * <p>
     * Converts a boolean to an int using the convention that <code>zero</code>
     * is <code>false</code>.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toInteger(true)  = 1
     *   BooleanUtils.toInteger(false) = 0
     * </pre>
     * 
     * @param bool the boolean to convert
     * @return one if <code>true</code>, zero if <code>false</code>
     */
    public static int boolToInt(boolean bool)
    {
        return bool ? 1 : 0;
    }

    /**
     * <p>
     * Converts a boolean to an Integer using the convention that
     * <code>zero</code> is <code>false</code>.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toIntegerObject(true)  = new Integer(1)
     *   BooleanUtils.toIntegerObject(false) = new Integer(0)
     * </pre>
     * 
     * @param bool the boolean to convert
     * @return one if <code>true</code>, zero if <code>false</code>
     */
    public static Integer booleanToInteger(boolean bool)
    {
        return bool ? new Integer(1) : new Integer(0);
    }

    /**
     * <p>
     * Converts a Boolean to a Integer using the convention that
     * <code>zero</code> is <code>false</code>.
     * </p>
     * 
     * <p>
     * <code>null</code> will be converted to <code>null</code>.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toIntegerObject(Boolean.TRUE)  = new Integer(1)
     *   BooleanUtils.toIntegerObject(Boolean.FALSE) = new Integer(0)
     * </pre>
     * 
     * @param bool the Boolean to convert
     * @return one if Boolean.TRUE, zero if Boolean.FALSE, <code>null</code> if
     *         <code>null</code>
     */
    public static Integer booleanToInteger(Boolean bool)
    {
        if (bool == null) {
            return null;
        }
        return bool.booleanValue() ? new Integer(1) : new Integer(0);
    }

    /**
     * <p>
     * Converts a boolean to an int specifying the conversion values.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toInteger(true, 1, 0)  = 1
     *   BooleanUtils.toInteger(false, 1, 0) = 0
     * </pre>
     * 
     * @param bool the to convert
     * @param trueValue the value to return if <code>true</code>
     * @param falseValue the value to return if <code>false</code>
     * @return the appropriate value
     */
    public static int booleanToInt(boolean bool, int trueValue, int falseValue)
    {
        return bool ? trueValue : falseValue;
    }

    /**
     * <p>
     * Converts a Boolean to an int specifying the conversion values.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toInteger(Boolean.TRUE, 1, 0, 2)  = 1
     *   BooleanUtils.toInteger(Boolean.FALSE, 1, 0, 2) = 0
     *   BooleanUtils.toInteger(null, 1, 0, 2)          = 2
     * </pre>
     * 
     * @param bool the Boolean to convert
     * @param trueValue the value to return if <code>true</code>
     * @param falseValue the value to return if <code>false</code>
     * @param nullValue the value to return if <code>null</code>
     * @return the appropriate value
     */
    public static int booleanToInt(
        Boolean bool,
        int trueValue,
        int falseValue,
        int nullValue)
    {
        if (bool == null) {
            return nullValue;
        }
        return bool.booleanValue() ? trueValue : falseValue;
    }

    /**
     * <p>
     * Converts a boolean to an Integer specifying the conversion values.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toIntegerObject(true, new Integer(1), new Integer(0))  = new Integer(1)
     *   BooleanUtils.toIntegerObject(false, new Integer(1), new Integer(0)) = new Integer(0)
     * </pre>
     * 
     * @param bool the to convert
     * @param trueValue the value to return if <code>true</code>, may be
     *            <code>null</code>
     * @param falseValue the value to return if <code>false</code>, may be
     *            <code>null</code>
     * @return the appropriate value
     */
    public static Integer booleanToInteger(
        boolean bool,
        Integer trueValue,
        Integer falseValue)
    {
        return bool ? trueValue : falseValue;
    }

    /**
     * <p>
     * Converts a Boolean to an Integer specifying the conversion values.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toIntegerObject(Boolean.TRUE, new Integer(1), new Integer(0), new Integer(2))  = new Integer(1)
     *   BooleanUtils.toIntegerObject(Boolean.FALSE, new Integer(1), new Integer(0), new Integer(2)) = new Integer(0)
     *   BooleanUtils.toIntegerObject(null, new Integer(1), new Integer(0), new Integer(2))          = new Integer(2)
     * </pre>
     * 
     * @param bool the Boolean to convert
     * @param trueValue the value to return if <code>true</code>, may be
     *            <code>null</code>
     * @param falseValue the value to return if <code>false</code>, may be
     *            <code>null</code>
     * @param nullValue the value to return if <code>null</code>, may be
     *            <code>null</code>
     * @return the appropriate value
     */
    public static Integer booleanObjectToInteger(
        Boolean bool,
        Integer trueValue,
        Integer falseValue,
        Integer nullValue)
    {
        if (bool == null) {
            return nullValue;
        }
        return bool.booleanValue() ? trueValue : falseValue;
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // String <=> Boolean conversions
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Converts a String to a Boolean.
     * </p>
     * 
     * <p>
     * <code>'true'</code>, <code>'on'</code> or <code>'yes'</code> (case
     * insensitive) will return <code>true</code>. <code>'false'</code>,
     * <code>'off'</code> or <code>'no'</code> (case insensitive) will return
     * <code>false</code>. Otherwise, <code>null</code> is returned.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toBooleanObject(null)    = null
     *   BooleanUtils.toBooleanObject("true")  = Boolean.TRUE
     *   BooleanUtils.toBooleanObject("false") = Boolean.FALSE
     *   BooleanUtils.toBooleanObject("on")    = Boolean.TRUE
     *   BooleanUtils.toBooleanObject("ON")    = Boolean.TRUE
     *   BooleanUtils.toBooleanObject("off")   = Boolean.FALSE
     *   BooleanUtils.toBooleanObject("oFf")   = Boolean.FALSE
     *   BooleanUtils.toBooleanObject("blue")  = null
     * </pre>
     * 
     * @param str the String to check
     * @return the Boolean value of the string, <code>null</code> if no match or
     *         <code>null</code> input
     */
    public static Boolean strToBooleanObject(String str)
    {
        // Previously used equalsIgnoreCase, which was fast for interned 'true'.
        // Non interned 'true' matched 15 times slower.
        //
        // Optimisation provides same performance as before for interned 'true'.
        // Similar performance for null, 'false', and other strings not length
        // 2/3/4.
        // 'true'/'TRUE' match 4 times slower, 'tRUE'/'True' 7 times slower.
        if (str == "true") {
            return Boolean.TRUE;
        }
        if (str == null) {
            return null;
        }
        switch (str.length()) {
        case 2: {
            char ch0 = str.charAt(0);
            char ch1 = str.charAt(1);
            if ((ch0 == 'o' || ch0 == 'O') && (ch1 == 'n' || ch1 == 'N')) {
                return Boolean.TRUE;
            }
            if ((ch0 == 'n' || ch0 == 'N') && (ch1 == 'o' || ch1 == 'O')) {
                return Boolean.FALSE;
            }
            break;
        }
        case 3: {
            char ch0 = str.charAt(0);
            char ch1 = str.charAt(1);
            char ch2 = str.charAt(2);
            if ((ch0 == 'y' || ch0 == 'Y') && (ch1 == 'e' || ch1 == 'E')
                            && (ch2 == 's' || ch2 == 'S')) {
                return Boolean.TRUE;
            }
            if ((ch0 == 'o' || ch0 == 'O') && (ch1 == 'f' || ch1 == 'F')
                            && (ch2 == 'f' || ch2 == 'F')) {
                return Boolean.FALSE;
            }
            break;
        }
        case 4: {
            char ch0 = str.charAt(0);
            char ch1 = str.charAt(1);
            char ch2 = str.charAt(2);
            char ch3 = str.charAt(3);
            if ((ch0 == 't' || ch0 == 'T') && (ch1 == 'r' || ch1 == 'R')
                            && (ch2 == 'u' || ch2 == 'U')
                            && (ch3 == 'e' || ch3 == 'E')) {
                return Boolean.TRUE;
            }
            break;
        }
        case 5: {
            char ch0 = str.charAt(0);
            char ch1 = str.charAt(1);
            char ch2 = str.charAt(2);
            char ch3 = str.charAt(3);
            char ch4 = str.charAt(4);
            if ((ch0 == 'f' || ch0 == 'F') && (ch1 == 'a' || ch1 == 'A')
                            && (ch2 == 'l' || ch2 == 'L')
                            && (ch3 == 's' || ch3 == 'S')
                            && (ch4 == 'e' || ch4 == 'E')) {
                return Boolean.FALSE;
            }
            break;
        }
        }

        return null;
    }

    /**
     * <p>
     * Converts a String to a Boolean throwing an exception if no match.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toBooleanObject("true", "true", "false", "null")  = Boolean.TRUE
     *   BooleanUtils.toBooleanObject("false", "true", "false", "null") = Boolean.FALSE
     *   BooleanUtils.toBooleanObject("null", "true", "false", "null")  = null
     * </pre>
     * 
     * @param str the String to check
     * @param trueString the String to match for <code>true</code> (case
     *            sensitive), may be <code>null</code>
     * @param falseString the String to match for <code>false</code> (case
     *            sensitive), may be <code>null</code>
     * @param nullString the String to match for <code>null</code> (case
     *            sensitive), may be <code>null</code>
     * @return the Boolean value of the string, <code>null</code> if either the
     *         String matches <code>nullString</code> or if <code>null</code>
     *         input and <code>nullString</code> is <code>null</code>
     * @throws IllegalArgumentException if the String doesn't match
     */
    public static Boolean strToBooleanObject(
        String str,
        String trueString,
        String falseString,
        String nullString)
    {
        if (str == null) {
            if (trueString == null) {
                return Boolean.TRUE;
            } else if (falseString == null) {
                return Boolean.FALSE;
            } else if (nullString == null) {
                return null;
            }
        } else if (str.equals(trueString)) {
            return Boolean.TRUE;
        } else if (str.equals(falseString)) {
            return Boolean.FALSE;
        } else if (str.equals(nullString)) {
            return null;
        }
        // no match
        throw new IllegalArgumentException(
                        "The String did not match any specified value");
    }

    /**
     * <p>
     * Converts a String to a boolean (optimised for performance).
     * </p>
     * 
     * <p>
     * <code>'true'</code>, <code>'on'</code> or <code>'yes'</code> (case
     * insensitive) will return <code>true</code>. Otherwise, <code>false</code>
     * is returned.
     * </p>
     * 
     * <p>
     * This method performs 4 times faster (JDK1.4) than
     * <code>Boolean.valueOf(String)</code>. However, this method accepts 'on'
     * and 'yes' as true values.
     * 
     * <pre>
     *   BooleanUtils.toBoolean(null)    = false
     *   BooleanUtils.toBoolean("true")  = true
     *   BooleanUtils.toBoolean("TRUE")  = true
     *   BooleanUtils.toBoolean("tRUe")  = true
     *   BooleanUtils.toBoolean("on")    = true
     *   BooleanUtils.toBoolean("yes")   = true
     *   BooleanUtils.toBoolean("false") = false
     *   BooleanUtils.toBoolean("x gti") = false
     * </pre>
     * 
     * @param str the String to check
     * @return the boolean value of the string, <code>false</code> if no match
     *         or the String is null
     */
    public static boolean strToBoolean(String str)
    {
        return strToBooleanObject(str) == Boolean.TRUE;
    }

    /**
     * <p>
     * Converts a String to a Boolean throwing an exception if no match found.
     * </p>
     * 
     * <p>
     * null is returned if there is no match.
     * </p>
     * 
     * <pre>
     *   BooleanUtils.toBoolean("true", "true", "false")  = true
     *   BooleanUtils.toBoolean("false", "true", "false") = false
     * </pre>
     * 
     * @param str the String to check
     * @param trueString the String to match for <code>true</code> (case
     *            sensitive), may be <code>null</code>
     * @param falseString the String to match for <code>false</code> (case
     *            sensitive), may be <code>null</code>
     * @return the boolean value of the string
     * @throws IllegalArgumentException if the String doesn't match
     */
    public static boolean strToBoolean(
        String str,
        String trueString,
        String falseString)
    {
        if (str == null) {
            if (trueString == null) {
                return true;
            } else if (falseString == null) {
                return false;
            }
        } else if (str.equals(trueString)) {
            return true;
        } else if (str.equals(falseString)) {
            return false;
        }
        // no match
        throw new IllegalArgumentException(
                        "The String did not match either specified value");
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // String <=> Character conversions
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Converts the String to a Character using the first character, returning
     * null for empty Strings.
     * </p>
     * 
     * <p>
     * For ASCII 7 bit characters, this uses a cache that will return the same
     * Character object each time.
     * </p>
     * 
     * <pre>
     *   CharUtils.toCharacterObject(null) = null
     *   CharUtils.toCharacterObject("")   = null
     *   CharUtils.toCharacterObject("A")  = 'A'
     *   CharUtils.toCharacterObject("BA") = 'B'
     * </pre>
     * 
     * @param str the character to convert
     * @return the Character value of the first letter of the String
     */
    public static Character strToCharacter(String str)
    {
        if (str == null || str.length() == 0) {
            return null;
        }
        return toObject(str.charAt(0));
    }

    /**
     * <p>
     * Converts the String to a char using the first character, throwing an
     * exception on empty Strings.
     * </p>
     * 
     * <pre>
     *   CharUtils.toChar(null) = IllegalArgumentException
     *   CharUtils.toChar("")   = IllegalArgumentException
     *   CharUtils.toChar("A")  = 'A'
     *   CharUtils.toChar("BA") = 'B'
     * </pre>
     * 
     * @param str the character to convert
     * @return the char value of the first letter of the String
     * @throws IllegalArgumentException if the String is empty
     */
    public static char strToChar(String str)
    {
        if (str == null || str.length() == 0) {
            throw new IllegalArgumentException("The String must not be empty");
        }
        return str.charAt(0);
    }

    /**
     * <p>
     * Converts the String to a char using the first character, defaulting the
     * value on empty Strings.
     * </p>
     * 
     * <pre>
     *   CharUtils.toChar(null, 'X') = 'X'
     *   CharUtils.toChar("", 'X')   = 'X'
     *   CharUtils.toChar("A", 'X')  = 'A'
     *   CharUtils.toChar("BA", 'X') = 'B'
     * </pre>
     * 
     * @param str the character to convert
     * @param defaultValue the value to use if the Character is null
     * @return the char value of the first letter of the String or the default
     *         if null
     */
    public static char strToChar(String str, char valueForNull)
    {
        if (str == null || str.length() == 0) {
            return valueForNull;
        }
        return str.charAt(0);
    }

    /**
     * <p>
     * Converts the character to the Integer it represents, throwing an
     * exception if the character is not numeric.
     * </p>
     * 
     * <p>
     * This method coverts the char '1' to the int 1 and so on.
     * </p>
     * 
     * <pre>
     *   CharUtils.toIntValue(null) = IllegalArgumentException
     *   CharUtils.toIntValue('3')  = 3
     *   CharUtils.toIntValue('A')  = IllegalArgumentException
     * </pre>
     * 
     * @param ch the character to convert, not null
     * @return the int value of the character
     * @throws IllegalArgumentException if the Character is not ASCII numeric or
     *             is null
     */
    public static int characterToInt(Character ch)
    {
        if (ch == null) {
            throw new IllegalArgumentException("The character must not be null");
        }
        return CharUtils.parseInt(ch.charValue());
    }

    /**
     * <p>
     * Converts the character to the Integer it represents, throwing an
     * exception if the character is not numeric.
     * </p>
     * 
     * <p>
     * This method coverts the char '1' to the int 1 and so on.
     * </p>
     * 
     * <pre>
     *   CharUtils.toIntValue(null, -1) = -1
     *   CharUtils.toIntValue('3', -1)  = 3
     *   CharUtils.toIntValue('A', -1)  = -1
     * </pre>
     * 
     * @param ch the character to convert
     * @param defaultValue the default value to use if the character is not
     *            numeric
     * @return the int value of the character
     */
    public static int characterToInt(Character ch, int valueForNull)
    {
        if (ch == null) {
            return valueForNull;
        }
        return CharUtils.parseInt(ch.charValue(), valueForNull);
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // String <=> int conversions
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Convert a <code>String</code> to an <code>int</code>, returning
     * <code>zero</code> if the conversion fails.
     * </p>
     * 
     * <p>
     * If the string is <code>null</code>, <code>zero</code> is returned.
     * </p>
     * 
     * <pre>
     *   NumberUtils.toInt(null) = 0
     *   NumberUtils.toInt("")   = 0
     *   NumberUtils.toInt("1")  = 1
     * </pre>
     * 
     * @param str the string to convert, may be null
     * @return the int represented by the string, or <code>zero</code> if
     *         conversion fails
     * @since 2.1
     */
    public static int strToInt(String str)
    {
        return strToInt(str, 0);
    }

    /**
     * <p>
     * Convert a <code>String</code> to an <code>int</code>, returning a default
     * value if the conversion fails.
     * </p>
     * 
     * <p>
     * If the string is <code>null</code>, the default value is returned.
     * </p>
     * 
     * <pre>
     *   NumberUtils.toInt(null, 1) = 1
     *   NumberUtils.toInt("", 1)   = 1
     *   NumberUtils.toInt("1", 0)  = 1
     * </pre>
     * 
     * @param str the string to convert, may be null
     * @param defaultValue the default value
     * @return the int represented by the string, or the default if conversion
     *         fails
     * @since 2.1
     */
    public static int strToInt(String str, int valueForNull)
    {
        if (str == null) {
            return valueForNull;
        }
        try {
            return Integer.parseInt(str);
        } catch (NumberFormatException nfe) {
            return valueForNull;
        }
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // toArray(), toMap()
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * Create a type-safe generic array.
     * 
     * <p>
     * Arrays are covariant i.e. they cannot be created from a generic type:
     * </p>
     * 
     * <pre>
     * public static &lt;T&gt; T[] createAnArray(int size)
     * {
     *     return T[size]; // compiler error here
     * }
     * 
     * public static &lt;T&gt; T[] createAnArray(int size)
     * {
     *     return (T[]) Object[size]; // ClassCastException at runtime
     * }
     * </pre>
     * 
     * <p>
     * Therefore new arrays of generic types can be created with this method,
     * e.g. an arrays of Strings:
     * </p>
     * 
     * <pre>
     * String[] array = ArrayUtils.toArray(&quot;1&quot;, &quot;2&quot;);
     * String[] emptyArray = ArrayUtils.&lt;String&gt; toArray();
     * </pre>
     * 
     * The method is typically used in scenarios, where the caller itself uses
     * generic types that have to be combined into an array.
     * 
     * Note, this method makes only sense to provide arguments of the same type
     * so that the compiler can deduce the type of the array itself. While it is
     * possible to select the type explicitly like in
     * <code>Number[] array = ArrayUtils.<Number>toArray(new
     * Integer(42), new Double(Math.PI))</code>, there is no real advantage to
     * <code>new
     * Number[] {new Integer(42), new Double(Math.PI)}</code> anymore.
     * 
     * @param <T> the array's element type
     * @param items the items of the array
     * @return the array
     * @since 3.0
     */
    public static <T> T[] toArray(final T... items)
    {
        return items;
    }

    /**
     * <p>
     * Converts the given array into a {@link java.util.Map}. Each element of
     * the array must be either a {@link java.util.Map.Entry} or an Array,
     * containing at least two elements, where the first element is used as key
     * and the second as value.
     * </p>
     * 
     * <p>
     * This method can be used to initialize:
     * </p>
     * 
     * <pre>
     * // Create a Map mapping colors.
     * Map colorMap = MapUtils.toMap(new String[][] {{
     *     {"RED", "#FF0000"},
     *     {"GREEN", "#00FF00"},
     *     {"BLUE", "#0000FF"}});
     * </pre>
     * 
     * <p>
     * This method returns <code>null</code> for a <code>null</code> input
     * array.
     * </p>
     * 
     * @param array an array whose elements are either a
     *            {@link java.util.Map.Entry} or an Array containing at least
     *            two elements, may be <code>null</code>
     * @return a <code>Map</code> that was created from the array
     * @throws IllegalArgumentException if one element of this Array is itself
     *             an Array containing less then two elements
     * @throws IllegalArgumentException if the array contains elements other
     *             than {@link java.util.Map.Entry} and an Array
     */
    public static Map<Object, Object> toMap(Object[] array)
    {
        if (array == null) {
            return null;
        }
        final Map<Object, Object> map = new HashMap<Object, Object>(
                        (int) (array.length * 1.5));
        for (int i = 0; i < array.length; i++) {
            Object object = array[i];
            if (object instanceof Map.Entry<?, ?>) {
                Map.Entry<?, ?> entry = (Map.Entry<?, ?>) object;
                map.put(entry.getKey(), entry.getValue());
            } else if (object instanceof Object[]) {
                Object[] entry = (Object[]) object;
                if (entry.length < 2) {
                    throw new IllegalArgumentException("Array element " + i
                                    + ", '" + object
                                    + "', has a length less than 2");
                }
                map.put(entry[0], entry[1]);
            } else {
                throw new IllegalArgumentException(
                                "Array element "
                                                + i
                                                + ", '"
                                                + object
                                                + "', is neither of type Map.Entry nor an Array");
            }
        }
        return map;
    }
}
