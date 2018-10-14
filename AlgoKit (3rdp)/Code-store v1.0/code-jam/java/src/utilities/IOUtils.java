package utilities;

import static utilities.Constants.*;

import java.io.*;
import java.math.*;
import java.util.*;

/**
 * Custom I/O class for GCJ
 */
public class IOUtils
{
    // ************************* INPUT DECLARATION ****************************
    /**
     * initialises input & output streams to problemName.in/out
     * 
     * @throws IOException
     */
    public static void init(String problemName)
        throws IOException
    {
        setInput(problemName/* + ".in" */);
        setOutput(problemName + ".out");
    }

    /**
     * sets input stream to filename by default
     * 
     * @throws IOException
     */
    public static void setInput(String filename)
        throws IOException
    {
        input = new File(filename);
        inputReader = new FileReader(input);
        in = new Scanner(inputReader);
    }

    /**
     * sets output stream to filename by default
     * 
     * @throws IOException
     */
    public static void setOutput(String filename)
        throws IOException
    {
        output = new File(filename);
        outputWriter = new FileWriter(output);
        out = new PrintWriter(outputWriter);
    }

    /**
     * clean up operations: close IO streams/readers/writers
     * 
     * @throws IOException
     */
    public static void close()
        throws IOException
    {
        if (in != null) {
            in.close();
            in = null;
        }
        if (inputReader != null) {
            inputReader.close();
            inputReader = null;
        }
        if (out != null) {
            out.close();
            out = null;
        }
        if (outputWriter != null) {
            outputWriter.close();
            outputWriter = null;
        }
    }

    // ************************** INPUT READING *******************************
    /**
     * Helper method for {@link IOUtils#TOKEN()}
     */
    public static String LINE()
    {
        return in.nextLine();
    }

    public static String TOKEN()
    {
        while (strTokenizer == null || !strTokenizer.hasMoreTokens()) {
            strTokenizer = new StringTokenizer(LINE());
        }
        return strTokenizer.nextToken();
    }

    public static char CHAR()
    {
        return TOKEN().charAt(0);
    }

    /**
     * reads in the next integer, interpreted in base radix
     * 
     * @param radix
     * @return int result
     */
    public static int INT(int radix)
    {
        return in.nextInt(radix);
    }

    public static int INT()
    {
        return in.nextInt();
    }

    public static long LONG(int radix)
    {
        return in.nextLong(radix);
    }

    public static long LONG()
    {
        return in.nextLong();
    }

    public static double DOUBLE()
    {
        return in.nextDouble();
    }

    public static BigInteger BIGINT(int radix)
    {
        return in.nextBigInteger(radix);
    }

    public static BigInteger BIGINT()
    {
        return in.nextBigInteger();
    }

    public static BigDecimal BIGDECIMAL()
    {
        return in.nextBigDecimal();
    }

    // **************************** PRINT METHODS *****************************
    // ////////////////////////////////////////////////////////////////////////
    // print()
    // ////////////////////////////////////////////////////////////////////////
    public static void print(boolean c)
        throws IOException
    {
        out.write(Boolean.toString(c));
        System.out.print(c);
    }

    public static void print(byte c)
        throws IOException
    {
        out.write(Byte.toString(c));
        System.out.print(c);
    }

    public static void print(char c)
        throws IOException
    {
        out.write(Character.toString(c));
        System.out.print(c);
    }

    public static void print(double c)
        throws IOException
    {
        out.write(Double.toString(c));
        System.out.print(c);
    }

    public static void print(int c)
        throws IOException
    {
        out.write(Integer.toString(c));
        System.out.print(c);
    }

    public static void print(long c)
        throws IOException
    {
        out.write(Long.toString(c));
        System.out.print(c);
    }

    public static void print(String line)
        throws IOException
    {
        out.write(line);
        System.out.print(line);
    }

    public static <T> void print(T obj)
        throws IOException
    {
        out.write(obj.toString());
        System.out.print(obj.toString());
    }

    // ////////////////////////////////////////////////////////////////////////
    // println()
    // ////////////////////////////////////////////////////////////////////////
    public static void println()
        throws IOException
    {
        out.write("\n");
        System.out.println();
    }

    public static void println(boolean c)
        throws IOException
    {
        out.write(Boolean.toString(c) + "\n");
        System.out.println(c);
    }

    public static void println(byte c)
        throws IOException
    {
        out.write(Byte.toString(c) + "\n");
        System.out.println(c);
    }

    public static void println(char c)
        throws IOException
    {
        out.write(Character.toString(c) + "\n");
        System.out.println(c);
    }

    public static void println(double c)
        throws IOException
    {
        out.write(Double.toString(c) + "\n");
        System.out.println(c);
    }

    public static void println(int c)
        throws IOException
    {
        out.write(Integer.toString(c) + "\n");
        System.out.println(c);
    }

    public static void println(long number)
        throws IOException
    {
        out.write(Long.toString(number) + "\n");
        System.out.println(number);
    }

    public static void println(String line)
        throws IOException
    {
        out.write(line + "\n");
        System.out.println(line);
    }

    public static void println(int case_no, String line)
        throws IOException
    {
        String output_line = String.format(OUTPUT_FORMAT, case_no, line);
        System.out.println(output_line);
        out.println(output_line);
    }

    public static void println(int[] array)
        throws IOException
    {
        out.write(Debug.deepToString(array) + "\n");
        System.out.println(Debug.deepToString(array));
    }

    public static <T> void println(T obj)
        throws IOException
    {
        out.write(obj.toString() + "\n");
        System.out.println(obj.toString());
    }
}
