package utilities.vector;

import java.io.*;

import static java.lang.Math.*;
import static utilities.Constants.*;
import utilities.geom.*;
import utilities.struct.*;

/**
 * A 2-element vector that is represented by double-precision floating point x,y
 * coordinates.
 * 
 */
public class Vector2d
    extends Tuple2d
    implements Serializable
{
    // Combatible with 1.1
    static final long serialVersionUID = 8572646365302599857L;

    private Angle theta = null;
    private double r = Double.NEGATIVE_INFINITY;

    /** A Vect with zero length */
    public static final Vector2d ZERO = new Vector2d(0.0, 0.0, 0.0, Angle.ZERO);

    /** A unit vector in the positive x direction */
    public static final Vector2d X_HAT = new Vector2d(1.0, 0.0, 1.0, Angle.ZERO);

    /** A unit vector in the positive y direction */
    public static final Vector2d Y_HAT = new Vector2d(0.0, 1.0, 1.0,
                    Angle.DEG_90);

    public Vector2d(double x, double y, double r, Angle theta)
    {
        this.x = x;
        this.y = y;
        this.r = r;
        this.theta = theta;
    }

    public Vector2d(Point pt)
    {
        x = pt.x;
        y = pt.y;
    }

    /**
     * Constructs and initializes a Vector2d from the specified xy coordinates.
     * 
     * @param x the x coordinate
     * @param y the y coordinate
     */
    public Vector2d(double x, double y)
    {
        super(x, y);
        computeRThetaFromXY();
    }

    public Vector2d(Angle a, double r)
    {
        theta = a;
        this.r = r;
        computeXYFromRTheta();
    }

    /**
     * Constructs and initializes a Vector2d from the specified array.
     * 
     * @param v the array of length 2 containing xy in order
     */
    public Vector2d(double[] v)
    {
        super(v);
    }

    /**
     * Constructs and initializes a Vector2d from the specified Vector2d.
     * 
     * @param v1 the Vector2d containing the initialization x y data
     */
    public Vector2d(Vector2d v1)
    {
        super(v1);
    }

    /**
     * Constructs and initializes a Vector2d from the specified Tuple2d.
     * 
     * @param t1 the Tuple2d containing the initialization x y data
     */
    public Vector2d(Tuple2d t1)
    {
        super(t1);
    }

    /**
     * Constructs and initializes a Vector2d to (0,0).
     */
    public Vector2d()
    {
        super();
    }

    /**
     * Static creation method for a Vector2d object
     */
    public static Vector2d of(double x, double y)
    {
        return new Vector2d(x, y);
    }

    /* Basic numeric operations */
    public Vector2d add(Vector2d b)
    {
        return new Vector2d(x + b.x, y + b.y);
    }

    public Vector2d sub(Vector2d b)
    {
        return new Vector2d(x - b.x, y - b.y);
    }

    public Vector2d mul(double b)
    {
        return new Vector2d(x * b, y * b);
    }

    /**
     * Computes the dot product of the this vector and vector v1.
     * 
     * @param v1 the other vector
     */
    public double dot(Vector2d v1)
    {
        return (this.x * v1.x + this.y * v1.y);
    }

    /**
     * Returns the length of this vector.
     * 
     * @return the length of this vector
     */
    public double length()
    {
        return Math.sqrt(lengthSquared());
    }

    /**
     * Returns the squared length of this vector.
     * 
     * @return the squared length of this vector
     */
    public double lengthSquared()
    {
        return (Math.pow(this.x, 2) + Math.pow(this.y, 2));
    }

    /**
     * Sets the value of this vector to the normalization of vector v1.
     * 
     * @param v1 the un-normalized vector
     */
    public void normalize(Vector2d v1)
    {
        double norm;

        norm = (1.0 / Math.sqrt(v1.x * v1.x + v1.y * v1.y));
        this.x = v1.x * norm;
        this.y = v1.y * norm;
    }

    /**
     * Normalizes this vector in place. Also returns a copy of this unit vector
     * if necessary
     */
    public Vector2d normalize()
    {
        double norm = 1.0 / length();
        this.x *= norm;
        this.y *= norm;
        return new Vector2d(x, y);
    }

    /**
     * Returns the angle in radians between this vector and the vector
     * parameter; the return value is constrained to the range [0,PI].
     * 
     * @param v1 the other vector
     * @return the angle in radians in the range [0,PI]
     */
    public double angle(Vector2d v1)
    {
        double vDot = this.dot(v1) / (this.length() * v1.length());
        if (vDot < -1.0) vDot = -1.0;
        if (vDot > 1.0) vDot = 1.0;
        return ((Math.acos(vDot)));

    }

    /* Transformations between rectangular <=> polar coordinates */
    public void computeRThetaFromXY()
    {
        r = Math.sqrt((x * x) + (y * y));
        if (r == 0.0) {
            theta = Angle.ZERO;
        } else {
            theta = new Angle(x, y);
        }
    }

    public void computeXYFromRTheta()
    {
        if (r == Double.NEGATIVE_INFINITY || theta == null) {
            System.err.println("Vector2d: (r, theta) not initialised from (x, y)");
        }
        x = r * theta.cos();
        y = r * theta.sin();
    }

    /**
     * @requires <code>a</code> is not null
     * @return a vector that is equivalent to <code>this</code> having been
     *         rotated around the origin by <code>a</code>.
     */
    public void rotateBy(Angle a)
    {
        computeRThetaFromXY();
        theta = theta.plus(a);
        computeXYFromRTheta();
    }

    /**
     * Returns the projection of this onto <code>b</code><br>
     * 
     * <img src="doc-files/project.gif">
     * 
     * @requires <code>b</code> is not null
     * @return a vector resulting from projecting <code>this</code> onto
     *         <code>b</code>. The resulting vector has the same angle as
     *         <code>b</code>, but its length is such that <code>this</code> -
     *         <code>c</code> is perpendicular to <code>c</code>.
     **/
    public Vector2d projectOn(Vector2d other)
    {
        Vector2d b = new Vector2d(other.x, other.y);
        b.normalize();
        double magnitude = dot(b);
        b.scale(magnitude);
        b.computeRThetaFromXY();
        return b;
    }

    public double distanceTo(Vector2d that)
    {
        return sqrt(pow((that.x - x), 2) + pow(that.y - y, 2));
    }

    @Override
    public String toString()
    {
        return "(x,y,r,theta): " + "(" + x + "," + y + "," + r + "," + theta
                        + ")";
    }

    public boolean equals(Vector2d v)
    {
        return (abs(x - v.x) < DBL_EPSILON && abs(y - v.y) < DBL_EPSILON);
    }

    @Override
    public boolean equals(Object o)
    {
        return (o instanceof Vector2d) && this.equals((Vector2d) o);
    }

    @Override
    public int hashCode()
    {
        return (new Double(x)).hashCode() + (new Double(y)).hashCode();
    }
}
