package utilities.geom;

import java.awt.geom.*;
import java.io.*;
import java.math.*;
import java.util.*;

public class SEC
{
    static class Circle
    {
        private Point2D p;
        private double r;

        public Circle()
        {
            p = new Point2D.Double(0, 0);
            r = 0;
        }

        public Circle(Circle circle)
        {
            p = new Point2D.Double(circle.p.getX(), circle.p.getY());
            r = circle.r;
        }

        public Circle(Point2D center, double radius)
        {
            p = new Point2D.Double(center.getX(), center.getY());
            r = radius;
        }

        public Circle(Point2D center)
        {
            p = new Point2D.Double(center.getX(), center.getY());
            r = 0;
        }

        public static Point2D midPoint(Point2D a, Point2D b)
        {
            return new Point2D.Double((a.getX() + b.getX()) / 2,
                            (a.getY() + b.getY()) / 2);
        }

        public Circle(Point2D p1, Point2D p2)
        {
            p = midPoint(p1, p2);
            r = p1.distance(p);
        }

        public Circle(Point2D p1, Point2D p2, Point2D p3)
        {
            try {
                double x = (p3.getX()
                                * p3.getX()
                                * (p1.getY() - p2.getY())
                                + (p1.getX() * p1.getX() + (p1.getY() - p2
                                                .getY())
                                                * (p1.getY() - p3.getY()))
                                * (p2.getY() - p3.getY()) + p2.getX()
                                * p2.getX() * (-p1.getY() + p3.getY()))
                                / (2 * (p3.getX() * (p1.getY() - p2.getY())
                                                + p1.getX()
                                                * (p2.getY() - p3.getY()) + p2
                                                .getX()
                                                * (-p1.getY() + p3.getY())));
                double y = (p2.getY() + p3.getY()) / 2
                                - (p3.getX() - p2.getX())
                                / (p3.getY() - p2.getY())
                                * (x - (p2.getX() + p3.getX()) / 2);
                p = new Point2D.Double(x, y);
                r = p.distance(p1);
                if (Double.isInfinite(r) || Double.isInfinite(x)
                                || Double.isInfinite(y) || Double.isNaN(r)
                                || Double.isNaN(x) || Double.isNaN(y)) {
                    r = 0;
                    p = new Point2D.Double(0, 0);
                }
            } catch (Exception e) {
            }
        }

        public Point2D getCenter()
        {
            return p;
        }

        public double getRadius()
        {
            return r;
        }

        public void setCenter(Point2D center)
        {
            p.setLocation(center);
        }

        public void setRadius(double radius)
        {
            r = radius;
        }

        public void translate(Point2D newCenter)
        {
            p.setLocation(newCenter);
        }

        public void offset(double dr)
        {
            r += dr;
        }

        public void scale(double factor)
        {
            r *= factor;
        }

        public double getDiameter()
        {
            return (2 * r);
        }

        public double getCircumference()
        {
            return (Math.PI * 2 * r);
        }

        public double getArea()
        {
            return (Math.PI * r * r);
        }

        public int contain(Point2D point)
        {
            int answer = 0;
            double d = p.distance(point);
            if (d > r) {
                answer = 1; // The point is outside the circle
            } else if (d == r) {
                answer = 0; // The point is on the circumference of the circle
            } else {
                answer = -1; // The point is inside the circle
            }
            return answer;
        }

        public boolean equals(Circle circle)
        {
            return p.equals(circle.p) && (r == circle.r);
        }
    }

    public static Circle sec(ArrayList<Point2D> a)
    {
        Point2D[] p = new Point2D[a.size()];
        a.toArray(p);
        return findSec(a.size(), p, 0, new Point2D[3]);
    }

    // Compute the Smallest Enclosing Circle of the n points in p,
    // such that the m points in B lie on the boundary of the circle.
    public static Circle findSec(int n, Point2D[] p, int m, Point2D[] b)
    {
        Circle sec = new Circle();
        if (m == 1) {
            sec = new Circle(b[0]);
        } else if (m == 2) {
            sec = new Circle(b[0], b[1]);
        } else if (m == 3) {
            return new Circle(b[0], b[1], b[2]);
        }
        for (int i = 0; i < n; i++) {
            if (sec.contain(p[i]) == 1) {
                b[m] = new Point2D.Double();
                b[m].setLocation(p[i]);
                sec = findSec(i, p, m + 1, b);
            }
        }
        return sec;
    }

    public static void main(String[] args)
        throws IOException
    {

        System.setIn(new FileInputStream("c.in"));
        System.setOut(new PrintStream("c.sol"));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while (true) {
            int numero = Integer.parseInt(br.readLine());
            if (numero == 0) return;
            ArrayList<Point2D> puntos = new ArrayList<Point2D>(numero);
            for (int i = 0; i < numero; i++) {
                String[] pedazos = br.readLine().split(" ");
                double x = java.lang.Double.parseDouble(pedazos[0]);
                double y = java.lang.Double.parseDouble(pedazos[1]);
                puntos.add(new Point2D.Double(x, y));
            }
            Circle circulo = sec(puntos);
            System.out.printf("%s %s %s\n", new BigDecimal(circulo.p.getX())
                            .divide(BigDecimal.ONE, 2,
                                BigDecimal.ROUND_HALF_EVEN), new BigDecimal(
                            circulo.p.getY()).divide(BigDecimal.ONE, 2,
                BigDecimal.ROUND_HALF_EVEN), new BigDecimal(circulo.r).divide(
                BigDecimal.ONE, 2, BigDecimal.ROUND_HALF_EVEN));
        }
    }
}
