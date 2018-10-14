package utilities;

public class CharUtils
{
    private static final String CHAR_STRING = "\u0000\u0001\u0002\u0003\u0004\u0005\u0006\u0007"
                    + "\b\t\n\u000b\f\r\u000e\u000f"
                    + "\u0010\u0011\u0012\u0013\u0014\u0015\u0016\u0017"
                    + "\u0018\u0019\u001a\u001b\u001c\u001d\u001e\u001f"
                    + "\u0020\u0021\"\u0023\u0024\u0025\u0026\u0027"
                    + "\u0028\u0029\u002a\u002b\u002c\u002d\u002e\u002f"
                    + "\u0030\u0031\u0032\u0033\u0034\u0035\u0036\u0037"
                    + "\u0038\u0039\u003a\u003b\u003c\u003d\u003e\u003f"
                    + "\u0040\u0041\u0042\u0043\u0044\u0045\u0046\u0047"
                    + "\u0048\u0049\u004a\u004b\u004c\u004d\u004e\u004f"
                    + "\u0050\u0051\u0052\u0053\u0054\u0055\u0056\u0057"
                    + "\u0058\u0059\u005a\u005b\\\u005d\u005e\u005f"
                    + "\u0060\u0061\u0062\u0063\u0064\u0065\u0066\u0067"
                    + "\u0068\u0069\u006a\u006b\u006c\u006d\u006e\u006f"
                    + "\u0070\u0071\u0072\u0073\u0074\u0075\u0076\u0077"
                    + "\u0078\u0079\u007a\u007b\u007c\u007d\u007e\u007f";
    private static final String[] CHAR_STRING_ARRAY = new String[128];
    private static final Character[] CHAR_ARRAY = new Character[128];
    /**
     * <code>\u000a</code> linefeed LF ('\n').
     * 
     * @see <a
     *      href="http://java.sun.com/docs/books/jls/third_edition/html/lexical.html#101089">JLF:
     *      Escape Sequences for Character and String Literals</a>
     * @since 2.2
     */
    public static final char LF = '\n';
    /**
     * <code>\u000d</code> carriage return CR ('\r').
     * 
     * @see <a
     *      href="http://java.sun.com/docs/books/jls/third_edition/html/lexical.html#101089">JLF:
     *      Escape Sequences for Character and String Literals</a>
     * @since 2.2
     */
    public static final char CR = '\r';

