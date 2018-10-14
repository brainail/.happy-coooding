package utilities.algo;

import java.awt.geom.*;

public class LineIntersection
{
    public static Point2D.Double intersect(
        double x11,
        double y11,
        double x12,
        double y12,
        double x21,
        double y21,
        double x22,
        double y22)
    {
        // l1 = p11 x p12
        // |i j k|
        // = |p11.x p11.y 1|
        // |p12.x p12.y 1|
        double l1x = y11 - y12;
        double l1y = x12 - x11;
        double l1w = x11 * y12 - y11 * x12;
        double l2x = y21 - y22;
        double l2y = x22 - x21;
        double l2w = x21 * y22 - y21 * x22;

        // i = l1 x l2
        // |i j k|
        // = |l1.x l1.y l1.w|
        // = |l2.x l2.y l2.w|
        double ix = l1y * l2w - l1w * l2y;
        double iy = l1w * l2x - l1x * l2w;
        double iw = l1x * l2y - l1y * l2x;

        System.out.println("ix = " + ix);
        System.out.println("iy = " + iy);
        System.out.println("iw = " + iw);

        return new Point2D.Double(ix / iw, iy / iw);
    }

    public static void main(String args[])
    {
        System.out.println(intersect(0, 0, 4, 5, 0, 5, 4, 0));
        System.out.println(intersect(0, 0, 4, 5, 5, 5, 6, 6));
    }
}
