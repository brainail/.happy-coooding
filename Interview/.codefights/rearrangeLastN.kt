/**
Note: Try to solve this task in O(list size) time using O(1) additional space, since this is what you'll be asked during an interview.

Given a singly linked list of integers l and a non-negative integer n, move the last n list nodes to the beginning of the linked list.

Example

For l = [1, 2, 3, 4, 5] and n = 3, the output should be
rearrangeLastN(l, n) = [3, 4, 5, 1, 2];
For l = [1, 2, 3, 4, 5, 6, 7] and n = 1, the output should be
rearrangeLastN(l, n) = [7, 1, 2, 3, 4, 5, 6].
Input/Output

[execution time limit] 3 seconds (kt)

[input] linkedlist.integer l

A singly linked list of integers.

Guaranteed constraints:
0 ≤ list size ≤ 105,
-1000 ≤ element value ≤ 1000.

[input] integer n

A non-negative integer.

Guaranteed constraints:
0 ≤ n ≤ list size.

[output] linkedlist.integer

Return l with the n last elements moved to the beginning.
 */

data class ListNode<T>(var value: T) {
   var next: ListNode<T>? = null;
}

//
fun rearrangeLastN(l: ListNode<Int>?, n: Int): ListNode<Int>? {
    var tail: ListNode<Int>? = ListNode(0).apply { next = l }
    var head: ListNode<Int>? = tail

    (0 until n).forEach { head = head?.next }

    while (head?.next != null) {
        tail = tail?.next
        head = head?.next
    }

    if (l != tail?.next) {
        head?.next = l
    }
    val retVal = tail?.next
    tail?.next = null
    return retVal
}
