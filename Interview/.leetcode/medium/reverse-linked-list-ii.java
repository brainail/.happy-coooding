/**
 * Reverse a linked list from position m to n. Do it in one-pass.
 * 
 * Note: 1 ≤ m ≤ n ≤ length of list.
 * 
 * Example:
 * 
 * Input: 1->2->3->4->5->NULL, m = 2, n = 4 Output: 1->4->3->2->5->NULL
 */

class Solution {
    public ListNode reverseBetween(ListNode head, int from, int to) {
        ListNode mainHead = new ListNode(-1), priorFromNode = mainHead, fromNode = head;
        mainHead.next = head;
        for (int i = 1; i < from; ++i) { // find start position and keep previous
            fromNode = fromNode.next;
            priorFromNode = priorFromNode.next;
        }
        ListNode reversedHead = new ListNode(-1), refFromNode = fromNode;
        for (int i = 0; i <= to - from; ++i) { // reverse from..to
            ListNode prev = reversedHead.next;
            reversedHead.next = fromNode;
            fromNode = fromNode.next;
            reversedHead.next.next = prev;
        }
        priorFromNode.next = reversedHead.next; // join reversed with prior to start position
        refFromNode.next = fromNode; // join end of reversed with remaining part
        return mainHead.next;
    }
}
