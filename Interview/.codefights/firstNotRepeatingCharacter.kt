/**
Note: Write a solution that only iterates over the string once and uses O(1) additional memory, since this is what you would be asked to do during a real interview.

Given a string s, find and return the first instance of a non-repeating character in it. If there is no such character, return '_'.

Example

For s = "abacabad", the output should be
firstNotRepeatingCharacter(s) = 'c'.

There are 2 non-repeating characters in the string: 'c' and 'd'. Return c since it appears in the string first.

For s = "abacabaabacaba", the output should be
firstNotRepeatingCharacter(s) = '_'.

There are no characters in this string that do not repeat.

Input/Output

[execution time limit] 3 seconds (kt)

[input] string s

A string that contains only lowercase English letters.

Guaranteed constraints:
1 ≤ s.length ≤ 105.

[output] char

The first non-repeating character in s, or '_' if there are no characters that do not repeat.
 */
fun firstNotRepeatingCharacter(s: String): Char {
    val occ = IntArray(27, { -1 })
    for (i in s.indices) {
        val ci = s [i].toInt() - 'a'.toInt()
        if (occ [ci] >= 0) {
            occ [ci] = Int.MAX_VALUE
        } else {
            occ [ci] = i
        }
    }
    var result = Int.MAX_VALUE
    for (i in occ.indices) {
        if (occ [i] >= 0) {
            result = Math.min(result, occ [i])
        }
    }
    return if (Int.MAX_VALUE == result) '_' else s [result]
}

fun main(args: Array<String>) {
    println(firstNotRepeatingCharacter("abacabad") == 'c')
    println(firstNotRepeatingCharacter("abacabaabacaba") == '_')
    println(firstNotRepeatingCharacter("z") == 'z')
}
