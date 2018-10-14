package utilities.geom;

import java.awt.geom.*;
import java.io.*;
import java.math.*;
import java.util.*;

public class SegmentIntersect
{
    static class Scanner
    {
        BufferedReader br;
        StringTokenizer st;

        public Scanner()
        {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        public String next()
        {

            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (Exception e) {
                    throw new RuntimeException();
                }
            }
            return st.nextToken();
        }

        public int nextInt()
        {
            return Integer.parseInt(next());
        }

        public double nextDouble()
        {
            return Double.parseDouble(next());
        }

        public String nextLine()
        {
            st = null;
            try {
                return br.readLine();
            } catch (Exception e) {
                throw new RuntimeException();
            }
        }
    }

    public static Point2D.Double intersection(
        double x1,
        double y1,
        double x2,
        double y2,
        double x3,
        double y3,
        double x4,
        double y4)
    {
        double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        if (d == 0) return null;
        double xi = ((x3 - x4) * (x1 * y2 - y1 * x2) - (x1 - x2)
                        * (x3 * y4 - y3 * x4))
                        / d;
        double yi = ((y3 - y4) * (x1 * y2 - y1 * x2) - (y1 - y2)
                        * (x3 * y4 - y3 * x4))
                        / d;
        if (x3 == x4) {
            if (yi < Math.min(y1, y2) || yi > Math.max(y1, y2)) return null;
        }
        Point2D.Double p = new Point2D.Double(xi, yi);
        if (xi < Math.min(x1, x2) || xi > Math.max(x1, x2)) return null;
        if (xi < Math.min(x3, x4) || xi > Math.max(x3, x4)) return null;
        return p;
    }

    static Point2D lineSegmentIntersection(
        double Ax,
        double Ay,
        double Bx,
        double By,
        double Cx,
        double Cy,
        double Dx,
        double Dy)
    {

        double distAB, theCos, theSin, newX, ABpos;

        // Fail if either line segment is zero-length.
        if (Ax == Bx && Ay == By || Cx == Dx && Cy == Dy) return null;

        // Fail if the segments share an end-point.
        if (Ax == Cx && Ay == Cy || Bx == Cx && By == Cy || Ax == Dx
                        && Ay == Dy || Bx == Dx && By == Dy) {
            return null;
        }

        // (1) Translate the system so that point A is on the origin.
        Bx -= Ax;
        By -= Ay;
        Cx -= Ax;
        Cy -= Ay;
        Dx -= Ax;
        Dy -= Ay;

        // Discover the length of segment A-B.
        distAB = Math.sqrt(Bx * Bx + By * By);

        // (2) Rotate the system so that point B is on the positive X axis.
        theCos = Bx / distAB;
        theSin = By / distAB;
        newX = Cx * theCos + Cy * theSin;
        Cy = Cy * theCos - Cx * theSin;
        Cx = newX;
        newX = Dx * theCos + Dy * theSin;
        Dy = Dy * theCos - Dx * theSin;
        Dx = newX;

        // Fail if segment C-D doesn't cross line A-B.
        if (Cy < -EPSILON && Dy < -EPSILON || Cy >= -EPSILON && Dy >= -EPSILON)
            return null;

        // (3) Discover the position of the intersection point along line A-B.
        ABpos = Dx + (Cx - Dx) * Dy / (Dy - Cy);

        // Fail if segment C-D crosses line A-B outside of segment A-B.
        if (ABpos < -EPSILON || ABpos > distAB - EPSILON) return null;

        // (4) Apply the discovered position to line A-B in the original
        // coordinate system.
        double X = Ax + ABpos * theCos;
        double Y = Ay + ABpos * theSin;

        return new Point2D.Double(X, Y);
    }

