package utilities.math;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;

public class MatrixGaussianElim
{
    // Tomado de Princeton
    static class Rational
        implements Comparable<Rational>
    {
        static Rational zero = new Rational(0, 1);

        private int num; // the numerator
        private int den; // the denominator

        // create and initialize a new Rational object
        public Rational(int numerator, int denominator)
        {

            // deal with x/0
            // if (denominator == 0) {
            // throw new RuntimeException("Denominator is zero");
            // }

            // reduce fraction
            int g = gcd(numerator, denominator);
            num = numerator / g;
            den = denominator / g;

            // only needed for negative numbers
            if (den < 0) {
                den = -den;
                num = -num;
            }
        }

        // return the numerator and denominator of (this)
        public int numerator()
        {
            return num;
        }

        public int denominator()
        {
            return den;
        }

        // return double precision representation of (this)
        public double toDouble()
        {
            return (double) num / den;
        }

        // return string representation of (this)
        @Override
        public String toString()
        {
            if (den == 1)
                return num + "";
            else
                return num + "/" + den;
        }

        // return { -1, 0, +1 } if a < b, a = b, or a > b
        @Override
        public int compareTo(Rational b)
        {
            Rational a = this;
            int lhs = a.num * b.den;
            int rhs = a.den * b.num;
            if (lhs < rhs) return -1;
            if (lhs > rhs) return +1;
            return 0;
        }

        // is this Rational object equal to y?
        @Override
        public boolean equals(Object y)
        {
            if (y == null) return false;
            if (y.getClass() != this.getClass()) return false;
            Rational b = (Rational) y;
            return compareTo(b) == 0;
        }

        // hashCode consistent with equals() and compareTo()
        @Override
        public int hashCode()
        {
            return this.toString().hashCode();
        }

        // create and return a new rational (r.num + s.num) / (r.den + s.den)
        public static Rational mediant(Rational r, Rational s)
        {
            return new Rational(r.num + s.num, r.den + s.den);
        }

        // return gcd(|m|, |n|)
        private static int gcd(int m, int n)
        {
            if (m < 0) m = -m;
            if (n < 0) n = -n;
            if (0 == n)
                return m;
            else
                return gcd(n, m % n);
        }

        // return lcm(|m|, |n|)
        public static int lcm(int m, int n)
        {
            if (m < 0) m = -m;
            if (n < 0) n = -n;
            return m * (n / gcd(m, n)); // parentheses important to avoid
                                        // overflow
        }

        // return a * b, staving off overflow as much as possible by
        // cross-cancellation
        public Rational times(Rational b)
        {
            Rational a = this;

            // reduce p1/q2 and p2/q1, then multiply, where a = p1/q1 and b =
            // p2/q2
            Rational c = new Rational(a.num, b.den);
            Rational d = new Rational(b.num, a.den);
            return new Rational(c.num * d.num, c.den * d.den);
        }

        // return a + b, staving off overflow
        public Rational plus(Rational b)
        {
            Rational a = this;

            // special cases
            if (a.compareTo(zero) == 0) return b;
            if (b.compareTo(zero) == 0) return a;

            // Find gcd of numerators and denominators
            int f = gcd(a.num, b.num);
            int g = gcd(a.den, b.den);

            // add cross-product terms for numerator
            Rational s = new Rational((a.num / f) * (b.den / g) + (b.num / f)
                            * (a.den / g), lcm(a.den, b.den));

            // multiply back in
            s.num *= f;
            return s;
        }

        // return -a
        public Rational negate()
        {
            return new Rational(-num, den);
        }

        // return a - b
        public Rational minus(Rational b)
        {
            Rational a = this;
            return a.plus(b.negate());
        }

        public Rational reciprocal()
        {
            return new Rational(den, num);
        }

        // return a / b
        public Rational divides(Rational b)
        {
            Rational a = this;
            return a.times(b.reciprocal());
        }

        public Rational abs()
        {
            if (num < 0)
                return negate();
            else
                return this;
        }
    }

    static class Elemento
    {
        static HashMap<String, Elemento> elementos = new HashMap<String, Elemento>();
        static int actual;
        int id;
        String c;

        public Elemento(String e, int i)
        {
            c = e;
            id = i;
        }

        static Elemento darElemento(String e)
        {
            Elemento posible = elementos.get(e);
            if (posible == null) {
                posible = new Elemento(e, actual++);
                elementos.put(e, posible);
            }
            return posible;
        }
    }

    static class Grupo
    {
        Elemento e;
        int c;

        Grupo(Elemento ee, int cc)
        {
            e = ee;
            c = cc;
        }

        public static Grupo leerGrupo(boolean invertir)
        {
            String s = entrada.poll() + "";
            if (entrada.peek() >= 'a' && entrada.peek() <= 'z')
                s += entrada.poll();
            Elemento e = Elemento.darElemento(s);
            int c = leerNumero();
            if (invertir) c = -c;
            return new Grupo(e, c);
        }
    }

