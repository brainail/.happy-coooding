package utilities.math;

/* 
 The extended Euclidean algorithm is an extension to the Euclidean algorithm.
 Besides finding the greatest common divisor of integers a and b, as the
 Euclidean algorithm does, it also finds integers x and y (one of which is
 typically negative) that satisfy Bezout's identity

 ax + by = gcd(a,b).

 The extended Euclidean algorithm is particularly useful when a and b are
 coprime, since x is the multiplicative inverse of a modulo b, and y is the
 multiplicative inverse of b modulo a.

 One can handle the case of more than 2 numbers iteratively. First we show that
 gcd(a,b,c) = gcd(gcd(a,b),c). To prove this let d = gcd(a,b,c). By definition
 of gcd d is a divisor of a and b. Thus gcd(a,b) = kd for some k. Similarly d
 is a divisor of c so c = jd for some j. Let u = gcd(k,j). By our construction
 of u, ud | a,b,c but since d is the greatest divisor u is a unit. And since ud
 = gcd(gcd(a,b),c) the result is proven.

 So if na + mb = gcd(a,b) then there are x and y such that xgcd(a,b) + yc =
 gcd(a,b,c) so the final equation will be

 x(na + mb) + yc = (xn)a + (xm)b + yc = \gcd(a,b,c).\,

 So then to apply to n numbers we use induction

 \gcd(a_1,a_2,\dots,a_n) =\gcd(a_1,\, \gcd(a_2,\, \gcd(a_3,\dots,
 \gcd(a_{n-1}\,,a_n)))\dots),

 with the equations following directly.
 */

public class EGCD
{
    static class Point
    {
        int x, y;

        Point(int xx, int yy)
        {
            x = xx;
            y = yy;
        }
    }

    public static void main(String[] args)
    {
        Point p = extendedGCD(5, -6);
        System.out.println(p.x + " " + p.y);
    }

    public static Point extendedGCD(int a, int b)
    {
        if ((a % b) == 0) return new Point(0, 1);
        Point p = extendedGCD(b, a % b);
        return new Point(p.y, p.x - (p.y * (a / b)));
    }
}
