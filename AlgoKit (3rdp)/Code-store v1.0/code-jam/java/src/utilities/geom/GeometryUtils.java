package utilities.geom;

import static java.lang.Math.*;

public class GeometryUtils
{
    public static double distanceBetween(Point p, Point q)
    {
        return sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));
    }

    public static double distanceBetween(
        double x1,
        double y1,
        double x2,
        double y2)
    {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    public static double length(double x, double y)
    {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    public static double length(LineSegment s)
    {
        return distanceBetween(s.p, s.q);
    }

    public static double angle(Point a, Point b, Point c)
    {
        double v1x = a.x - b.x;
        double v1y = a.y - b.y;
        double v1Length = length(v1x, v1y);

        double v2x = c.x - b.x;
        double v2y = c.y - b.y;
        double v2Length = length(v2x, v2y);

        if ((v2Length < 1e-7) || (v1Length < 1e-7)) {
            return 0;
        }

        return (acos((v1x * v2x + v1y * v2y) / (v1Length * v2Length)));
    }

    public static double sgn(double x)
    {
        return ((x < 0) ? -1.0 : 1.0);
    }

    public static Point intersect(Line L1, Line L2)
    {
        double px = L1.p.x, py = L1.p.y;
        double qx = L1.q.x, qy = L1.q.y;
        double rx = L2.p.x, ry = L2.p.y;
        double sx = L2.q.x, sy = L2.q.y;
        double vx = qx - px;
        double vy = qy - py;
        double wx = sx - rx;
        double wy = sy - ry;
        double nx = -wy;
        double ny = wx;

        if (((abs(wx) < 1e-7) && (abs(wy) < 1e-7))
                        || ((abs(vx) < 1e-7) && (abs(vy) < 1e-7))) return null;

        double nDotv = vx * nx + vy * ny;

        if (nDotv < 1e-7) return null;

        double lambda = (nx * (rx - px) + ny * (ry - py)) / nDotv;

        if (L1 instanceof LineSegment)
            if ((lambda < 0) || (lambda > 1)) return null;

        double x = lambda * vx + px;
        double y = lambda * vy + py;

        double kappa;
        if (abs(wx) > 1e-7)
            kappa = (x - rx) / wx;
        else
            kappa = (y - ry) / wy;

        if (L2 instanceof LineSegment)
            if ((kappa < 0) || (kappa > 1)) return null;

        return new Point(x, y);
    }

    public static Point intersect(Circle c, Line l, int whichPoint)
    {
        double px = l.p.x - c.center.x;
        double py = l.p.y - c.center.y;
        double qx = l.q.x - c.center.x;
        double qy = l.q.y - c.center.y;

        whichPoint = whichPoint >= 0 ? 1 : -1;

        double pxSqr = px * px;
        double pySqr = py * py;
        double pxqx = px * qx;
        double pyqy = py * qy;

        double gamma = pxSqr + pySqr + qx * qx + qy * qy - 2 * pxqx - 2 * pyqy;
        double delta = 2 * pxqx + 2 * pyqy - 2 * pxSqr - 2 * pySqr;

        double lambda;
        double r = c.radius;

        if (gamma == 0) {
            if (delta == 0) return null;

            lambda = (r * r - pxSqr - pySqr) / delta;
        } else {
            double argument = (r * r - pxSqr - pySqr) / gamma + delta * delta
                            / (4 * gamma * gamma);

            if (argument < 0) return null;

            lambda = whichPoint * sqrt(argument) - delta / (2 * gamma);
        }

        return (new Point((1 - lambda) * px + lambda * qx + c.center.x,
                        (1 - lambda) * py + lambda * qy + c.center.y));
    }

    public static Point intersect(Circle c1, Circle c2, int whichPoint)
    {
        double a = c1.center.x - c2.center.x;
        double b = c1.center.y - c2.center.y;
        double x, y;
        double r = c1.radius;
        double s = c2.radius;

        if (whichPoint >= 0)
            whichPoint = 1;
        else
            whichPoint = -1;

        if (abs(a) >= 1e-10) {
            double delta = -b / a;
            double gamma = (a * a + b * b - r * r + s * s) / (2 * a);
            double denom = delta * delta + 1;
            double gammaSquared = gamma * gamma;

            double argument = (s * s - gammaSquared) / denom
                            + (delta * delta * gammaSquared) / (denom * denom);

            if (argument < 0) return null;

            y = sgn(a) * whichPoint * sqrt(argument) - delta * gamma / denom;
            x = delta * y + gamma;
        } else if (abs(b) >= 1e-10) {
            // delta = -a / b = 0 in this case
            double gamma = (b * b - r * r + s * s) / (2 * b); // a*a = 0 in this
                                                              // case
            // denom = 1 in this case

            double argument = s * s - gamma * gamma;

            if (argument < 0) return null;

            x = -sgn(b) * whichPoint * sqrt(argument); // the - is for
                                                       // consistency, in
                                                       // the previous
            y = gamma; // case delta is negative.
        } else
            return null;

        return new Point(x + c2.center.x, y + c2.center.y);
    }

    public Point perpendicularPoint(LineSegment line, Point point)
    {
        double x1 = line.p.x, y1 = line.p.y, x2 = line.q.x, y2 = line.q.y, a = point.x, b = point.y;

        double height = (y2 - y1);
        double width = (x2 - x1);

        double lengthSquared = (height * height) + (width * width);
        double fraction = (((width * (a - x1)) + (height * (b - y1))) / lengthSquared);

        if (fraction < 0 || fraction > 1) {
            return null;
        }

        double pptx = x1 + fraction * width;
        double ppty = y1 + fraction * height;

        return new Point(pptx, ppty);
    }
}
