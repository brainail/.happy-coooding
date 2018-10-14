package utilities.string;

import java.util.Random;
import java.math.BigInteger;

/***************************************************************
 * Compilation: javac RabinKarp.java
 * Execution: java RabinKarp pat txt
 * 
 * Reads in two strings, the pattern and the input text, and
 * searches for the pattern in the input text using the
 * Las Vegas version of the Rabin-Karp algorithm.
 * 
 * % java RabinKarp abracadabra abacadabrabracabracadabrabrabracad
 * pattern: abracadabra
 * text: abacadabrabracabracadabrabrabracad
 * match: abracadabra
 * 
 ***************************************************************/
public class RabinKarp
{
    private String pat; // the pattern // needed only for Las Vegas
    private long patHash; // pattern hash value
    private int M; // pattern length
    private long Q; // a large prime, small enough to avoid long overflow
    private int R; // radix
    private long RM; // R^(M-1) % Q

    public RabinKarp(int R, char[] pattern)
    {
        throw new RuntimeException("Operation not supported yet");
    }

    public RabinKarp(String pat)
    {
        this.pat = pat; // save pattern (needed only for Las Vegas)
        R = 256;
        M = pat.length();
        Q = longRandomPrime();

        // precompute R^(M-1) % Q for use in removing leading digit
        RM = 1;
        for (int i = 1; i <= M - 1; i++)
            RM = (R * RM) % Q;
        patHash = hash(pat, M);
    }

    // Compute hash for key[0..M-1].
    private long hash(String key, int M)
    {
        long h = 0;
        for (int j = 0; j < M; j++)
            h = (R * h + key.charAt(j)) % Q;
        return h;
    }

    // Las Vegas version: does pat[] match txt[i..i-M+1] ?
    private boolean check(String txt, int i)
    {
        for (int j = 0; j < M; j++)
            if (pat.charAt(j) != txt.charAt(i + j)) return false;
        return true;
    }

    // check for exact match
    public int search(String txt)
    {
        int N = txt.length();
        if (N < M) return N;
        long txtHash = hash(txt, M);

        // check for match at offset 0
        if ((patHash == txtHash) && check(txt, 0)) return 0;

        // check for hash match; if hash match, check for exact match
        for (int i = M; i < N; i++) {
            // Remove leading digit, add trailing digit, check for match.
            txtHash = (txtHash + Q - RM * txt.charAt(i - M) % Q) % Q;
            txtHash = (txtHash * R + txt.charAt(i)) % Q;

            // match
            int offset = i - M + 1;
            if ((patHash == txtHash) && check(txt, offset)) return offset;
        }

        // no match
        return N;
    }

    // a random 31-bit prime
    private static long longRandomPrime()
    {
        BigInteger prime = new BigInteger(31, new Random());
        return prime.longValue();
    }

    // test client
    public static void main(String[] args)
    {
        String pat = "abracadabra";// args[0];
        String txt = "abacadabrabracabracadabrabrabracad";// args[1];
        // char[] pattern = pat.toCharArray();
        // char[] text = txt.toCharArray();

        RabinKarp searcher = new RabinKarp(pat);
        int offset = searcher.search(txt);

        // print results
        System.out.println("text:     " + txt);

        // from brute force search method 1
        System.out.print("pattern: ");
        for (int i = 0; i < offset; i++)
            System.out.print(" ");
        System.out.println("^" + pat);
        System.out.println("offset = " + offset);
    }
}
