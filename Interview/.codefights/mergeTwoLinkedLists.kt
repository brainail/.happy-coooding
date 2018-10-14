/**
Note: Your solution should have O(l1.length + l2.length) time complexity, since this is what you will be asked to accomplish in an interview.

Given two singly linked lists sorted in non-decreasing order, your task is to merge them. In other words, return a singly linked list, also sorted in non-decreasing order, that contains the elements from both original lists.

Example

For l1 = [1, 2, 3] and l2 = [4, 5, 6], the output should be
mergeTwoLinkedLists(l1, l2) = [1, 2, 3, 4, 5, 6];
For l1 = [1, 1, 2, 4] and l2 = [0, 3, 5], the output should be
mergeTwoLinkedLists(l1, l2) = [0, 1, 1, 2, 3, 4, 5].
Input/Output

[execution time limit] 3 seconds (kt)

[input] linkedlist.integer l1

A singly linked list of integers.

Guaranteed constraints:
0 ≤ list size ≤ 104,
-109 ≤ element value ≤ 109.

[input] linkedlist.integer l2

A singly linked list of integers.

Guaranteed constraints:
0 ≤ list size ≤ 104,
-109 ≤ element value ≤ 109.

[output] linkedlist.integer

A list that contains elements from both l1 and l2, sorted in non-decreasing order.
 */

data class ListNode<T>(var value: T) {
   var next: ListNode<T>? = null;
}

//
fun mergeTwoLinkedLists(l1: ListNode<Int>?, l2: ListNode<Int>?): ListNode<Int>? {
    var A = l1
    var B = l2
    val head = ListNode(0)
    var cur = head
    while (null != A?.value || null != B?.value) {
        if (null == A?.value || (null != B?.value && B?.value <= A?.value)) {
            cur.next = ListNode(B?.value!!)
            cur = cur.next!!
            B = B?.next
        } else {
            cur.next = ListNode(A?.value!!)
            cur = cur.next!!
            A = A?.next
        }
    }
    return head.next
}