    static {
        for (int i = 127; i >= 0; i--) {
            CHAR_STRING_ARRAY[i] = CHAR_STRING.substring(i, i + 1);
            CHAR_ARRAY[i] = new Character((char) i);
        }
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // parseInt(char)
    // ////////////////////////////////////////////////////////////////////////////////////
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
     *   CharUtils.toIntValue('3')  = 3
     *   CharUtils.toIntValue('A')  = IllegalArgumentException
     * </pre>
     * 
     * @param ch the character to convert
     * @return the int value of the character
     * @throws IllegalArgumentException if the character is not ASCII numeric
     */
    public static int parseInt(char ch)
    {
        if (isAsciiNumeric(ch) == false) {
            throw new IllegalArgumentException("The character " + ch
                            + " is not in the range '0' - '9'");
        }
        return ch - '0';
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
     *   CharUtils.toIntValue('3', -1)  = 3
     *   CharUtils.toIntValue('A', -1)  = -1
     * </pre>
     * 
     * @param ch the character to convert
     * @param defaultValue the default value to use if the character is not
     *            numeric
     * @return the int value of the character
     */
    public static int parseInt(char ch, int valueForNull)
    {
        if (isAsciiNumeric(ch) == false) {
            return valueForNull;
        }
        return ch - '0';
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // toString(char)
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Converts the character to a String that contains the one character.
     * </p>
     * 
     * <p>
     * For ASCII 7 bit characters, this uses a cache that will return the same
     * String object each time.
     * </p>
     * 
     * <pre>
     *   CharUtils.toString(' ')  = " "
     *   CharUtils.toString('A')  = "A"
     * </pre>
     * 
     * @param ch the character to convert
     * @return a String containing the one specified character
     */
    public static String toString(char ch)
    {
        if (ch < 128) {
            return CHAR_STRING_ARRAY[ch];
        }
        return new String(new char[] { ch });
    }

    /**
     * <p>
     * Converts the character to a String that contains the one character.
     * </p>
     * 
     * <p>
     * For ASCII 7 bit characters, this uses a cache that will return the same
     * String object each time.
     * </p>
     * 
     * <p>
     * If <code>null</code> is passed in, <code>null</code> will be returned.
     * </p>
     * 
     * <pre>
     *   CharUtils.toString(null) = null
     *   CharUtils.toString(' ')  = " "
     *   CharUtils.toString('A')  = "A"
     * </pre>
     * 
     * @param ch the character to convert
     * @return a String containing the one specified character
     */
    public static String toString(Character ch)
    {
        if (ch == null) {
            return null;
        }
        return toString(ch.charValue());
    }

    // ////////////////////////////////////////////////////////////////////////////////////
    // isTests()
    // ////////////////////////////////////////////////////////////////////////////////////
    /**
     * <p>
     * Checks whether the character is ASCII 7 bit.
     * </p>
     * 
     * <pre>
     *   CharUtils.isAscii('a')  = true
     *   CharUtils.isAscii('A')  = true
     *   CharUtils.isAscii('3')  = true
     *   CharUtils.isAscii('-')  = true
     *   CharUtils.isAscii('\n') = true
     *   CharUtils.isAscii('&copy;') = false
     * </pre>
     * 
     * @param ch the character to check
     * @return true if less than 128
     */
    public static boolean isAscii(char ch)
    {
        return ch < 128;
    }

    /**
     * <p>
     * Checks whether the character is ASCII 7 bit alphabetic.
     * </p>
     * 
     * <pre>
     *   CharUtils.isAsciiAlpha('a')  = true
     *   CharUtils.isAsciiAlpha('A')  = true
     *   CharUtils.isAsciiAlpha('3')  = false
     *   CharUtils.isAsciiAlpha('-')  = false
     *   CharUtils.isAsciiAlpha('\n') = false
     *   CharUtils.isAsciiAlpha('&copy;') = false
     * </pre>
     * 
     * @param ch the character to check
     * @return true if between 65 and 90 or 97 and 122 inclusive
     */
    public static boolean isAsciiAlpha(char ch)
    {
        return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
    }

    /**
     * <p>
     * Checks whether the character is ASCII 7 bit alphabetic upper case.
     * </p>
     * 
     * <pre>
     *   CharUtils.isAsciiAlphaUpper('a')  = false
     *   CharUtils.isAsciiAlphaUpper('A')  = true
     *   CharUtils.isAsciiAlphaUpper('3')  = false
     *   CharUtils.isAsciiAlphaUpper('-')  = false
     *   CharUtils.isAsciiAlphaUpper('\n') = false
     *   CharUtils.isAsciiAlphaUpper('&copy;') = false
     * </pre>
     * 
     * @param ch the character to check
     * @return true if between 65 and 90 inclusive
     */
    public static boolean isAsciiAlphaUpper(char ch)
    {
        return ch >= 'A' && ch <= 'Z';
    }

    /**
     * <p>
     * Checks whether the character is ASCII 7 bit alphabetic lower case.
     * </p>
     * 
     * <pre>
     *   CharUtils.isAsciiAlphaLower('a')  = true
     *   CharUtils.isAsciiAlphaLower('A')  = false
     *   CharUtils.isAsciiAlphaLower('3')  = false
     *   CharUtils.isAsciiAlphaLower('-')  = false
     *   CharUtils.isAsciiAlphaLower('\n') = false
     *   CharUtils.isAsciiAlphaLower('&copy;') = false
     * </pre>
     * 
     * @param ch the character to check
     * @return true if between 97 and 122 inclusive
     */
    public static boolean isAsciiAlphaLower(char ch)
    {
        return ch >= 'a' && ch <= 'z';
    }

    /**
     * <p>
     * Checks whether the character is ASCII 7 bit numeric.
     * </p>
     * 
     * <pre>
     *   CharUtils.isAsciiNumeric('a')  = false
     *   CharUtils.isAsciiNumeric('A')  = false
     *   CharUtils.isAsciiNumeric('3')  = true
     *   CharUtils.isAsciiNumeric('-')  = false
     *   CharUtils.isAsciiNumeric('\n') = false
     *   CharUtils.isAsciiNumeric('&copy;') = false
     * </pre>
     * 
     * @param ch the character to check
     * @return true if between 48 and 57 inclusive
     */
    public static boolean isAsciiNumeric(char ch)
    {
        return ch >= '0' && ch <= '9';
    }

    /**
     * <p>
     * Checks whether the character is ASCII 7 bit numeric.
     * </p>
     * 
     * <pre>
     *   CharUtils.isAsciiAlphanumeric('a')  = true
     *   CharUtils.isAsciiAlphanumeric('A')  = true
     *   CharUtils.isAsciiAlphanumeric('3')  = true
     *   CharUtils.isAsciiAlphanumeric('-')  = false
     *   CharUtils.isAsciiAlphanumeric('\n') = false
     *   CharUtils.isAsciiAlphanumeric('&copy;') = false
     * </pre>
     * 
     * @param ch the character to check
     * @return true if between 48 and 57 or 65 and 90 or 97 and 122 inclusive
     */
    public static boolean isAsciiAlphanumeric(char ch)
    {
        return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')
                        || (ch >= '0' && ch <= '9');
    }
}
