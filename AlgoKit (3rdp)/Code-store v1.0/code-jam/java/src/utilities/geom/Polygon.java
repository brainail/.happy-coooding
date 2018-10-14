package utilities.geom;

import java.awt.geom.*;
import java.io.*;
import java.util.*;

public class Polygon
{
    static class IPolygon
    {
        ArrayList<Line2D> lines;
        Point2D anterior = null;

        public IPolygon(int minSize)
        {
            lines = new ArrayList<Line2D>(minSize);
        }

        public void add(Point2D nuevo)
        {
            if (anterior != null) {
                lines.add(new Line2D.Double(anterior, nuevo));
            }
            anterior = nuevo;
        }

        public void close()
        {
            lines.add(new Line2D.Double(anterior, lines.get(0).getP1()));
        }

        public static Point2D subtract(Point2D a, Point2D b)
        {
            return new Point2D.Double(a.getX() - b.getX(), a.getY() - b.getY());
        }

        static double abs(Point2D a)
        {
            return Math.sqrt(a.getX() * a.getX() + a.getY() * a.getY());
        }

        static double cross(Point2D a, Point2D b)
        {
            return (a.getX() * b.getY()) - (a.getY() * b.getX());
        }

        static boolean is_point_online(Point2D a, Point2D b, Point2D c)
        {
            return abs(subtract(a, c)) + abs(subtract(b, c)) <= abs(subtract(a,
                b));
        }

        // Ya esta implementado en ((Line2D) lineA).intersectsLine(lineB)
        public static boolean lines_intersect(Line2D a, Line2D b)
        {
            return cross(subtract(a.getP2(), a.getP1()),
                subtract(b.getP1(), a.getP1()))
                            * cross(subtract(a.getP2(), a.getP1()),
                                subtract(b.getP2(), a.getP1())) < 0
                            && cross(subtract(b.getP2(), b.getP1()),
                                subtract(a.getP1(), b.getP1()))
                                            * cross(
                                                subtract(b.getP2(), b.getP1()),
                                                subtract(a.getP2(), b.getP1())) < 0;
        }

        // Funciona para cualquier poligono excepto si es self-intersecting
        public double area()
        {
            double area = 0;
            for (Line2D line : lines) {
                area += line.getP1().getX() * line.getP2().getY();
                area -= line.getP2().getX() * line.getP1().getY();
            }
            area /= 2.0;
            return Math.abs(area);
        }

        // Funciona para cualquier poligono excepto si es self-intersecting
        public double areaUnsigned()
        {
            double area = 0;
            for (Line2D line : lines) {
                area += line.getP1().getX() * line.getP2().getY();
                area -= line.getP2().getX() * line.getP1().getY();
            }
            area /= 2.0;
            return area;
        }

        // Funciona para cualquier poligono excepto si es self-intersecting
        public Point2D centerOfMass()
        {
            double cx = 0, cy = 0;
            double area = areaUnsigned();
            double factor = 0;
            for (Line2D line : lines) {
                factor = line.getP1().getX() * line.getP2().getY()
                                - line.getP2().getX() * line.getP1().getY();
                cx += (line.getP1().getX() + line.getP2().getX()) * factor;
                cy += (line.getP1().getY() + line.getP2().getY()) * factor;
            }
            area *= 6.0d;
            factor = 1 / area;
            cx *= factor;
            cy *= factor;
            return new Point2D.Double(cx, cy);
        }

        public boolean intersects(IPolygon other)
        {
            for (Line2D lineA : lines) {
                if (other.contains(lineA.getP1())) return true;
                for (Line2D lineB : other.lines) {
                    if (lineA.intersectsLine(lineB)) return true;
                }
            }
            for (Line2D line : other.lines) {
                if (contains(line.getP1())) return true;
            }
            return false;
        }

        public boolean contains(Point2D p)
        {
            int cnt = 0;
            for (Line2D line : lines) {
                Point2D curr = subtract(line.getP1(), p);
                Point2D next = subtract(line.getP2(), p);
                if (curr.getY() > next.getY()) {
                    Point2D temp = curr;
                    curr = next;
                    next = temp;
                }
                if (curr.getY() < 0 && 0 <= next.getY()
                                && cross(next, curr) >= 0) {
                    cnt++;
                }
                if (is_point_online(line.getP1(), line.getP2(), p))
                    return true;
            }
            return cnt % 2 == 1;
        }
    }

    static class DisjointSet
    {
        int[] p, rank;

        public DisjointSet(int size)
        {
            rank = new int[size];
            p = new int[size];
            for (int i = 0; i < size; i++) {
                make_set(i);
            }
        }

        public void make_set(int x)
        {
            p[x] = x;
            rank[x] = 0;
        }

        public void merge(int x, int y)
        {
            link(find_set(x), find_set(y));
        }

        public void link(int x, int y)
        {
            if (rank[x] > rank[y])
                p[y] = x;
            else {
                p[x] = y;
                if (rank[x] == rank[y]) rank[y] += 1;
            }
        }

        public int find_set(int x)
        {
            if (x != p[x]) p[x] = find_set(p[x]);
            return p[x];
        }
    }

    public static void main(String[] args)
        throws NumberFormatException,
            IOException
    {
        int n = 0;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while ((n = Integer.parseInt(br.readLine())) != 0) {
            LinkedList<Polygon.IPolygon> poligonos = new LinkedList<Polygon.IPolygon>();
            for (int i = 0; i < n; i++) {
                String[] linea = br.readLine().split(" ");
                Polygon.IPolygon poligono = new Polygon.IPolygon(10);
                for (int j = 0; j < linea.length; j += 2) {
                    poligono.add(new Point2D.Double(Double
                                    .parseDouble(linea[j]), Double
                                    .parseDouble(linea[j + 1])));
                }
                poligono.close();
                poligonos.add(poligono);
            }
            DisjointSet dj = new DisjointSet(poligonos.size());
            int i = 0;
            for (Polygon.IPolygon a : poligonos) {
                int j = 0;
                for (Polygon.IPolygon b : poligonos) {
                    if (dj.find_set(i) == dj.find_set(j)) {
                        j++;
                        continue;
                    }
                    if (a.intersects(b)) {
                        dj.merge(i, j);
                    }
                    j++;
                }
                i++;
            }
            TreeSet<Integer> set = new TreeSet<Integer>();
            for (i = 0; i < poligonos.size(); i++)
                set.add(dj.find_set(i));
            System.out.println(set.size());
        }
    }
}