    static class Molecula
    {
        LinkedList<Grupo> g = new LinkedList<Grupo>();
    }

    static LinkedList<Character> entrada = new LinkedList<Character>();

    private static int leerNumero()
    {
        if (entrada.peek() > '9' || entrada.peek() < '0') return 1;
        int a = entrada.poll() - '0';
        if (entrada.peek() <= '9' && entrada.peek() >= '0') {
            a *= 10;
            a += entrada.poll() - '0';
        }
        return a;
    }

    static LinkedList<Molecula> leerMoleculas(char hasta, boolean invertir)
    {
        LinkedList<Molecula> acumuladas = new LinkedList<Molecula>();
        while (true) {
            char actual = entrada.peek();
            if (actual == hasta)
                return acumuladas;
            else if (actual == '+')
                entrada.poll();
            else if (actual == '-') {
                invertir = true;
                entrada.poll();
                entrada.poll();
            } else {
                Molecula m = new Molecula();
                while ((entrada.peek() >= 'A' && entrada.peek() <= 'Z')
                                || entrada.peek() == '(') {
                    if (entrada.peek() == '(') {
                        entrada.poll();
                        Molecula m1 = leerMoleculas(')', invertir).get(0);
                        entrada.poll();
                        int n = leerNumero();
                        for (Grupo g : m1.g)
                            g.c *= n;
                        m.g.addAll(m1.g);
                    } else {
                        Grupo g = Grupo.leerGrupo(invertir);
                        m.g.add(g);
                    }
                }
                acumuladas.add(m);
            }
        }
    }

    static class Matrix
    {
        Rational[][] data;
        int rows, cols;

        Matrix(int rows, int cols)
        {
            this.rows = rows;
            this.cols = cols;
            data = new Rational[rows][cols];
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    data[i][j] = Rational.zero;
        }

        void clonar(Matrix a)
        {
            Matrix nueva = new Matrix(rows, cols);
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    nueva.data[i][j] = data[i][j];
        }

        void swapRow(int row1, int row2)
        {
            Rational[] tmp = data[row2];
            data[row2] = data[row1];
            data[row1] = tmp;
        }

        void multRow(int row, Rational coeff)
        {
            for (int j = 0; j < cols; j++)
                data[row][j] = data[row][j].times(coeff);
        }

        void addRows(int destRow, int srcRow, Rational factor)
        {
            for (int j = 0; j < cols; j++)
                data[destRow][j] = data[destRow][j].plus(data[srcRow][j]
                                .times(factor));
        }

        void printMat()
        {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++)
                    System.out.print(data[i][j] + " ");
                System.out.println();
            }
        }
    };

    static void gaussianElim(Matrix m)
    {
        int rows = m.rows;
        for (int i = 0; i < rows; i++) {
            int maxrow = i;
            Rational maxval = m.data[i][i];
            for (int k = i + 1; k < rows; k++) {
                if (maxval.abs().compareTo(m.data[k][i].abs()) < 0) {
                    maxval = m.data[k][i];
                    maxrow = k;
                }
            }
            if (maxval.compareTo(Rational.zero) == 0) return;
            m.swapRow(maxrow, i);
            m.multRow(i, maxval.reciprocal());
            for (int k = 0; k < rows; k++)
                if (k != i) m.addRows(k, i, m.data[k][i].negate());
        }
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        while (true) {
            String s = sc.nextLine();
            if (s.equals(".")) return;
            entrada.clear();
            for (char c : s.toCharArray())
                entrada.add(c);
            Elemento.actual = 0;
            Elemento.elementos.clear();
            LinkedList<Molecula> moleculas = leerMoleculas('.', false);
            Matrix matriz = new Matrix(Elemento.actual, moleculas.size());
            int i = 0;
            for (Molecula m : moleculas) {
                for (Grupo g : m.g)
                    matriz.data[g.e.id][i] = matriz.data[g.e.id][i]
                                    .plus(new Rational(g.c, 1));
                i++;
            }
            gaussianElim(matriz);
            int lcm = matriz.data[Elemento.actual - 1][0].den;
            for (i = 0; i < Elemento.actual; i++)
                lcm = Rational.lcm(matriz.data[i][moleculas.size() - 1].den,
                    lcm);
            boolean empezo = false;
            for (i = 0; i < Elemento.actual; i++) {
                if (matriz.data[i][moleculas.size() - 1].num == 0) break;
                if (empezo)
                    System.out.print(" ");
                else
                    empezo = true;
                System.out.print(-matriz.data[i][moleculas.size() - 1].num
                                * (lcm / matriz.data[i][moleculas.size() - 1].den));
            }
            if (empezo)
                System.out.print(" ");
            else
                empezo = true;
            System.out.println(lcm);
        }
    }
}