    static Point2D interseccionAux(
        double x1,
        double y1,
        double x2,
        double y2,
        double x3,
        double y3,
        double x4,
        double y4)
    {
        double px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2)
                        * (x3 * y4 - y3 * x4))
                        / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
        double py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2)
                        * (x3 * y4 - y3 * x4))
                        / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
        if (Math.abs(((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))) < EPSILON)
            return null;
        if (Math.abs(((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))) < EPSILON)
            return null;
        return new Point2D.Double(px, py);
    }

    static final double EPSILON = 0.00001;

    static Point2D PARALELAS = new Point2D.Double();

    static Point2D interseccionLineas(
        double x1,
        double y1,
        double x2,
        double y2,
        double x3,
        double y3,
        double x4,
        double y4)
    {
        if (Math.abs(y2 - y1) < EPSILON) {
            if (Math.abs(y4 - y3) < EPSILON) {
                if (Math.abs(y1 - y3) < EPSILON)
                    return PARALELAS;
                else
                    return null;
            } else
                return interseccionAux(x1, y1, x2, y2, x3, y3, x4, y4);
        } else {
            double ma = (x2 - x1) / (y2 - y1);
            double mb = (x4 - x3) / (y4 - y3);
            if (Math.abs(ma - mb) < EPSILON) {
                if (Math.abs((-y1 * ma + x1) - (-y3 * mb + x3)) < EPSILON)
                    return PARALELAS;
                else
                    return null;
            } else
                return interseccionAux(x1, y1, x2, y2, x3, y3, x4, y4);
        }
    }

    static Point2D interseccionLineas(Line2D a, Line2D b)
    {
        return lineSegmentIntersection(a.getX1(), a.getY1(), a.getX2(),
            a.getY2(), b.getX1(), b.getY1(), b.getX2(), b.getY2());
    }

    static class PermutationGenerator
    {

        private final int[] a;
        private BigInteger numLeft;
        private final BigInteger total;

        // -----------------------------------------------------------
        // Constructor. WARNING: Don't make n too large.
        // Recall that the number of permutations is n!
        // which can be very large, even when n is as small as 20 --
        // 20! = 2,432,902,008,176,640,000 and
        // 21! is too big to fit into a Java long, which is
        // why we use BigInteger instead.
        // ----------------------------------------------------------

        public PermutationGenerator(int n)
        {
            if (n < 1) {
                throw new IllegalArgumentException("Min 1");
            }
            a = new int[n];
            total = getFactorial(n);
            reset();
        }

        // ------
        // Reset
        // ------

        public void reset()
        {
            for (int i = 0; i < a.length; i++) {
                a[i] = i;
            }
            numLeft = new BigInteger(total.toString());
        }

        // ------------------------------------------------
        // Return number of permutations not yet generated
        // ------------------------------------------------

        public BigInteger getNumLeft()
        {
            return numLeft;
        }

        // ------------------------------------
        // Return total number of permutations
        // ------------------------------------

        public BigInteger getTotal()
        {
            return total;
        }

        // -----------------------------
        // Are there more permutations?
        // -----------------------------

        public boolean hasMore()
        {
            return numLeft.compareTo(BigInteger.ZERO) == 1;
        }

        // ------------------
        // Compute factorial
        // ------------------

        private static BigInteger getFactorial(int n)
        {
            BigInteger fact = BigInteger.ONE;
            for (int i = n; i > 1; i--) {
                fact = fact.multiply(new BigInteger(Integer.toString(i)));
            }
            return fact;
        }

        // --------------------------------------------------------
        // Generate next permutation (algorithm from Rosen p. 284)
        // --------------------------------------------------------

        public int[] getNext()
        {

            if (numLeft.equals(total)) {
                numLeft = numLeft.subtract(BigInteger.ONE);
                return a;
            }

            int temp;

            // Find largest index j with a[j] < a[j+1]

            int j = a.length - 2;
            while (a[j] > a[j + 1]) {
                j--;
            }

            // Find index k such that a[k] is smallest integer
            // greater than a[j] to the right of a[j]

            int k = a.length - 1;
            while (a[j] > a[k]) {
                k--;
            }

            // Interchange a[j] and a[k]

            temp = a[k];
            a[k] = a[j];
            a[j] = temp;

            // Put tail end of permutation after jth position in increasing
            // order

            int r = a.length - 1;
            int s = j + 1;

            while (r > s) {
                temp = a[s];
                a[s] = a[r];
                a[r] = temp;
                r--;
                s++;
            }

            numLeft = numLeft.subtract(BigInteger.ONE);
            return a;

        }

    }

    static class Punto
    {
        Point2D p;

        public Punto(Point2D pp)
        {
            p = pp;
        }

        @Override
        public boolean equals(Object obj)
        {
            Punto otro = (Punto) obj;
            if (Math.abs(p.getX() - otro.p.getX()) > EPSILON) return false;
            if (Math.abs(p.getY() - otro.p.getY()) > EPSILON) return false;
            return true;
        }
    }

    static int n, c;
    static int[][] costo = new int[20][20];
    static Punto[] ciudades = new Punto[20];

    public static void main(String[] args)
    {
        Scanner sc = new Scanner();
        int caso = 1;
        while (true) {
            n = sc.nextInt();
            c = sc.nextInt();
            if (n == 0 && c == 0) return;
            for (int i = 0; i < n; i++) {
                int x = sc.nextInt();
                int y = sc.nextInt();
                ciudades[i] = new Punto(new Point2D.Double(x, y));
            }
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    costo[i][j] = sc.nextInt();
            PermutationGenerator pg = new PermutationGenerator(n);
            int mejor = Integer.MAX_VALUE;
            while (pg.hasMore())
                mejor = Math.min(mejor, intentar(pg.getNext()));
            System.out.println(caso++ + ". " + mejor);
        }
    }

    static class Interseccion
    {
        Punto p;
        ArrayList<Line2D> lineas = new ArrayList<Line2D>();

        public Interseccion(Punto pp, Line2D primera, Line2D segunda)
        {
            p = pp;
            lineas.add(primera);
            lineas.add(segunda);
        }
    }

    private static int intentar(int[] next)
    {
        ArrayList<Line2D> lineas = new ArrayList<Line2D>();
        LinkedList<Interseccion> intersecciones = new LinkedList<Interseccion>();
        int costoT = 0;
        for (int i = 1; i <= next.length; i++) {
            costoT += costo[next[i - 1]][next[i % next.length]];
            Line2D.Double nueva = new Line2D.Double(ciudades[next[i - 1]].p,
                            ciudades[next[i % next.length]].p);
            for (Line2D l : lineas) {
                if (nueva.getP1().equals(l.getP1())
                                || nueva.getP1().equals(l.getP2())
                                || nueva.getP2().equals(l.getP1())
                                || nueva.getP2().equals(l.getP2())) continue;
                if (!l.intersectsLine(nueva)) continue;
                Point2D inter = interseccionLineas(l, nueva);
                if (inter == null) continue;
                Punto punto = new Punto(inter);
                boolean esta = false;
                for (Interseccion in : intersecciones) {
                    if (in.p.equals(punto)) {
                        if (!in.lineas.contains(nueva)) in.lineas.add(nueva);
                        esta = true;
                    }
                }
                if (!esta)
                    intersecciones.add(new Interseccion(punto, nueva, l));
            }
            lineas.add(nueva);
        }
        for (Interseccion in : intersecciones)
            costoT += (in.lineas.size() * (in.lineas.size() - 1) * c) / 2;
        return costoT;
    }
}
