import java.io.*;
import java.math.*;
import java.lang.*;
import java.util.*;

public class Task_10_J {

    private static enum ExecuteMode {STD, FILE, IN_FILE};

    private FastScanner mScanner;
    private PrintWriter mWriter;

    public static void main(String [] args) {
        // new Task_10_J().execute(ExecuteMode.STD);
        // new Task_10_J().execute(ExecuteMode.FILE);
        new Task_10_J().execute(ExecuteMode.IN_FILE);
    }

    void solve() {
        int T = mScanner.nextInt();
        for (int t = 0; t < T; ++ t) {
            long K = mScanner.nextLong();
            mWriter.println(K);
        }
    }

    void execute(final ExecuteMode executeMode) {
        try {
            mScanner = new FastScanner(executeMode);

            if (ExecuteMode.FILE != executeMode) {
                mWriter = new PrintWriter(System.out);
            } else {
                mWriter = new PrintWriter(new File("output.txt"));
            }

            solve();
        } catch (final Exception exception) {
            exception.printStackTrace();
        } finally {
            mWriter.close();
        }
    }

    class FastScanner {

        private BufferedReader mReader;
        private StringTokenizer mTokenizer;

        public FastScanner(final ExecuteMode executeMode) throws Exception {
            if (ExecuteMode.STD == executeMode) {
                mReader = new BufferedReader(new InputStreamReader(System.in));
            } else {
                mReader = new BufferedReader(new FileReader(new File("input.txt")));
            }
        }

        public FastScanner(String s) {
            try {
                mReader = new BufferedReader(new FileReader(s));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        String nextToken() {
            while (null == mTokenizer || !mTokenizer.hasMoreElements()) {
                try {
                    mTokenizer = new StringTokenizer(mReader.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            return mTokenizer.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(nextToken());
        }

        long nextLong() {
            return Long.parseLong(nextToken());
        }

        double nextDouble() {
            return Double.parseDouble(nextToken());
        }

    }

}