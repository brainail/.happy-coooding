package utilities.struct;

public class Complex<T extends Number>
{
    T a, b;

    public Complex(T a)
    {
        this.a = a;
        this.b = a;
    }

    public Complex(T a, T b)
    {
        this.a = a;
        this.b = b;
    }

    /**
     * Static creation method for a Fraction<Y>.
     * 
     * @param <T extends Number>
     * @param a
     * @param b
     * @return Fraction<T>(a, b)
     */
    public static <T extends Number> Complex<T> of(T a, T b)
    {
        return new Complex<T>(a, b);
    }

    /* Basic numeric operations */
    public static <T extends Number> Complex<Double> multiply(
        Complex<T> a,
        Complex<T> b)
    {
        return Complex.of(
            a.a.doubleValue() * b.a.doubleValue() - a.b.doubleValue()
                            * b.b.doubleValue(),
            a.a.doubleValue() * b.b.doubleValue() + a.b.doubleValue()
                            * b.a.doubleValue());
    }

    @Override
    public String toString()
    {
        return a + "+" + b + "i";
    }

}
