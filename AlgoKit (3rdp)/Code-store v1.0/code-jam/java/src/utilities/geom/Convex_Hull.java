package utilities.geom;

import java.awt.geom.*;
import java.util.*;

public class Convex_Hull
{
    static double cross(Point2D p1, Point2D p2, Point2D p3)
    {
        return (p2.getX() - p1.getX()) * (p3.getY() - p1.getY())
                        - (p2.getY() - p1.getY()) * (p3.getX() - p1.getX());
    }

    static class Comp
        implements Comparator<Point2D>
    {
        @Override
        public int compare(Point2D p1, Point2D p2)
        {
            if (p1.getY() < p2.getY()) return -1;
            if (p1.getY() > p2.getY()) return 1;
            if (p1.getX() < p2.getX()) return -1;
            return 1;
        }
    }

    static final double EPSILON = 1e-12;

    static void convexHull(List<Point2D> points, List<Point2D> result)
    {
        int n = points.size();
        Point2D[] p2 = new Point2D[points.size() + 1];
        Collections.sort(points, new Comp());
        int top = 0;
        p2[top++] = points.get(0);
        p2[top++] = points.get(1);
        for (int i = 2; i < n; i++) {
            while (top >= 2
                            && cross(p2[top - 2], p2[top - 1], points.get(i)) <= -EPSILON)
                --top;
            p2[top++] = points.get(i);
        }
        int r = top;
        for (int i = n - 2; i >= 0; i--) {
            while (top > r
                            && cross(p2[top - 2], p2[top - 1], points.get(i)) <= -EPSILON)
                --top;
            if (i != 0) p2[top++] = points.get(i);
        }
        for (int i = 0; i < top; i++)
            result.add(p2[i]);
    }
}
