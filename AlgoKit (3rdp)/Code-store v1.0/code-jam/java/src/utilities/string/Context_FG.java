package utilities.string;

import java.io.*;

public class Context_FG
{
    /*
     * Gramatica:
     * 
     * S -> SS
     * S -> LSL
     * S -> LSLSL
     * L -> {A, B, ..., Z} terminales
     */

    static String actual;
    static Boolean[][] dp = new Boolean[151][151];

    static boolean tieneSolucion(int inicio, int fin)
    {
        if (inicio == fin) return true;
        if (inicio + 1 == fin) return false;
        if (dp[inicio][fin] != null) return dp[inicio][fin];
        for (int i = inicio + 1; i < fin; i++)
            if (tieneSolucion(inicio, i) && tieneSolucion(i, fin))
                return dp[inicio][fin] = true;
        char clave = actual.charAt(inicio);
        if (clave != actual.charAt(fin - 1)) return dp[inicio][fin] = false;
        if (tieneSolucion(inicio + 1, fin - 1)) return dp[inicio][fin] = true;
        for (int i = inicio + 1; i < fin; i++)
            if (actual.charAt(i) == clave && tieneSolucion(inicio + 1, i)
                            && tieneSolucion(i + 1, fin - 1))
                return dp[inicio][fin] = true;
        return dp[inicio][fin] = false;
    }

    public static void main(String[] args)
        throws IOException
    {
        System.setIn(new FileInputStream("D.in"));
        System.setOut(new PrintStream("salida.out"));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            actual = br.readLine();
            if (actual == null) return;
            int tam = actual.length();
            for (int i = 0; i <= tam; i++)
                for (int j = 0; j <= tam; j++) {
                    dp[i][j] = null;
                }
            System.out.println(tieneSolucion(0, tam) ? "solvable"
                            : "unsolvable");
        }
    }

}
