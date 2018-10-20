/**
 * Given a singly linked list L: L0→L1→…→Ln-1→Ln, reorder it to:
 * L0→Ln→L1→Ln-1→L2→Ln-2→…
 * 
 * You may not modify the values in the list's nodes, only nodes itself may be
 * changed.
 * 
 * Example 1:
 * 
 * Given 1->2->3->4, reorder it to 1->4->2->3. Example 2:
 * 
 * Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
 */
class Solution {
    public void reorderList(ListNode head) {
        if (null == head || null == head.next) {
            return; // early exit
        }

        ListNode slow = head;
        ListNode fast = head.next;
        while (fast.next != null) {
            slow = slow.next;
            fast = fast.next;
            fast = null != fast.next ? fast.next : fast;
        }
        ListNode head2 = slow.next;
        slow.next = null;

        ListNode prev = null;
        ListNode cur = head2;
        while (cur != null) {
            ListNode next = cur.next;
            cur.next = prev;
            prev = cur;
            cur = next;
        }

        head2 = fast;
        ListNode head1 = head;
        while (head1 != null && head2 != null) {
            ListNode next1 = head1.next;
            ListNode next2 = head2.next;
            head1.next = head2;
            head2.next = next1;
            head1 = next1;
            head2 = next2;
        }
    }
}
