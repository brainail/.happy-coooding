//data class ListNode<T>(var value: T) {
//    var next: ListNode<T>? = null;
//}

/**
Note: Try to solve this task in O(n) time using O(1) additional space, where n is the number of elements in l, since this is what you'll be asked to do during an interview.

Given a singly linked list of integers, determine whether or not it's a palindrome.

Example

For l = [0, 1, 0], the output should be
isListPalindrome(l) = true;
For l = [1, 2, 2, 3], the output should be
isListPalindrome(l) = false.
Input/Output

[execution time limit] 3 seconds (kt)

[input] linkedlist.integer l

A singly linked list of integers.

Guaranteed constraints:
0 ≤ list size ≤ 5 · 105,
-109 ≤ element value ≤ 109.

[output] boolean

Return true if l is a palindrome, otherwise return false.


 */
fun isListPalindrome(l: ListNode<Int>?): Boolean {
    var fast: ListNode<Int>? = l?.next ?: return true
    var slow: ListNode<Int>? = ListNode(Int.MIN_VALUE)
    slow!!.next = l
    var odd = false
    while (null != fast) {
        slow = slow?.next
        odd = null != fast.next
        fast = fast.next?.next
    }
    var first = l
    var second = if (odd) slow?.next?.next else slow?.next
    var prev = second
    second = second?.next
    slow?.next = null
    prev?.next = null
    while (null != second) {
        val next = second.next
        second.next = prev
        prev = second
        second = next
    }
    second = prev
    while (null != first && null != second) {
        if (first.value != second.value) {
            return false
        }
        first = first.next
        second = second.next
    }
    return true
}
