import java.io.*;
import java.util.*;

public class Simple
{
    public static void main(String[] args)
        throws Exception
    {
        String fInFileName = "/Users/lwy08/Downloads/input.txt";
        String fOutFileName = "/Users/lwy08/Downloads/output.txt";
        String fEncoding = "UTF-8";
        Scanner sc = new Scanner(new FileInputStream(fInFileName), fEncoding);
        Writer out = new OutputStreamWriter(new FileOutputStream(fOutFileName),
                        fEncoding);

        // using system's default charset encoding
        // in = new Scanner(new FileReader(new File(filename)));
        // out = new PrintWriter(new FileWriter(new File(filename)));

        // using stdin
        // in = new BufferedReader(new InputStreamReader(System.in));
        // out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(
        // System.out)));

        int cases = sc.nextInt();
        for (int cc = 1; cc <= cases; cc++) {
            // for each case - read input
            int H = sc.nextInt();
            int W = sc.nextInt();
            int M = sc.nextInt();
            System.out.println(H + " " + W + " " + M);

            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    System.out.print(sc.nextInt() + " ");
                }
                System.out.println();
            }

            // solve()

            String result = String.format("Case #%d: %d\n", cc, 0);
            System.err.print(result);
            out.write(result);
        } // end for each case

        sc.close();
        out.close();
    }
}
