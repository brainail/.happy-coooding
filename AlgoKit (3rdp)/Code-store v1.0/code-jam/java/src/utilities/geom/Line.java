package utilities.geom;

public class Line
    extends Shape
{
    Point p, q;

    public Line(Point P, Point Q)
    {
        p = P;
        q = Q;
    }

    public Line(double x1, double y1, double x2, double y2)
    {
        p = new Point(x1, y1);
        q = new Point(x2, y2);
    }

    public Line(Point P, double m)
    {
        p = P;
        q = new Point(p.x + .3, q.x + .3 * m);
    }

    @Override
    public boolean exists()
    {
        if (p.exists() && q.exists())
            return (true);
        else
            return (false);
    }

    @Override
    public Point intersect(Shape s, int whichPoint)
    {
        if (s instanceof Line)
            return (GeometryUtils.intersect(this, (Line) s));
        else
            return (null);
    }

    @Override
    public void translate(double dx, double dy)
    {
        p.translate(dx, dy);
        q.translate(dx, dy);
    }

    public double slope()
    {
        if (Math.abs(p.x - q.x) < 1e-10)
            return 1e10;
        else if (p.x < q.x)
            return ((q.y - p.y) / (q.x - p.x));
        else
            return ((p.y - q.y) / (p.x - q.x));
    }

    public Point coordOnShape(double X, double Y)
    {
        double nx = -(q.y - p.y);
        double ny = q.x - p.x;
        double length = Math.sqrt(nx * nx + ny * ny);
        nx /= length;
        ny /= length;

        double baseDist = p.x * nx + p.y * ny;
        double PointDist = X * nx + Y * ny;

        X -= nx * (PointDist - baseDist);
        Y -= ny * (PointDist - baseDist);

        return new Point(X, Y);
    }
}
