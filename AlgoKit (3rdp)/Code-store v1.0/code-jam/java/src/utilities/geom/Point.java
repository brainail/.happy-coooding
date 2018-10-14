package utilities.geom;

import java.util.*;

import static java.lang.Math.*;

/**
 * Usage instructions:
 * 
 * - To sort a list of Points by their increasing distance to a base point (x,y)
 * <code>
 *      Arrays.sort(points, base.BY_DISTANCE_TO);
 * </code>
 */
public class Point
    extends Shape
    implements Comparable<Point>
{
    public double x, y;
    public final Comparator<Point> BY_DISTANCE_TO = new ByDistanceToComparator();
    public final Comparator<Point> BY_CCW = new ByCCWComparator();
    public static final Comparator<Point> BY_X = new ByXComparator();
    public static final Comparator<Point> BY_Y = new ByYComparator();

    /**
     * create and initialise a point with given (x, y)
     * 
     * @param x
     * @param y
     */
    public Point(double x, double y)
    {
        this.x = x;
        this.y = y;
    }

    /**
     * Static creation method for a Point object
     */
    public static Point of(double x, double y)
    {
        return new Point(x, y);
    }

    public void set(double X, double Y)
    {
        x = X;
        y = Y;
    }

    public void setPoint(Point xy)
    {
        x = xy.x;
        y = xy.y;
    }

    public void move(double dx, double dy)
    {
        x += dx;
        y += dy;
    }

    public double degrees(Point that)
    {
        double deg = toDegrees(Math.atan2(that.y - this.y, that.x - this.x));
        return deg < 0.0 ? deg + 360 : deg;
    }

    /**
     * return Euclidean distance between this point and that
     * 
     * @param that
     * @return
     */
    public double distanceTo(Point that)
    {
        double dX = this.x - that.x, dY = this.y - that.y;
        return sqrt(pow(dX, 2) + pow(dY, 2));
    }

    /**
     * is a->b->c a counter-clockwise turn?
     * -1 if clockwise, +1 if counter-clockwise, 0 if collinear
     * 
     * @param a
     * @param b
     * @param c
     * @return
     */
    public static int ccw(Point a, Point b, Point c)
    {
        double area2 = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
        if (area2 < 0)
            return -1;
        else if (area2 > 0)
            return 1;
        else
            return 0;
    }

    /**
     * 2 x signed area(a-b-c)
     * 
     * @param a
     * @param b
     * @param c
     * @return
     */
    public static double area2(Point a, Point b, Point c)
    {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    /**
     * natural order: compare by y-coordinate; break ties by x-coordinate
     */
    @Override
    public int compareTo(Point that)
    {
        if (this.y < that.y) return -1;
        if (this.y > that.y) return 1;
        if (this.x > that.x) return -1;
        if (this.x < that.x) return 1;
        return 0;
    }

    /**
     * are the x- y-coordinates of the two points the same?
     */
    @Override
    public boolean equals(Object y)
    {
        if (y == this) return true;
        if (y == null) return false;
        if (y.getClass() != this.getClass()) return false;
        Point that = (Point) y;
        return (this.x == that.x) && (this.y == that.y);
    }

    /**********************************************************************
     * Comparator that compares points according to polar angle
     * they make with this point. The polar angle is measured with
     * respect to a ray emanating from this point and pointing eastward.
     * Break ties according to distance to this point.
     * 
     * Tie-breaking rule is only for degeneracy, e.g., if three
     * collinear points on the convex hull, then this enables us
     * to grab only first and last points.
     * 
     * Precondition: q1 and q2 are in upper quadrant, relative to p.
     * 
     * Technically, this breaks the contract for compare() if
     * called with points with y coordinate less than p.
     * 
     **********************************************************************/
    public class ByCCWComparator
        implements Comparator<Point>
    {
        @Override
        public int compare(Point q1, Point q2)
        {
            int ccw = ccw(Point.this, q1, q2);
            if (ccw == -1) return -1;
            if (ccw == +1) return +1;

            double dx1 = q1.x - x;
            double dx2 = q2.x - x;
            double dy1 = q1.y - y;
            double dy2 = q2.y - y;

            // assert dy1 >= 0 && dy2 >= 0; // or breaks compare() contract

            // break ties by distance to this point
            // should be able to replace distance calculation with
            // projection because three points are collinear
            if (dx1 * dx1 + dy1 * dy1 < dx2 * dx2 + dy2 * dy2)
                return -1;
            else if (dx1 * dx1 + dy1 * dy1 > dx2 * dx2 + dy2 * dy2)
                return +1;
            else
                return 0;
        }
    }

    /**
     * compare points according to their distance to this point
     */
    public class ByDistanceToComparator
        implements Comparator<Point>
    {
        @Override
        public int compare(Point p, Point q)
        {
            if (distanceTo(p) < distanceTo(q))
                return -1;
            else if (distanceTo(p) > distanceTo(q))
                return +1;
            else
                return 0;
        }
    }

    /**
     * compare points according to their x-coordinate,
     * breaking ties by y-coordinate
     */
    public static class ByXComparator
        implements Comparator<Point>
    {
        @Override
        public int compare(Point p, Point q)
        {
            if (p.x < q.x) return -1;
            if (p.x > q.x) return +1;
            if (p.y < q.y) return -1;
            if (p.y > q.y) return +1;
            return 0;
        }
    }

    /**
     * compare points according to their y-coordinate, breaking ties by
     * x-coordinate
     */
    public static class ByYComparator
        implements Comparator<Point>
    {
        @Override
        public int compare(Point p, Point q)
        {
            if (p.y < q.y) return -1;
            if (p.y > q.y) return +1;
            if (p.x < q.x) return -1;
            if (p.x > q.x) return +1;
            return 0;
        }
    }

    @Override
    public String toString()
    {
        return String.format("(%.2f,%.2f)", x, y);
    }
}
