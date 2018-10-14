package utilities.graph;

import java.io.*;
import java.util.*;

public class Cycle_Detect
{
    static BufferedReader br = new BufferedReader(new InputStreamReader(
                    System.in));

    static class Arista
    {
        Nodo otro;
        Nodo anterior;
        boolean borrada = false;

        public Arista(Nodo o, Nodo a)
        {
            otro = o;
            anterior = a;
        }
    }

    static class Nodo
        implements Comparable<Nodo>
    {
        String nombre;
        ArrayList<Arista> adjacentes = new ArrayList<Arista>();
        Persona persona;
        int lowlink = -1;
        int index = -1;

        public Nodo(String n, Persona p)
        {
            nombre = n;
            persona = p;
        }

        @Override
        public int compareTo(final Nodo argNode)
        {
            return argNode == this ? 0 : -1;
        }

        @Override
        public boolean equals(Object obj)
        {
            return nombre.equals(((Nodo) obj).nombre);
        }
    }

    static class Persona
    {
        TreeMap<String, Nodo> nodos = new TreeMap<String, Nodo>();
        ArrayList<Arista> aristas = new ArrayList<Arista>();

        public boolean solucionarErrores()
        {
            for (Arista a : aristas) {
                a.borrada = true;
                if (verificarConsistencia()) return true;
                a.borrada = false;
            }
            return false;
        }

        public boolean verificarConsistencia()
        {
            for (Nodo n : nodos.values()) {
                n.lowlink = -1;
                n.index = -1;
            }
            index = 0;
            stack = new ArrayList<Nodo>();
            si = false;
            for (Nodo n : nodos.values()) {
                if (n.index == -1) {
                    tarjan(n);
                }
            }
            return !si;
        }

        public Nodo buscar(String string)
        {
            if (!nodos.containsKey(string))
                nodos.put(string, new Nodo(string, this));
            return nodos.get(string);
        }

        public void llenar()
            throws IOException
        {
            String[] preferencias = br.readLine().split(
                "(\\s*,\\s*) | (\\s*;\\s*)");
            for (String f : preferencias) {
                String[] preferenciasAA = f.split("\\s+");
                Nodo anterior = buscar(preferenciasAA[0]);
                for (int i = 1; i < preferenciasAA.length; i++) {
                    Nodo actual = buscar(preferenciasAA[i]);
                    Arista nueva = new Arista(actual, anterior);
                    anterior.adjacentes.add(nueva);
                    aristas.add(nueva);
                    anterior = actual;
                }
            }
        }
    }

    static int index;
    static ArrayList<Nodo> stack;
    static boolean si = false;

    public static void tarjan(Nodo v)
    {
        v.index = index;
        v.lowlink = index;
        index++;
        stack.add(0, v);
        for (Arista a : v.adjacentes) {
            if (a.borrada) continue;
            Nodo n = a.otro;
            if (n.index == -1) {
                tarjan(n);
                v.lowlink = Math.min(v.lowlink, n.lowlink);
            } else if (stack.contains(n))
                v.lowlink = Math.min(v.lowlink, n.index);
        }
        if (v.lowlink == v.index) {
            Nodo n;
            int cuenta = 0;
            do {
                n = stack.remove(0);
                cuenta++;
            } while (n != v);
            si = si || cuenta != 1;
        }
    }

    public static void main(String[] args)
        throws IOException
    {
        while (true) {
            String[] nombres = br.readLine().split(" ");
            if (nombres[0].equals("*") && nombres[1].equals("*")) return;
            Persona a = new Persona();
            a.llenar();
            a.llenar();
            if (a.verificarConsistencia())
                System.out.println("F");
            else if (a.solucionarErrores())
                System.out.println("P");
            else
                System.out.println("N");
        }
    }
}
