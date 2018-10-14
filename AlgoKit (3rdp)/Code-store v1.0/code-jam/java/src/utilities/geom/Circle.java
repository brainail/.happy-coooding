package utilities.geom;

public class Circle
{
    public Point center;
    public double radius;

    public Circle(Point center, double radius)
    {
        this.center = center;
        this.radius = radius;
    }

    /**
     * Determine the points where 2 circles in a common plane intersect
     * 
     * @param that, ie. other circle
     * @return Point[], containing the intersection points of these two circles
     */
    public Point[] intersection(Circle that)
    {
        // see: http://mathworld.wolfram.com/Circle-CircleIntersection.html
        double d = this.center.distanceTo(that.center);
        double d1 = ((this.radius * this.radius) - (that.radius * that.radius) + (d * d))
                        / (2 * d);
        double h = Math.sqrt((this.radius * this.radius) - (d1 * d1));
        double x3 = this.center.x + (d1 * (that.center.x - this.center.x)) / d;
        double y3 = this.center.y + (d1 * (that.center.y - this.center.y)) / d;
        double x4_i = x3 + (h * (that.center.y - this.center.y)) / d;
        double y4_i = y3 - (h * (that.center.x - this.center.x)) / d;
        double x4_ii = x3 - (h * (that.center.y - this.center.y)) / d;
        double y4_ii = y3 + (h * (that.center.x - this.center.x)) / d;

        if (Double.isNaN(x4_i)) {
            // no intersections
            return new Point[0];
        }

        // create the intersection points
        Point i1 = new Point(x4_i, y4_i);
        Point i2 = new Point(x4_ii, y4_ii);

        if (i1.distanceTo(i2) < 1E-10) {
            // i1 and i2 are (more or less) the same: a single intersection
            return new Point[] { i1 };
        }

        // two unique intersections
        return new Point[] { i1, i2 };
    }

    @Override
    public String toString()
    {
        return String.format("{center=%s, radius=%.2f}", center, radius);
    }
}
