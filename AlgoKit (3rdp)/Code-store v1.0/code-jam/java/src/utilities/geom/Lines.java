package utilities.geom;

import java.awt.geom.Point2D;
import java.io.IOException;
import java.util.Scanner;

public class Lines
{

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
        double px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2)
                        * (x3 * y4 - y3 * x4))
                        / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
        double py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2)
                        * (x3 * y4 - y3 * x4))
                        / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
        return new Point2D.Double(px, py);
    }

    // Esta implementado en Line2D - Distancia de un punto a un segmento

    double ptSegDist(
        double x1,
        double y1,
        double x2,
        double y2,
        double px,
        double py)
    {
        // Adjust vectors relative to x1,y1
        // x2,y2 becomes relative vector from x1,y1 to end of segment
        x2 -= x1;
        y2 -= y1;
        // px,py becomes relative vector from x1,y1 to test point
        px -= x1;
        py -= y1;
        double dotprod = px * x2 + py * y2;
        double projlenSq;
        if (dotprod <= 0.0) {
            // px,py is on the side of x1,y1 away from x2,y2
            // distance to segment is length of px,py vector
            // "length of its (clipped) projection" is now 0.0
            projlenSq = 0.0;
        } else {
            // switch to backwards vectors relative to x2,y2
            // x2,y2 are already the negative of x1,y1=>x2,y2
            // to get px,py to be the negative of px,py=>x2,y2
            // the dot product of two negated vectors is the same
            // as the dot product of the two normal vectors
            px = x2 - px;
            py = y2 - py;
            dotprod = px * x2 + py * y2;
            if (dotprod <= 0.0) {
                // px,py is on the side of x2,y2 away from x1,y1
                // distance to segment is length of (backwards) px,py vector
                // "length of its (clipped) projection" is now 0.0
                projlenSq = 0.0;
            } else {
                // px,py is between x1,y1 and x2,y2
                // dotprod is the length of the px,py vector
                // projected on the x2,y2=>x1,y1 vector times the
                // length of the x2,y2=>x1,y1 vector
                projlenSq = dotprod * dotprod / (x2 * x2 + y2 * y2);
            }
        }
        // Distance to line is now the length of the relative point
        // vector minus the length of its projection onto the line
        // (which is zero if the projection falls outside the range
        // of the line segment).
        double lenSq = px * px + py * py - projlenSq;
        if (lenSq < 0) {
            lenSq = 0;
        }
        return Math.sqrt(lenSq);
    }

    public static void main(String[] args)
        throws NumberFormatException,
            IOException
    {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println("INTERSECTING LINES OUTPUT");
        for (int i = 0; i < n; i++) {
            double x1 = sc.nextDouble();
            double y1 = sc.nextDouble();
            double x2 = sc.nextDouble();
            double y2 = sc.nextDouble();
            double x3 = sc.nextDouble();
            double y3 = sc.nextDouble();
            double x4 = sc.nextDouble();
            double y4 = sc.nextDouble();
            if (y2 - y1 == 0) {
                if (y4 - y3 == 0) {
                    if (y1 == y3) {
                        System.out.println("LINE");
                    } else {
                        System.out.println("NONE");
                    }
                } else {
                    Point2D interseccion = interseccionLineas(x1, y1, x2, y2,
                        x3, y3, x4, y4);
                    System.out.printf("POINT %.2d %.2d\n", interseccion.getX(),
                        interseccion.getY());
                }
            } else {
                double ma = (x2 - x1) / (y2 - y1);
                double mb = (x4 - x3) / (y4 - y3);
                if (Math.abs(ma - mb) < 1e-6) {
                    if (Math.abs((-y1 * ma + x1) - (-y3 * mb + x3)) < 1e-6) {
                        System.out.println("LINE");
                    } else {
                        System.out.println("NONE");
                    }
                } else {
                    Point2D interseccion = interseccionLineas(x1, y1, x2, y2,
                        x3, y3, x4, y4);
                    System.out.printf("POINT %.2f %.2f\n", interseccion.getX(),
                        interseccion.getY());
                }
            }
        }
        System.out.println("END OF OUTPUT");
    }

}
