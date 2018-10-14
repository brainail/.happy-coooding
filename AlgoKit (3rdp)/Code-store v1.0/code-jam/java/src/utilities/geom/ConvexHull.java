package utilities.geom;

/**************************************************************************
 * Create 2D points to compute the convex hull using Graham scan algorithm
 *************************************************************************/

//Point[] pts = new Point[xs.length];
//for (int i = 0; i < pts.length; i++) {
//    pts[i] = new Point(xs[i], ys[i]);
//}
//ConvexHull2D graham = new ConvexHull2D(pts);
//for (Point p : graham.hull()) {
//  System.out.println(p);
//}
//graham.getAreaOfHull();

import static java.lang.Math.*;

import java.util.*;

public class ConvexHull
{
    private final Stack<Point> hull = new Stack<Point>();

    public ConvexHull(Point[] pts)
    {
        // defensive copy
        int N = pts.length;
        Point[] points = new Point[N];
        for (int i = 0; i < N; i++)
            points[i] = pts[i];

        // preprocess so that points[0] has lowest y-coordinate; break ties by
        // x-coordinate points[0] is an extreme point of the convex hull
        Arrays.sort(points);

        // sort by polar angle with respect to base point points[0],
        // breaking ties by distance to points[0]
        Arrays.sort(points, 1, N, points[0].BY_CCW);

        hull.push(points[0]); // p[0] is first extreme point

        // find index k1 of first point not equal to points[0]
        int k1;
        for (k1 = 1; k1 < N; k1++)
            if (!points[0].equals(points[k1])) break;
        if (k1 == N) return; // all points equal

        // find index k2 of first point not collinear with points[0] and
        // points[k1]
        int k2;
        for (k2 = k1 + 1; k2 < N; k2++)
            if (Point.ccw(points[0], points[k1], points[k2]) != 0) break;
        hull.push(points[k2 - 1]); // points[k2-1] is second extreme point

        // Graham scan; note that points[N-1] is extreme point different from
        // points[0]
        for (int i = k2; i < N; i++) {
            Point top = hull.pop();
            while (Point.ccw(top, hull.peek(), points[i]) <= 0) {
                top = hull.pop();
            }
            hull.push(top);
            hull.push(points[i]);
        }
    }

    public Stack<Point> getHull()
    {
        return hull;
    }

    public double getAreaOfHull()
    {
        if (hull.size() < 3) {
            return 0.0;
        } else {
            double area = 0.0;
            Point pivot = hull.pop();
            while (hull.size() > 1) {
                Point p1 = hull.pop(), p2 = hull.peek();
                double a = p1.distanceTo(p2), b = p2.distanceTo(pivot), c = p1
                                .distanceTo(pivot);
                area += heronsFormula(a, b, c);
            }
            return area;
        }
    }

    public double heronsFormula(double a, double b, double c)
    {
        double s = .5 * (a + b + c);
        double area = sqrt(s * (s - a) * (s - b) * (s - c));
        return area;
    }
}
