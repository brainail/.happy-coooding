fun gcd(a: Int, b: Int): Int {
    return if (0 == b) a else gcd(b, a.rem(b))
}

fun simplifyRational(numerator: Int, denominator: Int): MutableList<Int> {
    val sa = if (numerator < 0) -1 else +1
    val sb = if (denominator < 0) -1 else +1
    var a = sa * numerator
    var b = sb * denominator
    val x = gcd(a, b)
    a /= x
    b /= x
    return mutableListOf(a * (sa * sb), b)
}
