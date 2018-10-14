package utilities.games;

import java.io.*;
import java.util.*;

public class Grundy
{
    static Integer[] grundy = new Integer[10010];
    static boolean[] mex = new boolean[10010];

    static int grundy(int n)
    {
        if (n <= 0) return 0;
        if (grundy[n] != null) return grundy[n];
        for (int i = 0; i <= n; i++)
            mex[i] = false;
        mex[grundy(n - 3)] = true;
        for (int i = 1; i < (n - 1) / 2 + 1; i++)
            mex[grundy(i - 2) ^ grundy(n - i - 3)] = true;
        int menor = -1;
        while (mex[++menor])
            ;
        grundy[n] = menor;
        return grundy[n];
    }

    public static boolean solucionar(char[] tablero)
    {
        ArrayList<Integer> grundys = new ArrayList<Integer>();
        int ultimaX = tablero[0] == 'X' ? 0 : -1;
        for (int i = 1; i < tablero.length; i++) {
            if (tablero[i] == 'X') {
                if (ultimaX == -1) {
                    ultimaX = i;
                    grundys.add(grundy(i - 2));
                } else {
                    if (ultimaX == i - 1 || ultimaX == i - 2) return true;
                    int distancia = i - ultimaX - 1;
                    grundys.add(grundy(distancia - 4));
                    ultimaX = i;
                }
            }
        }
        if (ultimaX != tablero.length - 1) if (ultimaX == -1)
            grundys.add(grundy(tablero.length));
        else
            grundys.add(grundy(tablero.length - 3 - ultimaX));
        int acumulado = grundys.get(0);
        for (int i = 1; i < grundys.size(); i++)
            acumulado = acumulado ^ grundys.get(i);
        return acumulado != 0;
    }

    public static void main(String[] args)
        throws NumberFormatException,
            IOException
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            int n = Integer.parseInt(br.readLine());
            if (n == 0) return;
            System.out.println(solucionar(br.readLine().toCharArray()) ? "S"
                            : "N");
        }
    }
}
