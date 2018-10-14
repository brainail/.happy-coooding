package utilities.geom;

import static java.lang.Math.*;

import java.io.*;

public final class Angle
    implements Serializable, Comparable<Object>
{
    private static final long serialVersionUID = -2301630032062979228L;
    public double cosine;
    public double sine;

    private static final double SQRT = Math.sqrt(0.5);

    /** A zero-degree or zero-radian angle */
    public static final Angle ZERO = new Angle(1.0, 0.0);
    /** A 45-degree angle */
    public static final Angle DEG_45 = new Angle(SQRT, SQRT);
    /** A 90-degree angle */
    public static final Angle DEG_90 = new Angle(0.0, 1.0);
    /** A 135-degree angle */
    public static final Angle DEG_135 = new Angle(-SQRT, SQRT);
    /** A 180-degree angle */
    public static final Angle DEG_180 = new Angle(-1.0, 0.0);
    /** A 225-degree angle */
    public static final Angle DEG_225 = new Angle(-SQRT, -SQRT);
    /** A 270-degree angle */
    public static final Angle DEG_270 = new Angle(0.0, -1.0);
    /** A 315-degree angle */
    public static final Angle DEG_315 = new Angle(SQRT, -SQRT);
    /** An angle of pi/4 radians */
    public static final Angle RAD_PI_OVER_FOUR = DEG_45;
    /** An angle of pi/2 radians */
    public static final Angle RAD_PI_OVER_TWO = DEG_90;
    /** An angle of pi radians */
    public static final Angle RAD_PI = DEG_180;

    // CONSTRUCTORS:
    /**
     * @effects constructs an <code>Angle</code> with <code>radians</code>
     *          radians.
     */
    public Angle(double radians)
    {
        cosine = Math.cos(radians);
        sine = Math.sin(radians);
    }

    /**
     * @requires (x,y) != (0,0)
     * 
     * @effects constructs the <code>Angle</code> that is formed between the
     *          positive x-axis and the line from the origin to (<code>x</code>,
     *          <code>y</code>).
     **/
    public Angle(double x, double y)
    {
        double r = Math.sqrt((x * x) + (y * y));
        if (r == 0.0) {
            if ((x == 0.0) && (y == 0.0)) {
                throw new IllegalArgumentException(
                                "Requires violated: Triangle is singular");
            } else {
                throw new ArithmeticException(
                                "Triangle is singular; imprecision on <" + x
                                                + "," + y + ">");
            }
        }
        cosine = x / r;
        sine = y / r;
    }

    // OBSERVERS:
    /**
     * @return the cosine of this.
     */
    public double cos()
    {
        return cosine;
    }

    /**
     * @return the sine of this.
     */
    public double sin()
    {
        return sine;
    }

    /**
     * @return the tangent of this.
     */
    public double tan()
    {
        return sine / cosine;
    }

    /**
     * @return the number of radians represented by this in the range of -pi to
     *         pi.
     **/
    public double radians()
    {
        double d = atan2(sine, cosine);
        if (d > Math.PI || d < -Math.PI) {
            System.out.println("d = " + d);
            throw new IllegalArgumentException();
        }
        return d;
    }

    /**
     * Compares this object with the specified object for order.
     * 
     * @return a negative integer, zero, or a positive integer as this object is
     *         less than, equal to, or greater than the specified object.
     * @exception ClassCastException if <code>o</code> is not an Angle
     * @exception NullPointerException if <code>o</code> is null
     */
    @Override
    public int compareTo(Object o)
    {
        // Comparable.compareTo allows us to throw a ClassCastException
        return compareTo((Angle) o);
    }

    /**
     * Compares this object with the specified object for order.
     * 
     * @return a negative integer, zero, or a positive integer as this object is
     *         less than, equal to, or greater than the specified object.
     * @exception NullPointerException if <code>c</code> is null
     */
    public int compareTo(Angle c)
    {
        if (this.equals(c)) return 0;

        // first discriminate on the basis of top vs. bottom half (sin)
        // then discriminate on the basis of left vs. right half (cos)

        if (sine >= 0.0) {
            if (c.sine < 0.0) {
                return -1;
            } else {
                if (cosine < c.cosine) {
                    return 1;
                } else {
                    return -1;
                }
            }
        } else {
            if (c.sine >= 0.0) {
                return 1;
            } else {
                if (cosine < c.cosine) {
                    return -1;
                } else {
                    return 1;
                }
            }
        }
    }

    // PRODUCERS:
    /**
     * @requires <code>a</code> is not null
     * @return the angle <code>this</code> + <code>a</code>.
     */
    public Angle plus(Angle a)
    {
        // These are standard trig identities. See the appendix of your
        // favorite calculus text book.
        double cosine = (this.cosine * a.cosine) - (this.sine * a.sine);
        double sine = (this.sine * a.cosine) + (this.cosine * a.sine);

        return new Angle(cosine, sine);
    }

    /**
     * @requires <code>a</code> is not null
     * @return the angle <code>this</code> - <code>a</code>.
     */
    public Angle minus(Angle a)
    {
        // These are standard trig identities. See the appendix of your
        // favorite calculus text book.
        double cosine = (this.cosine * a.cosine) + (this.sine * a.sine);
        double sine = (this.sine * a.cosine) - (this.cosine * a.sine);

        return new Angle(cosine, sine);
    }

    public static double toRadians(double angleInDegrees)
    {
        return (angleInDegrees / 360.0) * (2 * PI);
    }

    public static double toDegrees(double angleInRadians)
    {
        return (angleInRadians / (2 * PI)) * 360.0;
    }

    public static double toDegrees(Angle a)
    {
        return toDegrees(a.radians());
    }

    @Override
    public String toString()
    {
        return Double.toString(radians());
        // 'cosine' represents 'x' & 'sine' represents 'y' components
        // return "Angle(" + cosine + "," + sine + ")";
    }

    public boolean equals(Angle a)
    {
        if (a == null) return false;
        return (this.cosine == a.cosine) && (this.sine == a.sine);
    }

    @Override
    public boolean equals(Object o)
    {
        return (o instanceof Angle) && equals((Angle) o);
    }

    @Override
    public int hashCode()
    {
        return (new Double(sine)).hashCode() + (new Double(cosine)).hashCode();
    }
}
