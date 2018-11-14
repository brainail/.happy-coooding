/**
 * Given a linked list, remove the n-th node from the end of list and return its
 * head.
 * 
 * Example:
 * 
 * Given linked list: 1->2->3->4->5, and n = 2.
 * 
 * After removing the second node from the end, the linked list becomes
 * 1->2->3->5. Note:
 * 
 * Given n will always be valid.
 * 
 * Follow up:
 * 
 * Could you do this in one pass?
 */
class Solution {
    public ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode nahead = head;
        for (int i = 1; i < n; ++i)
            nahead = nahead.next;
        ListNode memoHead = head;
        ListNode prev = null;
        while (nahead.next != null) {
            nahead = nahead.next;
            prev = head;
            head = head.next;
        }
        if (prev == null) {
            memoHead = head.next;
        } else {
            prev.next = head.next;
        }
        return memoHead;
    }
}