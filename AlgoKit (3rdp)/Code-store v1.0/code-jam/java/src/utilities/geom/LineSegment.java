package utilities.geom;

import java.io.*;

public class LineSegment
    extends Line
    implements Serializable
{
    private static final long serialVersionUID = 5535996522526579787L;

    public LineSegment(Point P, Point Q)
    {
        super(P, Q);
    }

    public LineSegment(double x1, double y1, double x2, double y2)
    {
        super(x1, y1, x2, y2);
    }

    public LineSegment(Point P, double m)
    {
        super(P, m);
    }

    /**
     * @return the length of <code>this</code>.
     */
    public double length()
    {
        return (Math.sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y)));
    }

    /**
     * @return the angle from the x-axis of <code>this</code>.
     */
    public Angle angle()
    {
        return new Angle(q.x - p.x, q.y - p.y);
    }

    @Override
    public String toString()
    {
        return "LineSegment(" + p + "-" + q + ")";
    }

    public boolean equals(LineSegment ls)
    {
        if (ls == null) return false;
        return (p.equals(ls.p) && q.equals(ls.q));
    }

    @Override
    public boolean equals(Object o)
    {
        if (o instanceof LineSegment)
            return equals((LineSegment) o);
        else
            return false;
    }

    @Override
    public int hashCode()
    {
        return p.hashCode() + q.hashCode();
    }
}
