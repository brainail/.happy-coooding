package utilities.graph;

import java.util.*;

public class Prim
{
    static class PriorityQueue
    {
        private int currentSize;
        private PriorityQueueItem[] array;

        public PriorityQueue(int capacidad)
        {
            currentSize = 0;
            array = new PriorityQueueItem[capacidad + 1];
        }

        public int insert(PriorityQueueItem x)
        {
            if (currentSize + 1 == array.length) doubleArray();
            int hole = ++currentSize;
            array[0] = x;
            array[0].setPosition(0);
            for (; x.compareTo(array[hole / 2]) < 0; hole /= 2) {
                array[hole] = array[hole / 2];
                array[hole].setPosition(hole);
            }
            array[hole] = x;
            array[hole].setPosition(hole);
            return hole;
        }

        public void decreaseKey(PriorityQueueItem newVal)
        {
            int hole = newVal.position();
            array[0] = newVal;
            array[0].setPosition(0);
            for (; newVal.compareTo(array[hole / 2]) < 0; hole /= 2) {
                array[hole] = array[hole / 2];
                array[hole].setPosition(hole);
            }
            array[hole] = newVal;
            array[hole].setPosition(hole);
        }

        public PriorityQueueItem deleteMin()
        {
            PriorityQueueItem minItem = array[1];
            array[1] = array[currentSize--];
            array[1].setPosition(1);
            percolateDown(1);
            return minItem;
        }

        public boolean isEmpty()
        {
            return currentSize == 0;
        }

        private void percolateDown(int hole)
        {
            int child;
            PriorityQueueItem tmp = array[hole];
            for (; hole * 2 <= currentSize; hole = child) {
                child = hole * 2;
                if (child != currentSize
                                && array[child + 1].compareTo(array[child]) < 0)
                    child++;
                if (array[child].compareTo(tmp) < 0) {
                    array[hole] = array[child];
                    array[hole].setPosition(hole);
                } else
                    break;
            }
            array[hole] = tmp;
            array[hole].setPosition(hole);
        }

        private void doubleArray()
        {
            PriorityQueueItem[] newArray;
            newArray = new PriorityQueueItem[array.length * 2];
            for (int i = 0; i < array.length; i++)
                newArray[i] = array[i];
            array = newArray;
        }
    }

    static abstract class PriorityQueueItem
    {
        int dist = Integer.MAX_VALUE;
        private int position;

        public int position()
        {
            return position;
        }

        public void setPosition(int newPosition)
        {
            position = newPosition;
        }

        public int compareTo(PriorityQueueItem o)
        {
            return new Integer(dist).compareTo(o.dist);
        }
    }

    static int[][] pesos = new int[400][400];

    static class Ciudad
        extends PriorityQueueItem
    {
        String nombre;
        int posicion;
        Ciudad parent = null;
        boolean is_in_q = true;
        ArrayList<Ciudad> adjacentes = new ArrayList<Ciudad>();

        public Ciudad(String n, int pos)
        {
            nombre = n;
            posicion = pos;
            dist = Integer.MAX_VALUE;
        }
    }

    static class Vertice
    {
        Ciudad a, b;
        int costo;

        public Vertice(Ciudad a, Ciudad b, int costo)
        {
            super();
            this.a = a;
            this.b = b;
            this.costo = costo;
        }

    }

    public static void main(String[] args)
    {
        Hashtable<String, Ciudad> hash = new Hashtable<String, Ciudad>();
        Scanner sc = new Scanner(System.in);
        while (true) {
            int s = sc.nextInt();
            int c = sc.nextInt();
            if (s == 0 && c == 0) return;
            for (int i = 0; i < s; i++)
                for (int j = 0; j < s; j++) {
                    pesos[i][j] = Integer.MAX_VALUE;
                }
            ArrayList<Ciudad> ciudades = new ArrayList<Ciudad>(s);
            for (int i = 0; i < s; i++) {
                String actual = sc.next();
                Ciudad nueva = new Ciudad(actual, i);
                hash.put(actual, nueva);
                ciudades.add(nueva);
            }
            for (int i = 0; i < c; i++) {
                String c1 = sc.next();
                String c2 = sc.next();
                int costo = sc.nextInt();
                Ciudad ci1 = hash.get(c1);
                Ciudad ci2 = hash.get(c2);
                int pos1 = ci1.posicion;
                int pos2 = ci2.posicion;
                ci1.adjacentes.add(ci2);
                ci2.adjacentes.add(ci1);
                pesos[pos1][pos2] = costo;
                pesos[pos2][pos1] = costo;
            }
            String ini = sc.next();
            Ciudad inicial = hash.get(ini);
            inicial.dist = 0;
            PriorityQueue q = new PriorityQueue(s);
            for (Ciudad ci : ciudades)
                q.insert(ci);
            while (!q.isEmpty()) {
                Ciudad latest = (Ciudad) q.deleteMin();
                latest.is_in_q = false;
                for (Ciudad adj : latest.adjacentes) {
                    if (adj.is_in_q
                                    && pesos[latest.posicion][adj.posicion] < adj.dist) {
                        adj.parent = latest;
                        adj.dist = pesos[latest.posicion][adj.posicion];
                        q.decreaseKey(adj);
                    }
                }
            }
            int valorTotal = 0;
            boolean termino = false;
            for (Ciudad ci : ciudades) {
                if (ci.dist == Integer.MAX_VALUE) {
                    System.out.println("Impossible");
                    termino = true;
                    break;
                }
                valorTotal += ci.dist;
            }
            if (!termino) System.out.println(valorTotal);
        }
    }
}
