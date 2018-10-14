package utilities;

import java.io.*;
import java.text.*;
import java.util.*;

public final class Constants
{
    public static int cc, cases = 0;
    public static final String OUTPUT_FORMAT = "Case #%d: %s";
    public static final DecimalFormat DECIMAL_FORMAT = new DecimalFormat(
                    "#0.0000000", new DecimalFormatSymbols(Locale.US));
    public static final double DBL_EPSILON = 1E-6; // default tolerance
    public static final BufferedReader stdin = new BufferedReader(
                    new InputStreamReader(System.in));
    public static final PrintWriter stdout = new PrintWriter(
                    new OutputStreamWriter(System.out));
    public static File input, output;
    public static FileReader inputReader;
    public static Scanner in;
    public static FileWriter outputWriter;
    public static PrintWriter out;
    public static StringTokenizer strTokenizer;
    public static Random rng = new Random(System.currentTimeMillis());
}
